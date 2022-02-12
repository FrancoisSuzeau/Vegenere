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
                                // A     B      C       D   E       F   G       H   I       J   K       L
    frequency_appearance_french = {9.42, 1.02, 2.64, 3.39, 15.87, 0.95, 1.04, 0.77, 8.41, 0.89, 0.0, 5.34,
    
//  M       N   O       P   Q       R   S       T   U       V   W   X       Y   Z
    3.24, 7.15, 5.14, 2.86, 1.06, 6.46, 7.9, 7.26, 6.24, 2.15, 0.0, 0.3, 0.24, 0.32};

                                //   A      B   C       D   E       F      G    H   I       J   K       L
    frequency_appearance_english = {8.08, 1.67, 3.18, 3.99, 12.56, 2.17, 1.8, 5.27, 7.24, 0.14, 0.63, 4.04,

//  M       N   O       P   Q       R   S       T   U     V     W   X       Y   Z
    2.6, 7.38, 7.47, 1.91, 0.09, 6.42, 6.59, 9.15, 2.79, 1.0, 1.89, 0.21, 1.65, 0.07};

    decrypted_cypher = new std::string[m_cypher_text.size()];
    assert(decrypted_cypher);

    int i(0);
    for(std::string::iterator it = m_cypher_text.begin(); it != m_cypher_text.end(); ++it)
    {
        std::string l = m_cypher_text.substr(i, 1);
        decrypted_cypher[i] = l;
        i++;
    }
}

Analysis::Analysis() : m_cypher_text("none")
{

}

Analysis::~Analysis()
{
    if(decrypted_cypher != nullptr)
    {
        delete decrypted_cypher;
    }
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
                unsigned int count = this->findOccurrence(sequence);

                //save it in this variable that we used later
                occcurence_table[sequence].occurences = count;

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
unsigned int Analysis::findOccurrence(std::string sequence)
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

    return count;
}

/***********************************************************************************************************************************************************************/
/************************************************************************* calculateDistance ***************************************************************************/
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
        // std::cout << it->first << std::endl;
        //and then we browse all the distances of a sequence
        for(auto &tmp : it->second.distances)
        {
            // std::cout << tmp << std::endl;
            //and calculate the frequency of the divisor of the current distance (tmp)
            this->calculateDistantDivisorFrequency(tmp);
        }
    }

    //we now have a map with all divisor possible (no double) and his appearence count
    //we just have to find the max of appearance
    int max = this->findMaxFrequency();
    key_length = 0;

    //and then find the distance corresponding to this max
    //Reminder : in this map the first member of an iterator is the distance (the key) and the second member is
    //his the appearance count
    for(std::map<int, int>::iterator it = divisor_frequency.begin(); it != divisor_frequency.end(); ++it)
    {
        // std::cout << "Divisor : " << it->first << " and his appearance count : " << it->second << std::endl;
        if(it->second == max)
        {
            key_length = it->first;
        }
    }

    // std::cout << "Divisor method : " << key_length << std::endl;
    
}

