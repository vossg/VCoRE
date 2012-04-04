
MESSAGE(STATUS "Prepare VCore")

#############
#### BOOST
#############

IF(Boost_FOUND)
  FIND_PACKAGE(Boost COMPONENTS thread)

  IF(Boost_FOUND AND WIN32)

    SET(OSG_BOOST_THREAD_TARGETS )
    OSG_ADD_IMPORT_LIB(OSG_BOOST_THREAD_TARGETS Boost_THREAD_LIBRARY)
    SET(OSG_BOOST_THREAD_LIBS ${OSG_BOOST_THREAD_TARGETS})
      
  ELSE(Boost_FOUND AND WIN32)

    IF(CMAKE_BUILD_TYPE STREQUAL "Debug" OR 
       CMAKE_BUILD_TYPE STREQUAL "DebugOpt")

      SET(OSG_BOOST_THREAD_LIBS ${Boost_THREAD_LIBRARY_DEBUG})

    ELSE()
    
      SET(OSG_BOOST_THREAD_LIBS ${Boost_THREAD_LIBRARY_RELEASE})
    ENDIF()

  ENDIF(Boost_FOUND AND WIN32)

  # We ignore if boost thread fails, we catch that somewhere else
  # so if we get here Boost_FOUND was true in the first place
  SET(Boost_FOUND TRUE)
ENDIF()