project(Bomberman)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/")
#set(CMAKE_CXX_FLAGS "-Wall -W -Werror -ansi -pedantic -g")

# Bien sûr, pour compiler Ogre, il faut le chercher, et définir le répertoire contenant les includes.
find_package(OGRE REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS})


find_package(OIS REQUIRED)
if (NOT OIS_FOUND)
    message(SEND_ERROR "Failed to find OIS.")
endif ()

#include
include_directories(includes)

# On définit les sources qu'on veut compiler
SET(SOURCES
        main.cpp
        src/Map.cpp
        src/Objects/Wall.cpp
        includes/Map.hpp
        includes/AGameObject.hpp
        includes/Wall.hpp
        src/Objects/AGameObject.cpp
        src/Controller/EventManager.cpp
        includes/EventManager.hpp
        )

# On les compile
add_executable(
        Bomberman ${SOURCES}
)

target_link_libraries(Bomberman ${OGRE_LIBRARY} ${OIS_LIBRARY} -lboost_system)