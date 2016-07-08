//
// Created by lvrma on 05/07/16.
//

#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

using namespace std;

int main() {
    Display display(800,600,"AVLC");
    Shader shader("basicShader");
    Texture texture("cin.png");
    Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
                          Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5,1.0)),
                          Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0,0.0))};

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));


    while(!display.IsClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f); // Paint on screen

        shader.Bind();
        mesh.Draw();

        display.SwapBuffers();                  // Swap the buffer
    }

    return 0;
}