/*  Author : SUZEAU François

    Creation : 15/02/2022

    Purpose : Declaration of the Bazeries class
*/

#include "Bazeries.hpp"

/***********************************************************************************************************************************************************************/
/***************************************************************** Constructor and Destructor **************************************************************************/
/***********************************************************************************************************************************************************************/
Bazeries::Bazeries(std::string const cypher_text) : m_cypher_text(cypher_text)
{
    //we just create an hash to easily find the position of each letter in alphabet
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for(int i(0); i < (int) alphabet.size(); i++)
    {
        std::string letter = alphabet.substr(i, 1);
        map_position[letter] = i;
    }
}

Bazeries::~Bazeries()
{

}

/***********************************************************************************************************************************************************************/
/*********************************************************************** likelyWordAnalysis ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Bazeries::likelyWordAnalysis(int key_length)
{
    std::string word_choice;

    std::cout << "Choose your more likely word : " << std::endl;
    std::cin >> word_choice;

    while((int) word_choice.size() <= key_length)
    {
        std::cout << "Your word size need to be greater (strictly) than the key size !"  << std::endl;
        std::cout <<"Your word size : " << word_choice.size() << std::endl;
        std::cout <<"Key size : " << key_length << std::endl;

        std::cin >> word_choice;
    }

    bool terminate(false);

    std::string key;

    int position(0);
    
    while((!terminate) && (position < (int) (m_cypher_text.size() - word_choice.size())))
    {
        //here we encrypt the cypher text with the more likely word choose by the user
        key = this->likelyWordAtPos(word_choice, position);

        //we display the result
        std::cout << "We found at position " << position + 1 << " this substring :\n" << key << ".\nMay be your key is contained here ... " << std::endl;

        std::string choice;
        std::cout << "Do you want to continue ?\n(Choose 1 to stop)" << std::endl;
        std::cin >> choice;

        if(choice == "1")
        {
            terminate = true;
        }
        else
        {
            system("cls");
            key.clear();
        }

        position++;
    }

    std::cout << "There is the substring with the key containing in it (may you think ...) : " << key << std::endl;
}

/***********************************************************************************************************************************************************************/
/************************************************************************** likelyWordAtPos ****************************************************************************/
/***********************************************************************************************************************************************************************/
std::string Bazeries::likelyWordAtPos(std::string likely_word, int position)
{
    //in this function we browse all letter of a subdivision of the cypher text and we substract it with the letter of the likely word

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    std::string result;

    //the substring in cypher text at position and the size of the likely word 
    std::string crypted = m_cypher_text.substr(position, likely_word.size());

    //we take each letter one by one
    for(int i(0); i < (int) likely_word.size(); i++)
    {
        std::string a = crypted.substr(i, 1);
        std::string b = likely_word.substr(i, 1);
        
        //we find the position of the letter in alphabet by substract the letter in cypher text by the letter in likely word
        int index = this->calculateDistance(a, b);

        //we add this letter giving by the position in the alphabet
        result.append(alphabet.substr(index, 1));
    }

    return result;
}

/***********************************************************************************************************************************************************************/
/************************************************************************ calculateDistance ****************************************************************************/
/***********************************************************************************************************************************************************************/
int Bazeries::calculateDistance(std::string a, std::string b)
{
    //we recover the position of the letter in cypher text (a) and the position of the letter in likely word (b)
    int index_a = map_position[a];
    int index_b = map_position[b];

    int dist;

    //we calculate the distance between them
    if(index_b > index_a)
    {
        dist = 26 - (index_b - index_a);
    }
    else
    {
        dist = (index_a - index_b) % 26;
    }

    //and we return the position of the letter
    return dist;
}