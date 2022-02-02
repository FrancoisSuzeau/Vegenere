#include "VigenereCrypto/Input/Input.hpp"



int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Input _input;
    _input.captureInput();
    std::cout << _input.getInput() << std::endl;
    _input.transformInput();
    std::cout << _input.getInput() << std::endl;
    
    return EXIT_SUCCESS;

}