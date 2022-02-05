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
    calculate_table.clear();
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
                calculate_table[sequence].occurences = this->findOccurrence(sequence);
                calculate_table[sequence].already_calculate = true;

                // std::cout << "OCCURENCE : " << calculate_table[sequence].occurences << std::endl;
            }

            
        }
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** findOccurrence **************************************************************************/
/***********************************************************************************************************************************************************************/
unsigned int Analysis::findOccurrence(std::string sequence)
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

    return count;
}

/***********************************************************************************************************************************************************************/
/************************************************************************* getters/setters *****************************************************************************/
/***********************************************************************************************************************************************************************/
std::map<std::string, sequence_calculate> Analysis::getCalculationTable() const
{
    return calculate_table;
}

void Analysis::setCypherText(std::string const text)
{
    m_cypher_text.clear();
    m_cypher_text = text;
}