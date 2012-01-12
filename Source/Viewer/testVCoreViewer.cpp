#include "OSGConfig.h"

#include <iostream>

#include "OSGVCSystem.h"
#include "OSGVCApp.h"
#include "OSGVCGLUTNativeWindow.h"

OSG_USING_NAMESPACE

VCORE_USING_NAMESPACE

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);
    OSG::osgLog().setLogLevel(OSG::LOG_NOTICE);
    VCSystem::init(argc, argv);

    VCAppRefPtr app = VCApp::createFromFile("trala");   // just creates a dummy
    VCGLUTNativeWindow::setupGLUTApp(*app);     // app should use glut

    app->run(); // this never returns atm, so the whole shutdown thing is not
                // working right now.

    VCSystem::shutdown();
    OSG::osgExit();

    return 0;
}
