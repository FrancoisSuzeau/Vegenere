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
            //recover the sequence at position with the number of letter by size
            std::string sequence = m_cypher_text.substr(position, size);

            // std::cout << "SEQUENCE : " << sequence << std::endl;

            if(tmp[sequence].already_calculate == false)
            {
                this->findOccurrence(sequence);
                occcurence_table[sequence].already_calculate = true;

                // std::cout << "OCCURENCE : " << occcurence_table[sequence].occurences << std::endl;
            }

            
        }
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** findOccurrence **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::findOccurrence(std::string sequence)
{

    std::string copy = m_cypher_text;
    std::string::size_type found_pos = copy.find(sequence);

    unsigned int count(0);

    while(found_pos != std::string::npos)
    {
        copy.erase(found_pos, sequence.size());

        found_pos = copy.find(sequence);

        count++;
    }

    occcurence_table[sequence].occurences = count;
}

/***********************************************************************************************************************************************************************/
/************************************************************************* calculateDistance **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::calculateDistance()
{
    
    for(std::map<std::string, sequence_calculate>::iterator it = better_sequence.begin(); it != better_sequence.end(); ++it)
    {
        std::string copy = m_cypher_text;
        std::string::size_type found_pos = copy.find(it->first);
        std::string::size_type current_pos = found_pos;

        while(found_pos != std::string::npos)
        {
            copy.erase(found_pos, it->first.size());

            found_pos = copy.find(it->first);

            if(found_pos != std::string::npos)
            {
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
    this->extractSequenceToAnalyse();
    this->calculateDistance();

    for(std::map<std::string, sequence_calculate>::iterator it = better_sequence.begin(); it != better_sequence.end(); ++it)
    {
        for(auto &tmp : it->second.distances)
        {
            this->calculateDistantDivisorFrequency(tmp);
        }
    }

    int max = this->findMaxFrequency();
    int key_length = 0;
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

    for(int i(2); i <= R; i++)
    {
        if(distance % i == 0)
        {
            divisor_frequency[i]++;
        }
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************* extractSequenceToAnalyse **************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::extractSequenceToAnalyse()
{
    better_sequence.clear();
    for(std::map<std::string, sequence_calculate>::iterator it = occcurence_table.begin(); it != occcurence_table.end(); ++it)
    {
        if((it->second.occurences >= 2))
        {
            better_sequence[it->first] = it->second;   
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