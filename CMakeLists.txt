project(Bomberman)
cmake_minimum_required(VERSION 2.6)

if(WIN32)
    set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH
            $ENV{OGRE_HOME}/Samples/include
            )
endif(WIN32)

if(UNIX)
    if(EXISTS "/usr/local/lib/OGRE/cmake")
        set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local
    elseif(EXISTS "/usr/share/local/lib/OGRE/cmake")
        set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local
    elseif(EXISTS "/usr/lib/OGRE/cmake")
        set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one
    else ()
        message(SEND_ERROR "Failed to find module path.")
    endif()
endif(UNIX)

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")

find_package(OGRE REQUIRED)

IF (OIS_LIBRARIES AND OIS_INCLUDE_DIR)
    SET(OIS_FIND_QUIETLY TRUE) # Already in cache, be silent
ENDIF (OIS_LIBRARIES AND OIS_INCLUDE_DIR)

IF (WIN32) #Windows
    MESSAGE(STATUS "Looking for OIS")
    SET(OIS_INCLUDE_DIR ../libs/ogre/Dependencies/include)
    SET(OIS_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libs/ogre/Samples/Common/bin/Release)
    SET(OIS_LIBRARIES debug OIS_d optimized OIS)
ELSE (WIN32) #Unix
    FIND_PACKAGE(PkgConfig)
    PKG_SEARCH_MODULE(OIS OIS /usr/pack/ois-1.0-sd/i686-debian-linux3.1/lib/pkgconfig/OIS.pc) # tardis specific hack
    SET(OIS_INCLUDE_DIR ${OIS_INCLUDE_DIRS})
    SET(OIS_LIB_DIR ${OIS_LIBDIR})
    SET(OIS_LIBRARIES ${OIS_LIBRARIES} CACHE STRING "")
ENDIF (WIN32)

#Do some preparation
SEPARATE_ARGUMENTS(OIS_INCLUDE_DIR)
SEPARATE_ARGUMENTS(OIS_LIBRARIES)

SET(OIS_INCLUDE_DIR ${OIS_INCLUDE_DIR} CACHE PATH "")
SET(OIS_LIBRARIES ${OIS_LIBRARIES} CACHE STRING "")
SET(OIS_LIB_DIR ${OIS_LIB_DIR} CACHE PATH "")

IF (OIS_INCLUDE_DIR AND OIS_LIBRARIES)
    SET(OIS_FOUND TRUE)
ENDIF (OIS_INCLUDE_DIR AND OIS_LIBRARIES)

IF (OIS_FOUND)
    IF (NOT OIS_FIND_QUIETLY)
        MESSAGE(STATUS "  libraries : ${OIS_LIBRARIES} from ${OIS_LIB_DIR}")
        MESSAGE(STATUS "  includes  : ${OIS_INCLUDE_DIR}")
    ENDIF (NOT OIS_FIND_QUIETLY)
ELSE (OIS_FOUND)
    IF (OIS_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find OIS")
    ENDIF (OIS_FIND_REQUIRED)
ENDIF (OIS_FOUND)
if(WIN32)
    set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH
            $ENV{OGRE_HOME}/Samples/include
            )
endif(WIN32)


if(NOT OIS_FOUND)
    message(SEND_ERROR "Failed to find OIS.")
endif()

# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
    if (WIN32 OR APPLE)
        set(Boost_USE_STATIC_LIBS TRUE)
    else ()
        set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
    endif ()
    if (MINGW)
        set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
    endif ()
    set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
    set(OGRE_BOOST_COMPONENTS thread date_time)
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
    if (NOT Boost_FOUND)
        set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
        find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
    endif()
    find_package(Boost QUIET)

    include_directories(${Boost_INCLUDE_DIR})
    add_definitions(-DBOOST_ALL_NO_LIB)
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

include_directories(includes)
include_directories(SYSTEM
  /usr/local/include/cegui-0
)

link_directories(
  /usr/local/lib/
)

