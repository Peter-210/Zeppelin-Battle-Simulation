cmake_minimum_required(VERSION 3.25)
project(main)

file(GLOB SOURCE CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADER CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/header/*.h")
add_executable(main ${SOURCE} ${HEADER})

find_package(OpenGL REQUIRED)

set (CMAKE_LIBRARY_PATH "C:/Program Files (x86)/Windows Kits/10/Lib/win8/km/x64")
set(OPENGL_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Dependencies/freeglut/include")
set(GLUT_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include")
set(OPENGL_LIBRARIES "${CMAKE_SOURCE_DIR}/Dependencies/freeglut/lib/x64/freeglut.lib")
set(GLUT_LIBRARIES "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/lib/Release/x64/glew32.lib")

include_directories(
    "${CMAKE_SOURCE_DIR}/Dependencies/freeglut/include"
    "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include"
)
target_link_libraries(main 
    PRIVATE OpenGL::GL
    glu32
    "${CMAKE_SOURCE_DIR}/Dependencies/freeglut/lib/x64/freeglut.lib" 
    "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/lib/Release/x64/glew32s.lib"
)
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Dependencies/freeglut/bin/x64/freeglut.dll"
        $<TARGET_FILE_DIR:main>
)