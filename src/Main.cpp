#include "VigenereCrypto/Input/Input.hpp"
#include "VigenereCrypto/Encryption/Encryption.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Input _input_text;
    Input _input_key;
    Encryption _encryption;

    //Capture the text
    _input_text.captureInput(">>> ENTER YOUR TEXT : ");
    // std::cout << _input_text.getInput() << std::endl;
    _input_text.transformInput();
    std::cout <<"Your initial message after transformation is : " << _input_text.getInput() << std::endl;

    //Catpure the key
    _input_key.captureInput(">>> ENTER YOUR KEY : ");
    // std::cout << _input_key.getInput() << std::endl;
    _input_key.transformInput();
    std::cout <<"Your key after transformation is : " << _input_key.getInput() << std::endl;

    _encryption.VigenereEncryption(_input_text.getInput(), _input_key.getInput());

    std::cout << "Your message encrypted is : " << _encryption.getEncrypted() << std::endl;
    
    return EXIT_SUCCESS;

}