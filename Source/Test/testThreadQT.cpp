#include <math.h>
#include <vector>

#include "OSGConfig.h"
#include "OSGGL.h"

#include <QtGui/QApplication>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>

#if defined(Q_CC_MSVC)
#pragma warning(disable:4305) // init: truncation from const double to float
#endif

#include "OSGSceneFileHandler.h"
#include "OSGSimpleGeometry.h"
#include "OSGPassiveWindow.h"
#include "OSGSimpleSceneManager.h"


class OpenSGWidget;


// MT Ptr takes care of correct aspect handling
OSG::TransformMTRecPtr  trans;

OSG::ThreadRefPtr       applicationThread;
OSG::ThreadRefPtr		renderThread;

OSG::BarrierRefPtr      syncBarrier;
//OSG::LockRefPtr			deadlock;

bool doQuit = false, quit = false;

OpenSGWidget *renderWidget = NULL;


//-------------------------------------------------------------------
// special qgl context, not yet very helpful 
// http://doc.qt.nokia.com/4.7/qglcontext.html
//-------------------------------------------------------------------
class OpenSGGLContext : public QGLContext
{
public:
    OpenSGGLContext(const QGLFormat &format, QPaintDevice *device) 
		: QGLContext(format, device)
    {
    }

    virtual ~OpenSGGLContext()
    {
    }

	/// Makes _no_ GL context the current context
    virtual void doneCurrent(void) 
    {
        QGLContext::doneCurrent();
    }

	/// Makes this context the current context
	virtual void makeCurrent(void)
    {
        QGLContext::makeCurrent();
    }
};

//-------------------------------------------------------------------
// special opensg qgl widget
//-------------------------------------------------------------------
class OpenSGWidget : public QGLWidget
{
public:
    OpenSGWidget(const QGLFormat &f, QWidget *parent=0);

    OSG::SimpleSceneManager *getManager(void);
    bool isInitialized(void);

    virtual void makeCurrent(void);
    virtual void doneCurrent(void);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

	void keyPressEvent(QKeyEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);
	void closeEvent(QCloseEvent *ev);

private:
    OSG::SimpleSceneManagerRefPtr mgr;
    OSG::PassiveWindowRecPtr      pwin;
    bool _initialized;
};


OpenSGWidget::OpenSGWidget(const QGLFormat &f, QWidget *parent)
     : QGLWidget(f, parent)
{
    setAutoBufferSwap(false);
	setContext(new OpenSGGLContext(f, this));

    mgr = OSG::SimpleSceneManager::create();
    pwin = OSG::PassiveWindow::create();
    mgr->setWindow(pwin);
}

OSG::SimpleSceneManager *OpenSGWidget::getManager(void)
{
    return mgr;
}

bool OpenSGWidget::isInitialized(void)
{
    return _initialized;
}

void OpenSGWidget::makeCurrent(void)
{
    if (OSG::Thread::getCurrent() == applicationThread)
    {
        SLOG << "OpenSGWidget::makeCurrent from main thread!" << std::endl;
        // when the render thread is not running yet and while initializing
        // the gl widget we have to call makeCurrent() for the main thread!
        if (renderThread != NULL)
            return;
    }
	
    QGLWidget::makeCurrent();
}

void OpenSGWidget::doneCurrent(void)
{
    const_cast<OpenSGGLContext *>(
        static_cast<const OpenSGGLContext *>(context()))->doneCurrent();
}

void OpenSGWidget::initializeGL()
{
    pwin->init();

	_initialized = true;
}

void OpenSGWidget::resizeGL( int width, int height )
{
	// Attention, do we need some context handling here?
	if (OSG::Thread::getCurrent() == applicationThread)
    {
        SLOG << "OpenSGWidget::resizeGL from main thread!" << std::endl;
        return;
    }

    mgr->resize(width, height);
}

void OpenSGWidget::paintGL()
{
	if (OSG::Thread::getCurrent() == applicationThread)
    {
        SLOG << "OpenSGWidget::paintGL from main thread!" << std::endl;
        return;
    }
	
    mgr->redraw();
    swapBuffers();
}

void OpenSGWidget::closeEvent( QCloseEvent *ev )
{
    QGLWidget::closeEvent(ev);
    doQuit = true;
}

void OpenSGWidget::keyPressEvent( QKeyEvent *ev )
{
    switch ( ev->key() ) 
    {
        case Qt::Key_Escape:
			doQuit = true;
			break;
		default:
			return;
	}
}

void OpenSGWidget::mousePressEvent( QMouseEvent *ev )
{
    OSG::UInt32 button;
    
    switch ( ev->button() ) 
    {
        case Qt::LeftButton:  
            button = OSG::SimpleSceneManager::MouseLeft;   
            break;
        case Qt::MidButton:   
            button = OSG::SimpleSceneManager::MouseMiddle; 
            break;
        case Qt::RightButton: 
            button = OSG::SimpleSceneManager::MouseRight;  
            break;
        default:          
			return;
    }

    mgr->mouseButtonPress(button, ev->x(), ev->y());
    update();
}

