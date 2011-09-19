
#include "OSGVCoreApp.h"

int run(int argc, char **argv)
{
#ifdef WIN32
    OSG::preloadSharedObject("OSGImageFileIO");
#endif

    OSG::ChangeList::setReadWriteDefault(true);

    OSG::osgInit(argc,argv);

    if(argc == 2) 
    {
        fprintf(stderr, "Trying to start from : %s\n", argv[1]);

        OSG::VCoreAppUnrecPtr pApp = OSG::VCoreApp::create();

        pApp->startFrom(argv[1]);

        pApp->run();

        pApp = NULL;
    }

	return 0;
}

int main (int argc, char **argv)
{
    run(argc, argv);

    return 0;
}
