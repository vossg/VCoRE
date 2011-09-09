
#include "OSGConfig.h"

#include "OSGBaseInitFunctions.h"

#include "OSGNode.h"

#include "OSGSceneFileHandler.h"
#include "OSGOSGWriter.h"
#include "OSGOSGSceneFileType.h"

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::FieldContainerUnrecPtr pFile = NULL;

    if(argc > 1)
    {
        pFile = OSG::OSGSceneFileType::the().readContainer(argv[1], NULL);
    }

    OSG::commitChanges();

    if(pFile != NULL)
    {
        fprintf(stderr, "===================== GOP ========================\n");

#if 1
#if 0
        const char *outFileName = "/tmp/foo1.osg";

        OSG::IndentFileOutStream outFileStream(outFileName);

        if( !outFileStream )
        {
            std::cerr << "Can not open output stream to file: "
                      << outFileName << std::endl;
            return -1;
        }

        std::cerr << "STARTING PRINTOUT:" << std::endl;
        OSG::OSGWriter writer( outFileStream, 4 );
#endif

        OSG::OSGSceneFileType::the().writeContainer(pFile, "/tmp/foo1.osg");

//        outFileStream.close();

//        OSG::SceneFileHandler::the()->write(pFile, "/tmp/foo.osb");
//        OSG::SceneFileHandler::the()->write(pFile, "/tmp/foo.wrl");
#endif    
    }

    pFile = NULL;
    
    OSG::osgExit();

    return 0;
}
