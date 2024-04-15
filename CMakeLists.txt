cmake_minimum_required(VERSION 3.26.4)
project(lab8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_executable(${PROJECT_NAME} src/main.cpp
        src/window/window.h
        src/window/window.cpp
        src/window/events.cpp
        src/window/events.h
        src/graphics/Shader.h
        src/graphics/Shader.cpp
        src/window/camera.h
        src/window/camera.cpp
        src/Kubic_Rubica.hpp)

target_link_libraries(${PROJECT_NAME}
        glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES}
        libglew_static
        glm::glm
)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDES})



