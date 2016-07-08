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

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 8 bits alocados, ou 2^8 tons de vermelho possiveis
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 2^8 = 256, um bom número já que 256 tons é +- o limite do olho humano
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Transparência
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // Tamanho do buffer = 32 porque acima se foi acumulado 32 bits do RGBA
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Alocando um bloco separado de memória para o double buffering

    // Usando o SDL para solicitar uma janela do sistema operacional
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    // OpenGL dá autonomia sobre a janela para a GPU, como se o OS tivesse feito uma terceirização da janela para a GPU
    // Agora podemos desenhar na janela
    m_glContext = SDL_GL_CreateContext(m_window);

    // GLEW procura no sistema janelas suportadas
    GLenum status = glewInit();

    if(status != GLEW_OK){
        cerr << "GLEW nao pode ser inicializado" << endl;
    }

    isClosed = false;

}

Display::~Display() {
    // Tentar sempre deletar os elementos na ordem inversa que foram criados
    // Tentar fazer uma analogia com camadas, para não ter erros removendo a externa e deixando a interna
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::SwapBuffers(){
    // Com 2 buffers, um está alocado para a janela e o outro para o openGL
    // Enquanto o openGL desenha em um, a janela mostra o outro.
    // Assim, algo que está ainda sendo desenhado nunca é mostrado, deixando tudo mais fluido.
    SDL_GL_SwapWindow(m_window);


    // Mas o OS ainda está mandando Window Events, então precisamos avisá-lo que a GPU está no controle
    // Caso contrário ele pensará que o programa parou de responder, e tentar encerrá-lo
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT)
            isClosed = true;
    }
}

// Limpar e redesenhar
void Display::Clear(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Apenas event handling para o OS
bool Display::IsClosed(){
    return isClosed;
}