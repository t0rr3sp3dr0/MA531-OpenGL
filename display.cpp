//
// Created by lvrma on 05/07/16.
//

#include "display.h"
#include <iostream>
#include <GL/glew.h>

using namespace std;

Display::Display(int width, int height, const string& title) {

    m_width = width;
    m_height = height;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 8 bits allocated, or 2^8 shades of RED
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 2^8 = 256, good number if you don't know what to pick
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // since 256 shades is the limit of the human eye
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Transparency
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // Because there are possibly 32 bits of color above
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Allocate a separate block of memory

    // GL Context Flow:
    // SDL requests Window from Operating System
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    // OpenGL contacts the GPU and gives it autonomy over the Window
    // as if the Operating System outsourced the Window to the GPU
    // Now we can draw in the Window using the GPU, through OpenGL
    m_glContext = SDL_GL_CreateContext(m_window);

    // GLEW searches the system for supported OpenGL windows
    GLenum status = glewInit();

    if(status != GLEW_OK){
        cerr << "GLEW failed to initialize" << endl;
    }

    isClosed = false;

}

Display::~Display() {
    //Try to delete components in the reverse order they were created
    // Imagine a layer analogy, to avoid bugs removing the upper and not the lower
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::SwapBuffers(){
    // With 2 buffers, one allocates for the Window, the other for OpenGL
    // While OpenGL draws in one space, the Window displays the other
    // Then we Swap Buffers and display the just drawn while OpenGL draws on the other
    // That way things are way more fluid.
    // Something that's still being drawn is never shown.
    SDL_GL_SwapWindow(m_window);


    // Still, the Operating System is still sending Window Events,
    // so we need to somehow warn it, otherwise it will think
    // the program isn't responding, and generate a bug.
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT)
            isClosed = true;
    }
}

// Paint
void Display::Clear(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Event Handling getter
bool Display::IsClosed(){
    return isClosed;
}