/***********************************************************************************************************************************************************************/
/*************************************************************************** friedmanTest ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::friedmanTest()
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    letter_occurence.clear();

    for(int i = 0; i < (int) alphabet.size(); i++)
    {
        std::string letter = alphabet.substr(i, 1);
        letter_occurence[letter] = this->findOccurrence(letter);
    }

    float K(0.0f);

    for(std::map<std::string, int>::iterator it = letter_occurence.begin(); it != letter_occurence.end(); ++it)
    {
        K+= (float) ( letter_occurence[it->first] * (letter_occurence[it->first] - 1) );
    }

    K /=  (float) (m_cypher_text.size() * (m_cypher_text.size() - 1));

    float Ke = 0.067f;
    float Kr = (float) 1/26;
    float Ltmp = (float) (Ke - Kr) / (float) (K - Kr);

    L = (int) Ltmp;
    // std::cout << "Friedman Test : " << L << std::endl;
}

/***********************************************************************************************************************************************************************/
/********************************************************************** frequencyAnalysis ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::frequencyAnalysis(int key_l)
{
    //since we already calculate the occurence of all letter in the Friedman test
    //I re used them
    std::map<std::string, float> frequency_in_cypher;
    for(std::map<std::string, int>::iterator it = letter_occurence.begin(); it != letter_occurence.end(); ++it)
    {
        frequency_in_cypher[it->first] = (float) (it->second * 100) / (float) m_cypher_text.size();
    }

    std::string replace;
    std::string replace_by;
    std::string tmp = "abcdefghijkelmnopqurstuvwxyz";
    std::string tmp1 = "abcdefghijkelmnopqurstuvwxyz";

    while((replace != "1") && (replace_by != "1"))
    {
        std::cout << "There is the frequency of each letter in the encrypted text : " << std::endl;
        this->showFrequnecyAnalysisSept(frequency_in_cypher, tmp);

        std::cout << ">>>>>>>>> Choose a letter to replace : (Enter 1 to stop)" << std::endl;
        std::cin >> replace;
        std::cout << std::endl;

        if((replace.size() == 1) && (tmp.find(replace) != std::string::npos))
        {
            std::cout << ">>>>>>>>> Choose by which letter you want to replace : (Enter 1 to stop)" << std::endl;
            std::cin >> replace_by;
            std::cout << std::endl;

            if((replace_by.size() == 1) && (tmp1.find(replace_by) != std::string::npos))
            {
                this->replaceAndShowResult(replace, replace_by);
                this->clean(replace, replace_by, tmp1, frequency_in_cypher);
                std::string::size_type pos = tmp.find(replace);
                tmp.erase(pos, 1);
            }
        }
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************** replaceAndShowResult **********************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::replaceAndShowResult(std::string re, std::string re_by)
{
    
    for(int pos(0); pos < (int) m_cypher_text.size(); pos++)
    {
        std::string letter = m_cypher_text.substr(pos, 1);
        if(letter == re)
        {
            decrypted_cypher[pos] = re_by;
        }
    }

    for(int i(0); i < (int) m_cypher_text.size(); i++)
    {
        std::cout << decrypted_cypher[i];
        if((i % 4 == 0) && (i > 1))
        {
            std::cout << " ";
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

/***********************************************************************************************************************************************************************/
/********************************************************************** showFrequnecyAnalysisSept **********************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::showFrequnecyAnalysisSept(std::map<std::string, float> frequency_in_cypher, std::string alphabet)
{

    for(std::map<std::string, float>::iterator it = frequency_in_cypher.begin(); it != frequency_in_cypher.end(); ++it)
    {
        std::cout << "[" << it->first << " : " << it->second << "] ";
    }

    std::cout << std::endl;
    std::cout << std::endl;

    this->displayGeneralLanguageLetterFrequency(alphabet);
}

/***********************************************************************************************************************************************************************/
/*************************************************************************** findMaxFrequency **************************************************************************/
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
/******************************************************************* calculateDistantDivisorFrequency ******************************************************************/
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
    std::map<std::string, sequence_calculate> ret;
    switch (type)
    {
        case OCCURENCE:
            ret = occcurence_table;
            break;
        case SEQUENCE_A:
            ret = better_sequence;
            break;
        default:
            break;
    }

    return ret;
}

void Analysis::setCypherText(std::string const text)
{
    m_cypher_text.clear();
    m_cypher_text = text;
}

int Analysis::getKeyLenght(int choice) const
{
    int ret(0);
    switch (choice)
    {
        case DIVISOR_KEY:
            ret = key_length;
            break;
        case FRIEDMAN_KEY:
            ret = L;
            break;
        default:
            break;
    }

    return ret;
}

void Analysis::displayGeneralLanguageLetterFrequency(std::string alphabet)
{
    std::cout << "Here, the frequency appearance of each letter in FRENCH : " << std::endl;
    // std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    int i(0);
    for(std::vector<float>::iterator it = frequency_appearance_french.begin(); it != frequency_appearance_french.end(); ++it)
    {
        std::string letter = alphabet.substr(i, 1);
        std::cout << "[" << letter << " : " << it[0] << "%] ";

        i++;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    i = 0;

    std::cout << "Now, the frequency appearance of each letter in ENGLISH : " << std::endl;
    for(std::vector<float>::iterator it = frequency_appearance_english.begin(); it != frequency_appearance_english.end(); ++it)
    {
        std::string letter = alphabet.substr(i, 1);
        std::cout << "[" << letter << " : " << it[0] << "%] ";

        i++;
    }

    std::cout << std::endl;
    std::cout << std::endl;

}

void Analysis::clean(std::string replaced, std::string replaced_by, std::string &alphabet, std::map<std::string, float> &frequency_in_cypher)
{
    int i(0);
    for(std::string::iterator it = alphabet.begin(); it != alphabet.end(); ++it)
    {
        if(it[0] == replaced_by.at(0))
        {
            break;
        }

        i++;
    }

    frequency_appearance_french.erase(frequency_appearance_french.begin()+i);
    frequency_appearance_english.erase(frequency_appearance_english.begin()+i);
    
    alphabet.erase(i, 1);

    for(auto it = frequency_in_cypher.begin(); it != frequency_in_cypher.end();)
    {
        if(it->first == replaced)
        {
            it = frequency_in_cypher.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }
}