void OpenSGWidget::mouseReleaseEvent( QMouseEvent *ev )
{
    OSG::UInt32 button;
    
    switch ( ev->button() ) 
    {
        case Qt::LeftButton:  
            button = OSG::SimpleSceneManager::MouseLeft;   
            break;
        case Qt::MidButton:   
            button = OSG::SimpleSceneManager::MouseMiddle; 
            break;
        case Qt::RightButton: 
            button = OSG::SimpleSceneManager::MouseRight;  
            break;
        default:          
			return;
    }

    mgr->mouseButtonRelease(button, ev->x(), ev->y());
    update();
}

void OpenSGWidget::mouseMoveEvent( QMouseEvent *ev )
{
    mgr->mouseMove(ev->x(), ev->y());
    update();
}

void OpenSGWidget::wheelEvent( QWheelEvent *ev )
{
    mgr->mouseButtonPress(ev->delta() > 0 ? OSG::SimpleSceneManager::MouseUp
                                          : OSG::SimpleSceneManager::MouseDown, 
                          ev->x(), ev->y());
    
    ev->accept();
    update();
}


//-------------------------------------------------------------------
static void renderFunc(void *cl)
{
	/*
    syncBarrier->enter(2);
    applicationThread->getChangeList()->applyNoClear();
	syncBarrier->enter(2);

    OSG::commitChanges();
    renderThread->getChangeList()->clear();
	*/

    while (!quit)
    {
		//SLOG << "Render thread" << std::endl;
		//OSG::commitChanges();

        // sync
        syncBarrier->enter(2);

        // merge changes into aspect
        applicationThread->getChangeList()->applyNoClear();
		OSG::commitChanges();

        syncBarrier->enter(2);

        renderWidget->updateGL();
        renderThread->getChangeList()->clear();

		//OSG::osgSleep(40);
    }
}

//-------------------------------------------------------------------
static void appFunc(void *cl)
{
	//if (syncBarrier->getNumWaiting() > 0)
	{
		// do some stupid animation in the main thread
		static OSG::Real64 t = 0.0;
		OSG::Real64 t1 = OSG::getSystemTime(), d = t1 - t;
        t = t1;

		static OSG::Real32 w = 0;
		w += d;
		if (w >= 2 * OSG::Pi) w = 0;

        //SLOG << "App thread " << w << std::endl;

		//deadlock->acquire();
        OSG::Matrix m;
        m.setRotate(OSG::Quaternion(OSG::Vec3f(0, 1, 0), w));
		trans->setMatrix(m);
        //deadlock->release();

		//OSG::osgSleep(50);
		OSG::commitChanges();

		/*
		syncBarrier->enter(2);
		//renderThread->getChangeList()->applyNoClear();
		//OSG::commitChanges();
		syncBarrier->enter(2);

		applicationThread->getChangeList()->clear();
		*/
	}
}


//-------------------------------------------------------------------
int main( int argc, char **argv )
{
	OSG::ChangeList::setReadWriteDefault(true);

    OSG::osgInit(argc,argv);
    
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );

    if ( !QGLFormat::hasOpenGL() ) {
		qWarning( "This system has no OpenGL support, exiting..." );
		return -1;
    }

	syncBarrier = OSG::Barrier::get("syncBarrier", true);
	//deadlock	= OSG::Lock::get("syncLock", true);
    
	renderWidget = new OpenSGWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer | 
											  QGL::Rgba | QGL::DirectRendering));
	renderWidget->setFixedSize(512, 512);

	// create a boring scene...
    OSG::NodeRecPtr scene = OSG::Node::create();

	OSG::Matrix m;
    m.setIdentity();

    trans = OSG::Transform::create();
    trans->setMatrix(m);
    
    scene->setCore(trans);

    if (argc > 1)
    {
        for (OSG::UInt16 i = 1; i < argc; ++i)
            scene->addChild(OSG::SceneFileHandler::the()->read(argv[i]));
    }
    else
    {
		    OSG::NodeRecPtr n = OSG::makeTorus(0.5,2.0,16,16);
			scene->addChild(n);
    }

    renderWidget->getManager()->setRoot(scene);
    renderWidget->getManager()->showAll();

    renderWidget->show();

    while (!renderWidget->isInitialized())
	{
        a.processEvents();
		OSG::osgSleep(20);
	}
	
    // The GL widget is initialized in the main thread
    // Without doneCurrent() the next makeCurrent() call in the render thread does not work, 
    // because qt thinks that the context is already current, but this was in the main thread
	renderWidget->doneCurrent();

	applicationThread = 
			dynamic_cast<OSG::Thread*>(OSG::ThreadManager::getAppThread());

	renderThread = OSG::dynamic_pointer_cast<OSG::Thread>(
            OSG::ThreadManager::the()->getThread("RenderThread", false) );
    
	// start render thread
	renderThread->runFunction(renderFunc, 1, NULL);

	OSG::commitChanges();

	/*
	syncBarrier->enter(2);
    syncBarrier->enter(2);
	applicationThread->getCurrentChangeList()->clear();
    */

	// main loop
	while (!quit)
    {
        appFunc(0);

		// sync
        syncBarrier->enter(2);

        if (doQuit)
            quit = true;

        syncBarrier->enter(2);
        
        applicationThread->getCurrentChangeList()->clear();

        qApp->processEvents();
    }

	OSG::Thread::join(renderThread);

	//return a.exec();
	return 0;
}
