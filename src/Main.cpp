#include "VigenereCrypto/Input/Input.hpp"
#include "VigenereCrypto/Encryption/Encryption.hpp"
#include "Analysis/Analysis.hpp"
#include "Analysis/Bazeries.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    
    Input _input_text;
    Input _input_key;
    Encryption _encryption;


    //Capture the text
    // _input_text.captureInput(">>> ENTER YOUR TEXT : ");

    //here if you want a random text in english (don't forget to comment the line above)
    // _input_text.setInput("During this last day, however, little by little the gangways were cleared, the scaffoldings were taken down, the fly-wheel cranes disappeared, the fixing of the engines was accomplished, the last screws and nails were driven in, the reservoirs filled with oil, and the last slab rested on its metal mortise. This day the chief engineer tried the boilers.");

    //here if you want a random text in french (don't forget to comment the lines above)
    _input_text.setInput("Internet n’est pas le seul réseau. Il existe un autre réseau plus performant. Je ne t’apprendrais rien en te disant qu’Internet a été crée par l’armée Américaine dans un but militaire. Internet n’était que le prototype. Un autre réseau a été créé pour les militaires. Complètement indépendant d’Internet. Tirant des leçons du premier réseau, le petit frère d’Internet est devenue un grand frère.");
    
    //remove or transform all special caractere in the text and transform it to lower case
    _input_text.transformInput();

    //Catpure the key
    _input_key.captureInput(">>> ENTER YOUR KEY : ");

    //remove or transform all special caractere in the key and transform it to lower case
    _input_key.transformInput();

    //Encrypt the text
    _encryption.VigenereEncryption(_input_text.getInput(true), _input_key.getInput(true));
    std::cout << "Your message encrypted is : " << _encryption.getEncrypted() << std::endl;

    //create an analysis object with the text encrypted as parameter that we will use in all our analysis
    Analysis _analysis(_encryption.getEncrypted());

    // Calculate all occurences by sequences of 3 or more letters
    _analysis.calculateOccurences();

    //calculate the key length with the most common divisor method
    _analysis.calculateKeylength();

    //calculate the key_length with friedman method
    _analysis.friedmanTest();

    //we let the choice to the user to select which key length was calculate by which method above
    std::string choice;
    std::cout << "Choose your key length :\n1 - Key divisor method\n2 - Key Friedman test" << std::endl;
    std::cin >> choice;

    int which_lenght = (choice == "1") ? DIVISOR_KEY : FRIEDMAN_KEY;
    int key_length = _analysis.getKeyLenght(which_lenght);

    //we do the frequency analysis with the key length previously selected
    std::string key = _analysis.frequencyAnalysis(key_length);

    //we decrypt the cypher text with possible key find with the frequency method
    _encryption.VigenereDecryption(key);

    //and finaly we see if you are a reel hacker
    if(_input_text.getInput(true) == _encryption.getDecrypted())
    {
        std::cout << "CONGRATS ! YOU HACKED THE TEXT !" << std::endl;
        std::cout << std::endl;
        std::cout << "Your reward will come soon ... " << std::endl;
        std::cout << std::endl;
        std::cout << ">> You are gonna be RICK ROLLED !" << std::endl;
        system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");
        std::cout << std::endl;
    }

    Bazeries _bazeries_analyst(_encryption.getEncrypted());

    //if you want to use this exemple : https://www.apprendre-en-ligne.net/crypto/vigenere/motprobvig.html
    // Bazeries _bazeries_analyst("bilkopffgmltwoewjcfdshkwonkseovusgrlwhgwfnvkwgggfnrfhyjvsgrfriekdccgbhrysxvkdijahcffgyefsgzwg");

    _bazeries_analyst.likelyWordAnalysis(key_length);
    
    return EXIT_SUCCESS;
}