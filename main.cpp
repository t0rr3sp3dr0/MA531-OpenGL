//
// Created by lvrma on 05/07/16.
//

#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"

using namespace std;

int main() {
    Display display(1920,1080,"AVLC");
    Shader shader("basicShader");
    Texture texture("cin.png");
    Transform transform;
    // 70 degrees is the approx. FoV of the human eye
    Camera camera(glm::vec3(0,0,-2), 70.f, (float)display.getWidth()/(float)display.getHeight(), 0.01f, 1000.0f);
    Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
                          Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5,1.0)),
                          Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0,0.0))};

    float counter = 0.0f;

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

    while(!display.IsClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f); // Paint on screen

        transform.GetPos().x = sinf(counter);
        transform.GetRot().x = counter * 2;
        transform.GetRot().y = counter * 2;
        transform.GetRot().z = counter * 2;
        transform.SetScale(glm::vec3(abs(sinf(counter)),abs(sinf(counter)),abs(sinf(counter))));

        shader.Update(transform, camera);               // Inform the transform to be multiplied, otherwise it will be null
        shader.Bind();
        mesh.Draw();

        display.SwapBuffers();                  // Swap the buffer

        counter += 0.0001f;
    }

    return 0;
}