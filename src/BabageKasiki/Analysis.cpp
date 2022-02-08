/*  Author : SUZEAU François

    Creation : 03/02/2022

    Purpose : Declaration of the Analysis class
*/

#include "Analysis.hpp"

/***********************************************************************************************************************************************************************/
/***************************************************************** Constructor and Destructor **************************************************************************/
/***********************************************************************************************************************************************************************/
Analysis::Analysis(std::string cyper_text) : m_cypher_text(cyper_text)
{

}

Analysis::Analysis() : m_cypher_text("none")
{

}

Analysis::~Analysis()
{

}

/***********************************************************************************************************************************************************************/
/************************************************************************* calculateOccurences *************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::calculateOccurences()
{
    //just to be sure, we cleazr the map because i still don't know how the OS initialize it
    occcurence_table.clear();
    std::map<std::string, sequence_calculate> tmp;

    //this loop move the position of the first letter of the sequence
    //note that we dont want the last substring of the last 3 letter of the cypher text
    for(int position(0); position < (int) m_cypher_text.size() - 3; position++) 
    {
        //to improve the second loop we recover a substring starting at position to the end of the cypher_text
        //so second loop will only be in the substring area not in cypher_text area
        std::string substr = m_cypher_text.substr(position, m_cypher_text.size());
        // std::cout << "SUBSTR : " << substr << std::endl;

        // this loop take the size of the sequence (3 or more)
        //and only browse the cypher text by the substring
        for(int size(3); size < (int) substr.size() + 1; size++)
        {
            //recover the sequence at position with the number of letter for size of the sequence
            std::string sequence = m_cypher_text.substr(position, size);

            if(tmp[sequence].already_calculate == false)
            {
                //calculate occurence count of the sequence
                this->findOccurrence(sequence);

                //because the sequence will appeared an other time if is occurence il >= 2
                // we don't have to calculate his occurence again so we set it a true
                occcurence_table[sequence].already_calculate = true;
            }

            
        }
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** findOccurrence **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::findOccurrence(std::string sequence)
{

    //a temporaly copy of the cypher text to calculate occurence count
    std::string copy = m_cypher_text;

    //the find method of class string return the position of the first letter of the sequence in the string copy
    //if the sequence hasn't be found the method return npos
    std::string::size_type found_pos = copy.find(sequence);

    unsigned int count(0);

    while(found_pos != std::string::npos)
    {
        //if we have find a sequence, we delete it in the copy of the cypher text
        //because if not the find method will always return the same result and we will go to
        //an infinite loop
        copy.erase(found_pos, sequence.size());

        //recover the next position of the sequence        
        found_pos = copy.find(sequence);

        //adding the current occurence in the count
        count++;
    }

    //save it in this variable that we used later
    occcurence_table[sequence].occurences = count;
}

/***********************************************************************************************************************************************************************/
/************************************************************************* calculateDistance **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::calculateDistance()
{
    //first we browse the sequence table
    for(std::map<std::string, sequence_calculate>::iterator it = better_sequence.begin(); it != better_sequence.end(); ++it)
    {
        //we need a copy of the cypher text
        std::string copy = m_cypher_text;

        //we take the first position of the sequence (if not return npos)
        std::string::size_type found_pos = copy.find(it->first);

        //we save it has the current pos
        std::string::size_type current_pos = found_pos;

        while(found_pos != std::string::npos)
        {
            //have to delete the sequence in the copy of the cypher text
            //(because if not the find method will return always the same position)
            copy.erase(found_pos, it->first.size());

            //recover the position of the next occurence
            found_pos = copy.find(it->first);

            //if we find an other occurence then we can calculate the distance between the position of the current ocurrence
            //and the next one
            if(found_pos != std::string::npos)
            {
                //we add the size of the occurence because the position of the next occurence is shiften of - the sequence.size()
                //because of the call of erase in the copy before the find
                it->second.distances.push_back(found_pos - current_pos + it->first.size());
                current_pos = found_pos;
            }   
        }
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************* calculateKeylength **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::calculateKeylength()
{
    //because we cannot find a distance if a sequence appears one time we first delete this kind of sequence
    this->extractSequenceToAnalyse();

    //here we calculate distances between all occurence of all sequence
    this->calculateDistance();

    //We now have to search dvisors of a distance
    //So we browse the sequence map
    for(std::map<std::string, sequence_calculate>::iterator it = better_sequence.begin(); it != better_sequence.end(); ++it)
    {
        //and then we browse all the distances of a sequence
        for(auto &tmp : it->second.distances)
        {
            //and calculate the frequency of the divisor of the current distance (tmp)
            this->calculateDistantDivisorFrequency(tmp);
        }
    }

    //we now have a map with all divisor possible (no double) and his appearence count
    //we just have to find the max of appearance
    int max = this->findMaxFrequency();
    int key_length = 0;

    //and then find the distance corresponding to this max
    //Reminder : in this map the first member of an iterator is the distance (the key) and the second member is
    //his the appearance count
    for(std::map<int, int>::iterator it = divisor_frequency.begin(); it != divisor_frequency.end(); ++it)
    {
        if(it->second == max)
        {
            key_length = it->first;
        }
    }

    std::cout << key_length << std::endl;
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************* findMaxFrequency **************************************************************************/
/***********************************************************************************************************************************************************************/
int Analysis::findMaxFrequency()
{
    int max = 0;

    for(std::map<int, int>::iterator it = divisor_frequency.begin(); it != divisor_frequency.end(); ++it)
    {
        if(it->second > max)
        {
            max = it->second;
        }
    }

    return max;
}

/***********************************************************************************************************************************************************************/
/******************************************************************* calculateDistantDivisorFrequency **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::calculateDistantDivisorFrequency(int distance)
{
    int R = (int) sqrt(distance);

    for(int potentialy_div(2); potentialy_div <= R; potentialy_div++)
    {
        if(distance % potentialy_div == 0)
        {
            //the magical thing appear here
            //if potentialy_div hasn't been found as divisor of a distance then c++ create a ligne in the map with potentialy_div as key
                //and increment this ligne by one
            //if it already found it for another distance then just increase
            divisor_frequency[potentialy_div]++;
        }
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************* extractSequenceToAnalyse **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::extractSequenceToAnalyse()
{
    better_sequence.clear();

    //we browse the occurence table that contain all possible sequencies calculate and their occurence count
    for(std::map<std::string, sequence_calculate>::iterator it = occcurence_table.begin(); it != occcurence_table.end(); ++it)
    {
        //we only keep a sequence with and occurences grather or equal than 2
        if((it->second.occurences >= 2))
        {
            better_sequence[it->first] = it->second;

            //reminder :
            //first is the key in an map iterator
            //second is the value (or the sequence_calculate structure in our case) 
        }
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************* getters/setters *****************************************************************************/
/***********************************************************************************************************************************************************************/
std::map<std::string, sequence_calculate> Analysis::getCalculationTable(int type) const
{
    switch (type)
    {
        case OCCURENCE:
            return occcurence_table;
        case SEQUENCE_A:
            return better_sequence;
        default:
            break;
    }
}

void Analysis::setCypherText(std::string const text)
{
    m_cypher_text.clear();
    m_cypher_text = text;
}