/*  Author : SUZEAU François

    Creation : 02/02/2022

    Purpose : Declaration of the Encryption class
*/

#include "Encryption.hpp"

/***********************************************************************************************************************************************************************/
/***************************************************************** Constructor and Destructor **************************************************************************/
/***********************************************************************************************************************************************************************/
Encryption::Encryption()
{
    alphabetic_code['a'] = 0;
    alphabetic_code['b'] = 1;
    alphabetic_code['c'] = 2;
    alphabetic_code['d'] = 3;
    alphabetic_code['e'] = 4;
    alphabetic_code['f'] = 5;
    alphabetic_code['g'] = 6;
    alphabetic_code['h'] = 7;
    alphabetic_code['i'] = 8;
    alphabetic_code['j'] = 9;
    alphabetic_code['k'] = 10;
    alphabetic_code['l'] = 11;
    alphabetic_code['m'] = 12;
    alphabetic_code['n'] = 13;
    alphabetic_code['o'] = 14;
    alphabetic_code['p'] = 15;
    alphabetic_code['q'] = 16;
    alphabetic_code['r'] = 17;
    alphabetic_code['s'] = 18;
    alphabetic_code['t'] = 19;
    alphabetic_code['u'] = 20;
    alphabetic_code['v'] = 21;
    alphabetic_code['w'] = 22;
    alphabetic_code['x'] = 23;
    alphabetic_code['y'] = 24;
    alphabetic_code['z'] = 25;
}

Encryption::~Encryption()
{

}

/***********************************************************************************************************************************************************************/
/************************************************************************* setTransformLetter **************************************************************************/
/***********************************************************************************************************************************************************************/
char Encryption::transformLetter(const char m, const char b)
{
    unsigned int code = (alphabetic_code[m] + alphabetic_code[b]) % 26;
    char n = '\0';
    for(std::map<const char, unsigned int>::iterator it = alphabetic_code.begin(); it != alphabetic_code.end(); it++)
    {
        if(it->second == code)
        {
            n = it->first;   
        }
    }

    return n;
}

/***********************************************************************************************************************************************************************/
/************************************************************************* VigenereEncryption **************************************************************************/
/***********************************************************************************************************************************************************************/
void Encryption::VigenereEncryption(std::string text, std::string key)
{
    // std::cout << "size text : " << text.size() << std::endl;
    // std::cout << "size key : " << key.size() << std::endl;

    int i(0);
    int j(0);

    for(std::string::iterator it = text.begin(); it != text.end(); it++)
    {

        if(j >= (int) key.size())
        {
            j = 0;
        }

        // std::cout << "text : " << *it << " at i : " << i << std::endl;
        // std::cout << "key : " << key.at(j) << " at j : " << j << std::endl;

        text_encrypted.push_back(this->transformLetter(it[0], key.at(j)));

        i++;
        j++;
    }
}

std::string Encryption::getEncrypted() const
{
    return text_encrypted;
}