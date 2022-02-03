#include "VigenereCrypto/Input/Input.hpp"
#include "VigenereCrypto/Encryption/Encryption.hpp"
#include "BabageKasiki/Analysis.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // Input _input_text;
    // Input _input_key;
    // Encryption _encryption;

    // //Capture the text
    // _input_text.captureInput(">>> ENTER YOUR TEXT : ");
    // _input_text.transformInput();
    // std::cout <<"Your initial message after transformation is : " << _input_text.getInput() << std::endl;

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
    Analysis _analysis("abcdefghijklmnopqrstuvwxyzabcdmnoabc");

    //Calculate all occurences by sequences of 3 or more letters
    _analysis.calculateOccurences();

    
    return EXIT_SUCCESS;

}