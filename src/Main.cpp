#include "VigenereCrypto/Input/Input.hpp"
#include "VigenereCrypto/Encryption/Encryption.hpp"
#include "BabageKasiki/Analysis.hpp"

#include "Graphics/Graphics.hpp"

#include <cassert>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Input _input_text;
    Input _input_key;
    Encryption _encryption;

    // //Capture the text
    // _input_text.captureInput(">>> ENTER YOUR TEXT : ");
    // _input_text.transformInput();
    // std::cout <<"Your initial message after transformation is : " << _input_text.getInput(true) << std::endl;

    // //Catpure the key
    // _input_key.captureInput(">>> ENTER YOUR KEY : ");
    // _input_key.transformInput();
    // std::cout <<"Your key after transformation is : " << _input_key.getInput() << std::endl;

    // //Encrypt text
    // _encryption.VigenereEncryption(_input_text.getInput(), _input_key.getInput());
    // std::cout << "Your message encrypted is : " << _encryption.getEncrypted() << std::endl;

    // //Decrypt text
    // _encryption.VigenereDecryption(_input_key.getInput());
    // std::cout << "Your message decrypted is : " << _encryption.getDecrypted() << std::endl;

    // Analysis _analysis(_encryption.getEncrypted());
    // Analysis _analysis("abcdefghijklmnopqrstuvwxyzabcdmnoabc");

    // //Calculate all occurences by sequences of 3 or more letters
    // _analysis.calculateOccurences();

    Graphics _graphic(1280, 800);
    assert(_graphic.initializeAll());


    bool terminate = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    static char buf_text[64] = "\0";
    static char buf_key[64] = "\0";

    std::string error_msg = "";

    while(!terminate)
    {
        //manage window closing
        _graphic.windowProcess(terminate);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(20, _graphic.getHeight()/2 - 100));
        ImGui::SetNextWindowSize(ImVec2(350, 130));

        ImGui::Begin("User input", NULL, window_flags);
        if(ImGui::InputTextWithHint("Text", "Enter your text ...", buf_text, IM_ARRAYSIZE(buf_text)))
        {
            _input_text.setInput(buf_text);
            _input_text.transformInput();
            std::cout <<"Your initial message after transformation is : " << _input_text.getInput(true) << std::endl;
        }

        if(ImGui::InputTextWithHint("Key", "Enter your key ...", buf_key, IM_ARRAYSIZE(buf_key)))
        {
            _input_key.setInput(buf_key);
            _input_key.transformInput();
            std::cout <<"Your key after transformation is : " << _input_key.getInput(true) << std::endl;
        }

        if(ImGui::Button("Encrypt !"))
        {
            if((strcmp(buf_text, "\0") != 0) && (strcmp(buf_key, "\0") != 0))
            {
                error_msg.clear();
                _encryption.VigenereEncryption(_input_text.getInput(true), _input_key.getInput(true));
                std::cout << "Your message encrypted is : " << _encryption.getEncrypted() << std::endl;
            }
            else
            {
                error_msg = (strcmp(buf_text, "\0") == 0) ? "Text missing !" : "Key missing !";
            }

        }

        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), error_msg.c_str());

        ImGui::End();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(_graphic.getWindow());

    }
    
    return EXIT_SUCCESS;

}