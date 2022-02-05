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
    array_hist = nullptr;
    already_extract = false;
}

Graphics::~Graphics()
{
    if(array_hist != nullptr)
    {
        free(array_hist);
    }

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
/************************************************************************* renderVegenere ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Graphics::renderVegenere(std::string encrypt, std::string decrypt, bool *open)
{
    ImGui::SetNextWindowPos(ImVec2(m_window_w/2, 40));
    ImGui::SetNextWindowSize(ImVec2(50 *encrypt.size(), 80));

    ImGui::Begin("Cypher data", open);
    ImGui::BulletText("Your text encrypted : ");
    ImGui::SameLine(); ImGui::TextColored(ImVec4(50.0f/255.0f, 205.0f/255.0f, 50.0f/255.0f, 1.0f), encrypt.c_str());
    ImGui::BulletText("Your text decrypted : ");
    ImGui::SameLine(); ImGui::TextColored(ImVec4(30.0f/255.0f, 144.0f/255.0f, 1.0f, 1.0f), decrypt.c_str());
        
    ImGui::End();
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** renderAnalysis ********************************************************************************/
/***********************************************************************************************************************************************************************/
void Graphics::renderAnalysis(Analysis analysis, bool *open)
{
    // ImGui::SetNextWindowPos(ImVec2(m_window_w/2, m_window_h/2));
    ImGui::SetNextWindowPos(ImVec2(0,0));
    // ImGui::SetNextWindowSize(ImVec2(300, 150));

    ImGui::Begin("Analysis", open);
    if(already_extract == false)
    {
        // this->extractData(analysis.getCalculationTable());
        already_extract = true;
    }
    
    ImGui::PlotHistogram("", array_hist, IM_ARRAYSIZE(array_hist), 0, NULL, 0.0f, 1.0f, ImVec2(80, 80.0f));
    ImGui::End();
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** renderAnalysis ********************************************************************************/
/***********************************************************************************************************************************************************************/
void Graphics::extractData(std::map<std::string, sequence_calculate> datas)
{
    if(array_hist != nullptr)
    {
        free(array_hist);
    }

    array_hist = (float*) malloc(datas.size());
    assert(array_hist);
    
    int i(0);

    for(std::map<std::string, sequence_calculate>::iterator it = datas.begin(); it != datas.end(); it++)
    {
        array_hist[i] = (float) it->second.occurences / (float) datas.size();

        std::cout << it->second.occurences << std::endl;

        i++;
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

void Graphics::setExtract(bool const new_val)
{
    already_extract = new_val;
}