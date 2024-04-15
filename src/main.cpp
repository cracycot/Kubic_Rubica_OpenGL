#include "iostream"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "window/window.h"
#include "window/events.h"
#include "graphics/Shader.h"
#include <glm/glm.hpp>
#include "stack"
#include <cstdlib>
#include <fstream>
#include "window/camera.h"
#include "Kubic_Rubica.hpp"
const int WIDTH = 3024;
const int HEIGHT = 1964;

int main(int argc, char** argv) {
    int flag_load = false;
    std::cout<<"Введите 1 если хотите загрузить состояние кубика иначе 0"<<"\n";
    std::cin>>flag_load;

    std::stack<int> comm;
    std::stack<int> command_sbor;

    bool flag_razb = false;
    bool flag_sbor = false;

    if (not(flag_load)) {
        int min = 0;
        int max = 5;
        for (int i = 0; i < 10; i++) {
            int randomNum = min + rand() % (max - min + 1);
            comm.push(randomNum);
        }
    }
    else {
        std::ifstream inputFile("/Users/kirilllesniak/Desktop/ITMO/PROGA/LABI_PO_PROGE/SEM2/lab8/src/condition"); // открываем файл для чтения
        if (!inputFile.is_open()) {
            std::cout << "Ошибка открытия файла." << std::endl;
            return 1;
        }
        int num;
        while (inputFile >> num) { // читаем числа из файла
            comm.push(num);
        }
        inputFile.close();
        flag_razb = true;
    }



    Window::initialize(WIDTH, HEIGHT, "name");
    Events::initialize();
    Shader* shader = load_shader("../res/main.glslv", "../res/main.glslf");

    if (shader == nullptr) {
        std::cerr<<"failed to load shader"<<"\n";
        Window::terminate();
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1);
    Kubic_Rubica a = Kubic_Rubica();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Camera* camera = new Camera(vec3(0.0f, 3.0f, 5.0f), 70.0f);
    float lastTime = glfwGetTime();
    float delta = 0.0f;

    float camX = 0.0f;
    float camY = 0.0f;

    float speed = 5;
    int i = 99;

    bool flag_click = false;
    glEnable(GL_DEPTH_TEST);
    while (!Window::isShouldClose()) {
        int small_command = -1;
        if (!comm.empty() and  i == 100 and flag_razb) {
            small_command = comm.top();
            comm.pop();
            i = 0;
        }
        if (!command_sbor.empty() and  i == 10 and flag_sbor) {
            small_command = command_sbor.top();
            command_sbor.pop();
            i = 0;
        }
        float currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;
        if (Events::jpressed(GLFW_KEY_ESCAPE)){
            Window::setShouldClose(true);
        }
        if (Events::jpressed(GLFW_KEY_TAB)){
            Events::toogleCursor();
        }
        if (Events::jclicked(GLFW_MOUSE_BUTTON_1)){
            if (!flag_click) {
                glClearColor(1.0f,1.0f,1.0f,1);
                flag_click = true;
            } else {
                glClearColor(0.0f,0.0f,0.0f,1);
                flag_click = false;
            }
        }
        if (Events::pressed(GLFW_KEY_W)){
            camera->position += camera->front * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_S)){
            camera->position -= camera->front * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_D)){
            camera->position += camera->right * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_A)){
            camera->position -= camera->right * delta * speed;
        }
        if ((Events::jpressed(GLFW_KEY_UP) && Events::pressed(GLFW_KEY_1)) || small_command  == 0) {
            a.rotate_up(0);
            if (!flag_sbor) {
                for (int i = 0; i < 3; i++) {
                    command_sbor.push(0);
                }
            }

        }
        if ((Events::jpressed(GLFW_KEY_UP) && Events::pressed(GLFW_KEY_3))  || small_command  == 1) {
            a.rotate_up(2);
            if (!flag_sbor) {
                for (int i = 0; i < 3; i++) {
                    command_sbor.push(1);
                }
            }

        }
        if ((Events::jpressed(GLFW_KEY_RIGHT) && Events::pressed(GLFW_KEY_1)) || small_command  == 2)   {
            a.rotate_right(0);
            if (!flag_sbor) {
                for (int j = 0; j < 3; j++) {
                    command_sbor.push(2);
                }
            }

        }
        if ((Events::jpressed(GLFW_KEY_RIGHT) && Events::pressed(GLFW_KEY_3)) || small_command  == 3) {
            a.rotate_right(2);
            if (!flag_sbor) {
                for (int j = 0; j < 3; j++) {
                    command_sbor.push(3);
                }
            }

        }
        if ((Events::jpressed(GLFW_KEY_X) && Events::pressed(GLFW_KEY_1)) || small_command  == 4) {
            a.rotate_front(0);
            if (!flag_sbor) {
                for (int j = 0; j < 3; j++) {
                    command_sbor.push(4);
                }
            }
        }
        if ((Events::jpressed(GLFW_KEY_X) && Events::pressed(GLFW_KEY_3)) || small_command  == 5) {
            a.rotate_front(2);
            if (!flag_sbor) {
                for (int j = 0; j < 3; j++) {
                    command_sbor.push(5);
                }
            }

        }
        if (Events::jpressed(GLFW_KEY_F)) {
            flag_sbor = false;
            flag_razb = true;
            i = 99;
        }
        if (Events::jpressed(GLFW_KEY_E)) {
            flag_razb = false;
            flag_sbor = true;
            i = 9;
        }
        if (command_sbor.size() == 0) {
            flag_sbor = false;
        }
        if (Events::_cursor_locked){
            camY += -Events::deltaY / Window::height * 2;
            camX += -Events::deltaX / Window::height * 2;

            if (camY < -radians(89.0f)){
                camY = -radians(89.0f);
            }
            if (camY > radians(89.0f)){
                camY = radians(89.0f);
            }

            camera->rotation = mat4(1.0f);
            camera->rotate(camY, camX, 0);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->use();
        shader->uniformMatrix("projview", camera->getProjection()*camera->getView());
        a.draw(shader);
        Window::swapBuffers();
        Events::pullEvents();
        i ++;
    }
    delete shader;
    Window::terminate();
    return 0;
}
