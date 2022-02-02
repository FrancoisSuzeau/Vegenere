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
    
}

Input::~Input()
{

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* captureInput **************************************************************************/
/***********************************************************************************************************************************************************************/
void Input::captureInput()
{

    std::cout << "Enter something : " << std::endl;

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
    this->transformToLowerCase();

    //Delete space character
    this->deleteAllSpecificCaract(' ');

    //delete all other caracter from 33 to 96 in the ASCII table
    for(int i(33); i < 97; i++)
    {
        this->deleteAllSpecificCaract((char) i);
    }

    //delete ~ character
    this->deleteAllSpecificCaract('~');

    //replace é, è, ç and à character to e, e c, a
    this->FindAndReplace();

    //delete § character
    int i(0);
    int index(0);
    for(std::string::iterator it = input_user.begin(); it !=input_user.end(); it++)
    {
        int code = (int) *it;
        if(code < 0)
        {
            index = i;
        }
        i++;
    }

    input_user.erase(index, 1);
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** FindAndReplace **************************************************************************/
/***********************************************************************************************************************************************************************/
void Input::FindAndReplace()
{
    int i(0);
    //goes through all character of the string
    for(std::string::iterator it = input_user.begin(); it !=input_user.end(); it++)
    {
        int code = (int) *it; // recover the code of the character
        if(code < 0) //not in ASCII table
        {
            switch (code)
            {
                case -121: //replace ç
                    input_user.replace(i, 1, "c");
                    break;
                case -126: //replace é
                    input_user.replace(i, 1, "e");
                    break;
                case -118: //replace è
                    input_user.replace(i, 1, "e");
                    break;
                case -123: //replace à
                    input_user.replace(i, 1, "a");
                    break;
                default:
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
    std::for_each(input_user.begin(), input_user.end(), [] (char & c) {
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
    while(input_user.find(c_to_find) != std::string::npos)
    {
        //the erase method will delete the first occurence
        //find here start at the begin iterator and finish at the end and return the character to erase.
        //if not then we are not in the loop so ¯\_(ツ)_/¯
        input_user.erase(std::find(input_user.begin(), input_user.end(), c_to_find));
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** getters/setters ************************************************************************/
/***********************************************************************************************************************************************************************/
std::string Input::getInput() const
{
    return input_user;
}