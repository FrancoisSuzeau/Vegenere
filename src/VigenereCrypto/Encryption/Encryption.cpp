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
/************************************************************************* VigenereEncryption **************************************************************************/
/***********************************************************************************************************************************************************************/
void Encryption::VigenereEncryption(std::string text, std::string key)
{
    int i(0);
    int j(0);

    //don't know how the os initialize a string so I prefer to empty it
    if((int) text_encrypted.size() != 0)
    {
        text_encrypted.assign("");
    }

    //we browse every letter of the text
    for(std::string::iterator it = text.begin(); it != text.end(); it++)
    {

        //if the size of the key is inferior to the size of the text we start again at the begining of the key every time the index of the letter in the text
        //go past the size of the key
        if(j >= (int) key.size())
        {
            j = 0;
        }

        //we add the letter transformed (initial it[0]) by the letter of the key at the j position
        text_encrypted.push_back(this->transformLetter(it[0], key.at(j)));

        i++;
        j++;
    }
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** transformLetter **************************************************************************/
/***********************************************************************************************************************************************************************/
char Encryption::transformLetter(const char m, const char b)
{
    unsigned int code = (alphabetic_code[m] + alphabetic_code[b]) % 26;
    char n = '\0';
    
    this->searchLetter(code, n);

    return n;
}

/***********************************************************************************************************************************************************************/
/************************************************************************* VigenereDecryption **************************************************************************/
/***********************************************************************************************************************************************************************/
void Encryption::VigenereDecryption(std::string key)
{
    int i(0);
    int j(0);

    //don't know how the os initialize a string so I prefer to empty it
    if((int) text_decrypted.size() != 0)
    {
        text_decrypted.assign("");
    }

    //we browse every letter of the encrypted message
    for(std::string::iterator it = text_encrypted.begin(); it != text_encrypted.end(); it++)
    {

        //if the size of the key is inferior to the size of the text we start again at the begining of the key every time the index of the letter in the text
        //go past the size of the key
        if(j >= (int) key.size())
        {
            j = 0;
        }

        //we add the letter transformed (initial it[0]) by the letter of the key at the j position
        text_decrypted.push_back(this->reverseLetter(it[0], key.at(j)));

        i++;
        j++;
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** reverseLetter **************************************************************************/
/***********************************************************************************************************************************************************************/
char Encryption::reverseLetter(const char m, const char b)
{
    unsigned int code = (26 - alphabetic_code[b] + alphabetic_code[m]) % 26;

    char n = '\0';
    this->searchLetter(code, n);

    return n;
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** searchLetter ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Encryption::searchLetter(unsigned int code, char &n)
{
    //Because i use a map I cannot find the letter (the key of the map) by its value (the alphabetic code).
    //May be i optimize it later
    for(std::map<const char, unsigned int>::iterator it = alphabetic_code.begin(); it != alphabetic_code.end(); it++)
    {
        if(it->second == code)
        {
            n = it->first;
            break;
        }
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************* getters/setters *****************************************************************************/
/***********************************************************************************************************************************************************************/
std::string Encryption::getEncrypted() const
{
    return text_encrypted;
}

std::string Encryption::getDecrypted() const
{
    return text_decrypted;
}