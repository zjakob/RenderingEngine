cmake_minimum_required(VERSION 3.6)
project(Game)


### --- CONFIG --- ###
# enable verbose cmake output
set(CMAKE_VERBOSE_MAKEFILE ON)

# set c++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# add cmake-modules folder for finding libs (e.g. FindGLFW.cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMakeModules")



### ------------ ADD LIBRARIES ------------ ###

# find X11
find_package(X11 REQUIRED)
message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
if (X11_FOUND)
    include_directories(${X11_INCLUDE_DIR})
    link_directories(${X11_LIBRARIES})
    #target_link_libraries(Game ${X11_LIBRARIES})
    link_libraries(${X11_LIBRARIES})
    #MESSAGE( WARNING "" ${X11_LIBRARIES} )
else()
    MESSAGE(FATAL_ERROR "X11 Not Found")
endif()

# find OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    link_libraries(${OPENGL_LIBRARIES})
else()
    MESSAGE(FATAL_ERROR "OpenGL Not Found")
endif()

# find GLFW library
#set(GLFW_INCLUDE_DIR "/usr/local/include/")
#set(GLFW_LIBRARY "/usr/local/lib/ibglfw3.a")
find_package(GLFW REQUIRED)
if (GLFW_FOUND)
    #set(GLFW_LIBRARIES ${OPENGL_LIBRARIES} ${GLFW_LIBRARY})
    #set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
    include_directories(${GLFW_INCLUDE_DIRS})
    link_libraries(${GLFW_LIBRARIES})
    #MESSAGE( WARNING "" ${GLFW_LIBRARIES} )
endif()

# find GLM library
set(GLM_INCLUDE_DIR "/usr/local/include/glm")
find_package(GLM 0.9.8 REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
else()
    MESSAGE(FATAL_ERROR "GLM >= v.0.9.8 Not Found")
endif()

# find GLEW 2.0 library
#set(GLEW_INCLUDE_DIR "/usr/include/")
#set(GLEW_LIBRARY "/usr/lib/x86_64-linux-gnu/libGLEW.so")
find_package(GLEW 2.0 REQUIRED STATIC)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
    #MESSAGE( WARNING "" ${GLEW_LIBRARIES} )
else()
    MESSAGE(FATAL_ERROR "GLEW >= v.2.0 Not Found")
endif()

# add static Engine lib
#find_path(STATIC_LIB_INCLUDE_DIR
#    NAMES library.h
#    PATHS ${PROJECT_SOURCE_DIR}/../CLionProjects/CmakeTestStaticLib/src)
#MESSAGE( WARNING "staticlib: " ${STATIC_LIB_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../Engine/src/)
#FIND_PATH(ENGINE_INCLUDE_DIRS *.h "${PROJECT_SOURCE_DIR}/../Engine/src/EventSystem/")
#INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
#MESSAGE( WARNING "staticlib dir: " ${ENGINE_INCLUDE_DIRS})
find_library(CMAKE_TEST_STATIC_LIB
        NAMES Engine
        PATHS ${PROJECT_SOURCE_DIR}/../Engine/bin)
#MESSAGE( WARNING "staticlib: " ${CMAKE_TEST_STATIC_LIB})



### ------------ SET OUTPUT PATH ------------ ###
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

### ------------ ADD SOURCE ------------ ###
# recursively add all source files
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)
add_executable(Game ${SOURCE_FILES})


### ------------ LINK ------------ ###
target_link_libraries(Game PUBLIC ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${CMAKE_TEST_STATIC_LIB} Xxf86vm Xrandr Xinerama X11 Xcursor pthread dl GLEW glfw3)