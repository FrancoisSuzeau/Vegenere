/*  Author : SUZEAU François

    Creation : 03/02/2022

    Purpose : Module for graphic representation
*/

#ifndef GRAPHIC_H
#define GRAPHIC_H

    #include <iostream>
    
    #include "../lib/imgui/imgui.h"
    #include "../lib/imgui/imgui_impl_sdl.h"
    #include "../lib/imgui/imgui_impl_opengl3.h"
    #include <SDL2/SDL.h>
    #if defined(IMGUI_IMPL_OPENGL_ES2)
    #include <SDL_opengles2.h>
    #else
    #include <SDL2/SDL_opengl.h>
    #endif
    

    class Graphics {


        private:

            int     m_window_w;
            int     m_window_h;

            SDL_Window  *m_window;
            SDL_GLContext gl_context;

            void renderCypher(std::string encrypt, std::string decrypt);

        public:

            Graphics(int width, int height);
            ~Graphics();

            bool initializeAll();

            void windowProcess(bool &terminate);

            void renderVegenere(std::string encrypt, std::string decrypt);

            SDL_Window *getWindow() const;
            int getWidth() const;
            int getHeight() const;
    };

#endif