set(CEGUI_LIBS CEGUIBase-0 CEGUICommonDialogs-0 CEGUIOgreRenderer-0)

SET(SRCS
        src/main.cpp
        src/MapManager.cpp
        src/Collision.cpp
        src/Objects/Wall.cpp
        src/Objects/AGameObject.cpp
        src/Objects/ACharacter.cpp
        src/Objects/Player.cpp
        src/Objects/Bomb.cpp
        src/Common/Manager/ConfigManager.cpp
#        src/Controller/KeyController.cpp
        src/Common/Manager/NodeManager.cpp
        src/Common/Manager/CameraManager.cpp
        src/Common/Manager/GameManager.cpp
        #        src/Common/Manager/ConfigManager.cpp
        src/Controller/EventManager.cpp
        includes/Common/Manager/GameManager.hpp
        includes/Common/Manager/NodeManager.hpp
        includes/Common/Manager/CameraManager.hpp
        #        includes/Common/Manager/ConfigManager.hpp
        includes/Controller/EventManager.hpp
        includes/Interfaces/AGameObject.hpp
        includes/Interfaces/ACharacter.hpp
#        includes/Controller/KeyController.hpp
        includes/Common/Manager/ConfigManager.hpp
        includes/Objects/Player.hpp
        includes/MapManager.hpp
        includes/Objects/Wall.hpp
        includes/Objects/Bomb.hpp
        includes/Collision.hpp
        )

set(HDRS ${SRCS})
set(CMAKE_CXX_FLAGS "-Iincludes -std=c++11")

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

include_directories( ${OIS_INCLUDE_DIRS}
        ${OGRE_INCLUDE_DIRS}
        ${OGRE_SAMPLES_INCLUDEPATH}
        ${OGRE_Overlay_INCLUDE_DIRS}
        )

add_executable(bomberman WIN32 ${HDRS} ${SRCS})

set_target_properties(bomberman PROPERTIES DEBUG_POSTFIX _d)

#${CEGUI_LIBS} ${FREETYPE_LIBRARIES}

target_link_libraries(bomberman OgreOverlay OgreMain ${OGRE_LIBRARIES} ${OIS_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/assets)

if(WIN32 AND NOT MINGW)
    add_custom_command( TARGET bomberman PRE_BUILD
            COMMAND if not exist .\\bin mkdir .\\bin )
    add_custom_command( TARGET bomberman POST_BUILD
            COMMAND copy \"$(TargetPath)\" .\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
endif(MINGW OR UNIX)

if(WIN32)

    install(TARGETS bomberman
            RUNTIME DESTINATION bin
            CONFIGURATIONS All)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets
            DESTINATION ./
            CONFIGURATIONS Release RelWithDebInfo Debug
            )

    install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins.cfg
            ${CMAKE_SOURCE_DIR}/bin/resources.cfg
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo
            )

    install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins_d.cfg
            ${CMAKE_SOURCE_DIR}/bin/resources_d.cfg
            DESTINATION bin
            CONFIGURATIONS Debug
            )

    install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
            ${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
            ${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
            ${OGRE_PLUGIN_DIR_REL}/libOIS.dll
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo
            )

    install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
            ${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
            ${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
            ${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
            DESTINATION bin
            CONFIGURATIONS Debug
            )

    install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
            ${Boost_THREAD_LIBRARY_RELEASE}
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo
            )

    install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
            ${Boost_THREAD_LIBRARY_DEBUG}
            DESTINATION bin
            CONFIGURATIONS Debug
            )
endif(WIN32)

if(UNIX)

    install(TARGETS bomberman
            RUNTIME DESTINATION bin
            CONFIGURATIONS All)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets
            DESTINATION ./
            CONFIGURATIONS Release RelWithDebInfo Debug
            )

    install(FILES ${CMAKE_SOURCE_DIR}/plugins.cfg
            ${CMAKE_SOURCE_DIR}/bin/resources.cfg
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo Debug
            )

endif(UNIX)
