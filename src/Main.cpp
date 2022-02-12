#include "VigenereCrypto/Input/Input.hpp"
#include "VigenereCrypto/Encryption/Encryption.hpp"
#include "Analysis/Analysis.hpp"

#include <cassert>
#include <fstream>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    
    Input _input_text;
    Input _input_key;
    Encryption _encryption;
    // //Capture the text
    // _input_text.captureInput(">>> ENTER YOUR TEXT : ");

    _input_text.setInput("During this last day, however, little by little the gangways were cleared, the scaffoldings were taken down, the fly-wheel cranes disappeared, the fixing of the engines was accomplished, the last screws and nails were driven in, the reservoirs filled with oil, and the last slab rested on its metal mortise. This day the chief engineer tried the boilers.");
    
    _input_text.transformInput();
    // std::cout <<"Your initial message after transformation is : " << _input_text.getInput(true) << std::endl;

    // // //Catpure the key
    _input_key.captureInput(">>> ENTER YOUR KEY : ");
    _input_key.transformInput();
    // std::cout <<"Your key after transformation is : " << _input_key.getInput(true) << std::endl;

    // // //Encrypt text
    _encryption.VigenereEncryption(_input_text.getInput(true), _input_key.getInput(true));
    std::cout << "Your message encrypted is : " << _encryption.getEncrypted() << std::endl;

    // //Decrypt text
    // _encryption.VigenereDecryption(_input_key.getInput(true));
    // std::cout << "Your message decrypted is : " << _encryption.getDecrypted() << std::endl;

    // // Analysis _analysis(_encryption.getEncrypted());
    // Analysis _analysis("abcdefghijklmnopqrstuvwxyzabcdmnoabc");
    // Analysis _analysis("segelazewaopqjlnkfapzajyuyhklazeacnwpqepaaynepaykklanwperaiajp");
    // Analysis _analysis("duringthislastdayhoweverlittlebylittlethegangwayswereclearedthescaffoldingsweretakendowntheflywheelcranesdisappearedthefixingoftheengineswasaccomplishedthelastscrewsandnailsweredriveninthereservoirsfilledwithoilandthelastslabrestedonitsmetalmortisethisdaythechiefengineertriedtheboilers");

    Analysis _analysis(_encryption.getEncrypted());

    // Calculate all occurences by sequences of 3 or more letters
    _analysis.calculateOccurences();

    _analysis.calculateKeylength();
    _analysis.friedmanTest();

    std::string choice;
    std::cout << "Choose your key length :\n1 - Key divisor method\n2 - Key Friedman test" << std::endl;
    std::cin >> choice;

    int key_length(0);

    if(choice == "1")
    {
        key_length = _analysis.getKeyLenght(DIVISOR_KEY);
    }
    else
    {
        key_length = _analysis.getKeyLenght(FRIEDMAN_KEY);
    }

    std::string key = _analysis.frequencyAnalysis(key_length);

    _encryption.VigenereDecryption(key);
    // std::cout << "Your message decrypted is : " << _encryption.getDecrypted() << std::endl;

    if(_input_text.getInput(true) == _encryption.getDecrypted())
    {
        std::cout << "CONGRATS ! YOU HACKED THE TEXT !" << std::endl;
    }
    
    return EXIT_SUCCESS;
}