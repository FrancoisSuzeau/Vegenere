#include "VigenereCrypto/Input/Input.hpp"
#include "VigenereCrypto/Encryption/Encryption.hpp"
#include "BabageKasiki/Analysis.hpp"

#include "Graphics/Graphics.hpp"

#include <cassert>
#include <fstream>

void makeItPrompt()
{
    // Input _input_text;
    // Input _input_key;
    // Encryption _encryption;
    // //Capture the text
    // _input_text.captureInput(">>> ENTER YOUR TEXT : ");
    // _input_text.transformInput();
    // std::cout <<"Your initial message after transformation is : " << _input_text.getInput(true) << std::endl;

    // //Catpure the key
    // _input_key.captureInput(">>> ENTER YOUR KEY : ");
    // _input_key.transformInput();
    // std::cout <<"Your key after transformation is : " << _input_key.getInput(true) << std::endl;

    // //Encrypt text
    // _encryption.VigenereEncryption(_input_text.getInput(true), _input_key.getInput(true));
    // std::cout << "Your message encrypted is : " << _encryption.getEncrypted() << std::endl;

    // //Decrypt text
    // _encryption.VigenereDecryption(_input_key.getInput(true));
    // std::cout << "Your message decrypted is : " << _encryption.getDecrypted() << std::endl;

    // // Analysis _analysis(_encryption.getEncrypted());
    Analysis _analysis("abcdefghijklmnopqrstuvwxyzabcdmnoabc");

    // Calculate all occurences by sequences of 3 or more letters
    _analysis.calculateOccurences();
    _analysis.calculateKeylength();
}

void makeItGraphical()
{
    std::ofstream flux("imgui.ini");
    if(flux)
    {
        flux.close();
        system("del imgui.ini");
    }

    Input _input_text;
    Input _input_key;
    Encryption _encryption;
    Analysis _analysis;
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
    bool open_Vigenere_window = false;
    bool do_analysis = false;

    while(!terminate)
    {
        //manage window closing
        _graphic.windowProcess(terminate);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(20, _graphic.getHeight()/2 - 100));
        ImGui::SetNextWindowSize(ImVec2(350, 120));

        ImGui::Begin("User input", NULL, window_flags);
        if(ImGui::InputTextWithHint("Text", "Enter your text ...", buf_text, IM_ARRAYSIZE(buf_text)))
        {
            _input_text.setInput(buf_text);
            _input_text.transformInput();

            //! delete before merging
            // std::cout <<"Your initial message after transformation is : " << _input_text.getInput(true) << std::endl;
        }

        if(ImGui::InputTextWithHint("Key", "Enter your key ...", buf_key, IM_ARRAYSIZE(buf_key)))
        {
            _input_key.setInput(buf_key);
            _input_key.transformInput();

            //! delete before merging
            // std::cout <<"Your key after transformation is : " << _input_key.getInput(true) << std::endl;
        }

        if(ImGui::Button("Encrypt !"))
        {
            if((strcmp(buf_text, "\0") != 0) && (strcmp(buf_key, "\0") != 0))
            {
                error_msg.clear();
                _encryption.VigenereEncryption(_input_text.getInput(true), _input_key.getInput(true));
                _encryption.VigenereDecryption(_input_key.getInput(true));

                open_Vigenere_window = true;
                do_analysis = true;
            }
            else
            {
                error_msg = (strcmp(buf_text, "\0") == 0) ? "Text missing !" : "Key missing !";
                open_Vigenere_window = false;
                do_analysis = false;
            }

        }

        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), error_msg.c_str());
        ImGui::End();

        if(open_Vigenere_window)
        {
            _graphic.renderVegenere(_encryption.getEncrypted(), _encryption.getDecrypted(), &open_Vigenere_window);
            _analysis.setCypherText("abcdefghijklmnopqrstuvwxyzabcdmnoabcabcefgghixyzuvwvwx");
            if(do_analysis)
            {
                _analysis.calculateOccurences();
                do_analysis = false;
                _graphic.setExtract(false);
                _analysis.calculateKeylength();
            }

            _graphic.renderAnalysis(_analysis, &open_Vigenere_window);
        }

        

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(_graphic.getWindow());



    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // std::string choice("none");

    // std::cout << ">> You have the possibility to work graphicaly or with your terminal.\n>> Note that the graphical way only work on windows systems." << std::endl;

    // do
    // {
    //     std::cout << ">> Select your choice :\n- 1 : Graphical\n- 2 : With a terminal" << std::endl;
    //     choice.clear();
    //     std::cin >> choice;

    // } while ((choice != "1") && (choice != "2"));
    
    // if(choice == "1")
    // {
    //     makeItGraphical();
    // }
    // else
    // {
    //     makeItPrompt();
    // }

    // makeItGraphical();
    makeItPrompt();
    
    return EXIT_SUCCESS;
}