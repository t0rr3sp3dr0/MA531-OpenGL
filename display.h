//
// Created by lvrma on 05/07/16.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display {
    public:
        Display(int width, int height, const std::string& title);
        void SwapBuffers();
        bool IsClosed(); // Event Handling
        void Clear(float r, float g, float b, float a); // Red, green, blue, alpha
        virtual ~Display();

        int getWidth() const { return m_width; }
        void setWidth(int width) { Display::m_width = width; }
        int getHeight() const { return m_height; }
        void setHeight(int height) { Display::m_height = height; }

    protected:
    private:
        Display(const Display& other){}
        void operator=(const Display& other){}

        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool isClosed;

        int m_width;
        int m_height;
};

#endif // DISPLAY_H