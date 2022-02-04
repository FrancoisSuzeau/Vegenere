/*  Author : SUZEAU François

    Creation : 01/02/2022

    Purpose : Declaration of the Input class
*/

#include "Input.hpp"


/***********************************************************************************************************************************************************************/
/***************************************************************** Constructor and Destructor **************************************************************************/
/***********************************************************************************************************************************************************************/
Input::Input()
{
    input_user = "none";
    input_transormed = "none";
}

Input::~Input()
{

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* captureInput **************************************************************************/
/***********************************************************************************************************************************************************************/
void Input::captureInput(std::string const message)
{
    if((int) input_user.size() != 0)
    {
        input_user.assign("");
    }

    std::cout << message << std::endl;

    //cin is the standard input flux. 
    //not that if we do this : cin >> input_user; then we only get one word even if we input an entire sentence
    //the getline method extract a whole stream into a string 
    std::getline(std::cin, input_user);
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** transformInput **************************************************************************/
/***********************************************************************************************************************************************************************/
void Input::transformInput()
{
    input_transormed.clear();
    input_transormed = input_user;

    this->transformToLowerCase();

    //delete all other caracter from 33 to 96 in the ASCII table
    for(int i(33); i < 97; i++)
    {
        //don't know why but the € character is replace by ? and it is deleted here
        this->deleteAllSpecificCaract((char) i);
    }

    //delete ~ character
    this->deleteAllSpecificCaract('~');

    //replace é, è, ç, ù and à character to e, e, c, u, a
    //replace §, µ, £, ¨, ¤, and € by a space character that will be deleted later
    this->FindAndReplace();

    //Delete space character
    this->deleteAllSpecificCaract(' ');
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** FindAndReplace **************************************************************************/
/***********************************************************************************************************************************************************************/
void Input::FindAndReplace()
{
    int i(0);
    //goes through all character of the string
    for(std::string::iterator it = input_transormed.begin(); it !=input_transormed.end(); it++)
    {
        int code = (int) *it; // recover the code of the character
        if(code < 0) //not in ASCII table
        {
            switch (code)
            {
                case -61: //Graphical input create this unknown caracter before all other special caracter (ç, é, è, à, ù)
                    input_transormed.replace(i, 1, " ");
                    break;
                case -89: //replace ç in graphical input and -121 in prompt input
                    input_transormed.replace(i, 1, "c");
                    break;
                case -87: //replace é in graphical input and -127 in prompt input
                    input_transormed.replace(i, 1, "e");
                    break;
                case -88: //replace è in graphical input and -118 in prompt input
                    input_transormed.replace(i, 1, "e");
                    break;
                case -96: //replace à in graphical input and -123 in prompt input
                    input_transormed.replace(i, 1, "a");
                    break;
                case -71: //replace ù in graphical input and -105 in prompt input
                    input_transormed.replace(i, 1, "u");
                    break;
                default: //replace §, µ, £, ¨, ¤ by a space that will be delete later
                    input_transormed.replace(i, 1, " ");
                    break;
            }
        }
        i++; //recover the position of the next character
    }

}

/***********************************************************************************************************************************************************************/
/*************************************************************************** transformToLowerCase **********************************************************************/
/***********************************************************************************************************************************************************************/
void Input::transformToLowerCase()
{
    //considering a string like an array we recover the iterator at the beginning and we copy it into the c character.
    //Then we use the tolower of the string class
    std::for_each(input_transormed.begin(), input_transormed.end(), [] (char & c) {
        c=std::tolower(c);
    });
}

/***********************************************************************************************************************************************************************/
/************************************************************************ deleteAllSpecificCaract **********************************************************************/
/***********************************************************************************************************************************************************************/
void Input::deleteAllSpecificCaract(const char c_to_find)
{
    //the find method is use to determine if the character exist in the string.
    // if so then we enter the loop and eradicate the first occurence of the character
    //if not then find return the npos string and this is because there is no other occurence of the character in the string
    while(input_transormed.find(c_to_find) != std::string::npos)
    {
        //the erase method will delete the first occurence
        //find here start at the begin iterator and finish at the end and return the character to erase.
        //if not then we are not in the loop so ¯\_(ツ)_/¯
        input_transormed.erase(std::find(input_transormed.begin(), input_transormed.end(), c_to_find));
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** getters/setters ************************************************************************/
/***********************************************************************************************************************************************************************/
std::string Input::getInput(bool get_transformed) const
{
    if(get_transformed)
    {
        return input_transormed;
    }

    return input_user;
    
}

void Input::setInput(const char *input)
{
    std::string tmp(input);
    if((tmp != input_user) && (tmp != "\0"))
    {
        input_user.clear();
        input_user = input;
    }    
}