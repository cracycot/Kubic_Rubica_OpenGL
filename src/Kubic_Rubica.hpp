//
// Created by Kirill Lesniak on 08.04.2024.
//
#include "iostream"
#include "vector"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "graphics/Shader.h"
#include "iostream"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "window/window.h"
#include "window/events.h"
#include "graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "window/camera.h"

static GLfloat vertices[] =  {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1, 0, 0,
                                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1, 0, 0,
                                0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1, 0, 0,
                                0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1, 0, 0,
                                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1, 0, 0,
                                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1, 0, 0,


                                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0, 1, 0,
                                0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0, 1, 0,
                                0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0, 1, 0,
                                0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0, 1, 0,
                                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0, 1, 0,
                                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0, 1, 0,

                                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0, 0, 1,
                                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0, 0, 1,
                                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0, 0, 1,
                                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0, 0, 1,
                                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0, 0, 1,
                                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0, 0, 1,


                                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.25f, 0.5f, 1,
                                0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.25f, 0.5f, 1,
                                0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.25f, 0.5f, 1,
                                0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.25f, 0.5f, 1,
                                0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.25f, 0.5f, 1,
                                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.25f, 0.5f, 1,

                                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.52f, 0, 1,
                                0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.52f, 0, 1,
                                0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.52f, 0, 1,
                                0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.52f, 0, 1,
                                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.52f, 0, 1,
                                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.52f, 0, 1,

                                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1, 0.155f, 1,
                                0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1, 0.155f, 1,
                                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1, 0.155f, 1,
                                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1, 0.155f, 1,
                                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1, 0.155f, 1,
                                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1, 0.155f, 1,
};
class Kubic {

    glm::vec3 offset;
    glm::vec3 vec_x = {1.0f ,0.0f,0.0f};
    glm::vec3 vec_y = {0.0f,1.0f,0.0f};
    glm::vec3 vec_z = {0.0f, 0.0f, 1.0f};
    glm::mat3 norm;
    glm::mat4 model;
    GLuint VAO, VBO;
    int number = 0;
    void initialize() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

public:
    void draw() {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
    void setOffset(const vec3 &offset) {
        Kubic::offset = offset;
    }

    const vec3 &getOffset() const {
        return offset;
    }

    const mat3 &getNorm() const {
        return norm;
    }

    const mat4 &getModel() const {
        return model;
    }

    void setNorm(const mat3 &norm) {
        Kubic::norm = norm;
    }

    void setModel(const mat4 &model) {
        Kubic::model = model;
    }
public:
    Kubic() {
        model = glm::mat4 (1.0f);
        initialize();
    }
    int get_numb() {
        return number;
    }
    void set_numb(int num) {
        number = num;
    }
    void del_Kubic() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    const GLuint *const getVao() const {
        return &VAO;
    }

    const GLuint *const getVbo() const {
        return &VBO;
    }

    Kubic(glm::vec3 off) {
        offset = off;
        model = glm::mat4 (1.0f);
        model = glm::translate(model, offset);
        initialize();
    }
    void rotate(glm::vec3 rotate) {
        model = glm::rotate(model, radians(1.0f), glm::mat3(vec_x, vec_y, vec_z)*rotate);
    }
    void set_norm_up() {
        glm::vec3 buf = vec_y;
        vec_y = -vec_z;
        vec_z = buf;
    }
    void set_norm_front() {
        glm::vec3 buf = vec_x;
        vec_x = vec_z;
        vec_z = -buf;
    }
    void set_norm_right() {
        glm::vec3 buf = vec_y;
        vec_y = vec_x;
        vec_x = -buf;
    }
    void move(glm::vec3 rotate) {
        model = glm::translate(model, rotate);
    }


};
class Kubic_Rubica {
    std::vector<std::vector<std::vector<Kubic>>> vertices;
    Shader * shader;
    void rotateMatrixUp(std::vector<std::vector<Kubic>>& matrix) {
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n/2; j++) {
                std::swap(matrix[i][j], matrix[i][n-j-1]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
    void rotateMatrixRight(std::vector<std::vector<std::vector<Kubic>>> & matrix, int z) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n/2; j++) {
                std::swap(matrix[i][j][z], matrix[i][n-j-1][z]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                std::swap(matrix[i][j][z], matrix[j][i][z]);
            }
        }

    }
    void rotateMatrixFront(std::vector<std::vector<std::vector<Kubic>>> &  matrix, int y) {
        int n = matrix.size();


        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                std::swap(matrix[i][y][j], matrix[j][y][i]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n/2; j++) {
                std::swap(matrix[i][y][j], matrix[i][y][n-j-1]);
            }
        }
    }

public:
    Kubic_Rubica() {
        for (int x = -1; x < 2; x++) {
            std::vector<std::vector<Kubic>> a1;
            for (int y = -1; y < 2; y++) {
                std::vector<Kubic> a2;
                for (int z = -1; z < 2; z++) {
                    a2.emplace_back(glm::vec3(x , y , z ));
                }
                a1.push_back(a2);
            }
            vertices.push_back(a1);
        }
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    vertices[x][y][z].set_numb(x*9 + y*3 + z);
                }
            }
        }
    }
    ~Kubic_Rubica() {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    vertices[x][y][z].del_Kubic();
                }
            }
        }
    }
    void draw(Shader * shader) {
        this->shader = shader;
        for (int x = 0; x < 3; x ++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    shader->uniformMatrix("model", vertices[x][y][z].getModel());
                    vertices[x][y][z].draw();
                }
            }
        }
    }
    void rotate_front(int y) {
        for (int i = 0; i < 90; i ++) {
            for (int z = 0; z < 3; z++) {
                for (int x = 0; x <  3; x++) {
                    glm::vec3 off = vertices[x][y][z].getOffset();
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(0,1, 0));
                    vertices[x][y][z].move(off);
                    //*glm::vec3(1, 0,0)

                }
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            draw(shader);
            Window::swapBuffers();
        }
        for (int z = 0; z < 3; z++) {
            for (int x = 0; x < 3; x++) {
                vertices[x][y][z].set_norm_front();
                //*glm::vec3(1, 0,0)

            }
        }
        rotateMatrixFront(vertices, y);
    }
    void rotate_up(int x) {
        for (int i = 0; i < 90; i ++) {
            for (int z = 0; z < 3; z++) {
                for (int y = 0; y < 3; y++) {
                    glm::vec3 off = vertices[x][y][z].getOffset();
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(1,0, 0));
                    vertices[x][y][z].move(off);
                    //*glm::vec3(1, 0,0)

                }
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            draw(shader);
            Window::swapBuffers();
        }
        for (int z = 0; z < 3; z++) {
            for (int y = 0; y < 3; y++) {
                vertices[x][y][z].set_norm_up();
                //*glm::vec3(1, 0,0)

            }
        }
        rotateMatrixUp(vertices[x]);
        //vertices[z] =  rotateMatrix(vertices[z]);
    }
    void rotate_right(int z) {
        for (int i = 0; i < 90; i ++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    glm::vec3 off = vertices[x][y][z].getOffset();
                    vertices[x][y][z].move(-off);
                    vertices[x][y][z].rotate(glm::vec3(0, 0, 1));
                    vertices[x][y][z].move(off);

                    //*glm::vec3(1, 0,0)

                }
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            draw(shader);
            Window::swapBuffers();
        }
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                vertices[x][y][z].set_norm_right();
                //*glm::vec3(1, 0,0)

            }
        }

        rotateMatrixRight(vertices, z);

    }

};