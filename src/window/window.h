//
// Created by Kirill Lesniak on 25.02.2024.
//


#ifndef LAB8_WINDOW_H
#define LAB8_WINDOW_H

class GLFWwindow;

class Window {

public:
    static int width;
    static int height;
    static GLFWwindow* window;
    static int initialize(int width, int height, const char * title);
    static bool isShouldClose();
    static void swapBuffers();
    static void setCursorMode(int mode);
    static void setShouldClose(bool flag  );
    static void terminate();
};

#endif //LAB8_WINDOW_H
