/*  Author : SUZEAU François

    Creation : 03/02/2022

    Purpose : Declaration of the Graphics class
*/

#include "Graphics.hpp"

/***********************************************************************************************************************************************************************/
/***************************************************************** Constructor and Destructor **************************************************************************/
/***********************************************************************************************************************************************************************/
Graphics::Graphics(int width, int height) : m_window_w(width), m_window_h(height)
{

}

Graphics::~Graphics()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();

}

/***********************************************************************************************************************************************************************/
/*************************************************************************** initializeAll *****************************************************************************/
/***********************************************************************************************************************************************************************/
bool Graphics::initializeAll()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << ">> Initialise SDL : ERROR : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialise SDL : SUCCESS" << std::endl;

    //openGL version
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0)
    {
        std::cout << ">> Set GL attribute ERROR : MAJOR VERSION " << SDL_GetError() << std::endl;
    }
    
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) < 0)
    {
        std::cout << ">> Set GL attribute ERROR : MINOR VERSION " << SDL_GetError() << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    m_window = SDL_CreateWindow("TP Vegenere", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_w, m_window_h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(m_window == NULL)
    {
        std::cout << ">> Creating window : ERROR : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating window : SUCCESS" << std::endl;

    gl_context = SDL_GL_CreateContext(m_window);
    if(gl_context == 0)
    {
        std::cout << ">> Creating context OpenGL : ERROR : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating context OpenGL : SUCCESS" << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(m_window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");


    return true;
}

/***********************************************************************************************************************************************************************/
/*************************************************************************** windowProcess *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Graphics::windowProcess(bool &terminate)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            terminate = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window))
            terminate = true;
        }
}

/***********************************************************************************************************************************************************************/
/************************************************************************* getters/setters *****************************************************************************/
/***********************************************************************************************************************************************************************/
SDL_Window* Graphics::getWindow() const
{
    return m_window;
}

int Graphics::getWidth() const
{
    return m_window_w;
}

int Graphics::getHeight() const
{
    return m_window_h;
}