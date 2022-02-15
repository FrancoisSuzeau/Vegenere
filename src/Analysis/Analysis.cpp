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

    int i(0);
    for(std::string::iterator it = m_cypher_text.begin(); it != m_cypher_text.end(); ++it)
    {
        std::string l = m_cypher_text.substr(i, 1);
        decrypted_cypher.push_back(l);
        i++;
    }
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
                unsigned int count = this->findOccurrence(sequence);

                //save it in this variable that we used later
                occcurence_table[sequence].occurences = count;
                // std::cout << sequence << " : " << occcurence_table[sequence] << std::endl;

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
        if(it->second == max)
        {
            key_length = it->first;
        }
    }

    //When the most common divisor is pair, the program find 2 as the most common divisor whereas it could be 4 or 6
    //so we let the user decide with statistics
    if(key_length % 2 == 0)
    {
        //browse the divisor occurence map
        for(std::map<int, int>::iterator it = divisor_frequency.begin(); it != divisor_frequency.end(); ++it)
        {
            std::cout << it->first << " : " << it->second << std::endl;
        }

        //capture the choice of the user
        std::string choice;
        std::cout << "The most common divisor is pair so you can choose a more probalble key length (see above)." << std::endl;
        std::cin >> choice;

        try
        {
            //convert it to int
            key_length = stoi(choice);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error  : " << e.what() << '\n';
        }
        
    }

    std::cout << "Divisor method find : " << key_length << " as key length" << std::endl;
    
}

/***********************************************************************************************************************************************************************/
/*************************************************************************** friedmanTest ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::friedmanTest()
{
    //we need a string containing all the letter in the alphabet to calculate the occurence in the cypher text
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    letter_occurence.clear();

    for(int i = 0; i < (int) alphabet.size(); i++)
    {
        //at each iteration we recover a letter in the alphabet
        std::string letter = alphabet.substr(i, 1);
        //and then calculate his occurence count in the cypher text that we add in our map
        letter_occurence[letter] = this->findOccurrence(letter);
    }

    float K(0.0f);

    //here we calculate the top part of the formula : (ke - kr) / (k - kr)
    //with ke the probability to find two same letter in a english text
    for(std::map<std::string, int>::iterator it = letter_occurence.begin(); it != letter_occurence.end(); ++it)
    {
        K+= (float) ( letter_occurence[it->first] * (letter_occurence[it->first] - 1) );
    }

    //the bottom part of the formula
    K /=  (float) (m_cypher_text.size() * (m_cypher_text.size() - 1));

    float Ke = 0.067f;
    float Kr = (float) 1/26;
    float Ltmp = (float) (Ke - Kr) / (float) (K - Kr);

    //convert the result to the lower rounding as key lenght
    L = (int) Ltmp;
    std::cout << "Friedman Test find : " << L << " as key length" << std::endl;
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
/********************************************************************** frequencyAnalysis ******************************************************************************/
/***********************************************************************************************************************************************************************/
std::string Analysis::frequencyAnalysis(int key_l)
{
    //a string that is fill with a letter at each iteration
    std::string key;
    //this string will serve to calculate the frequency of all letter in the substring
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    //this will serve the stop condition of our while loop
    int nb_letter_in_key_found(0);

    //here we want to let the choice of which language the user suspect how the original text is written
    std::string choice;
    std::cout << "Choose a language you want for analysis (default french) :\n1 - French\n2 - English" << std::endl;
    std::cin >> choice;

    std::cout << std::endl;

    //we display the cypher text by key length sequences
    std::cout << "The encrypted text cut by the key length : " << std::endl;
    this->displaySeparateCypher(key_l);

    std::cout << std::endl;

    //we stop the analysis when we reach the key size even if it is not the key
    while(nb_letter_in_key_found < key_l)
    {

        //there we display the letter at i position in the key length sequences of the cypher text after we recover them in the vector lettersAtPos
        std::cout << "There is the " << nb_letter_in_key_found + 1 << " letter of each sub sequence : " << std::endl;
        std::cout << std::endl;
        std::vector<std::string> lettersAtPos;
        this->takeLetterAtPos(key_l, nb_letter_in_key_found, lettersAtPos);
        for(std::vector<std::string>::iterator it = lettersAtPos.begin(); it != lettersAtPos.end(); ++it)
        {
            std::cout << it[0];
        }
        std::cout << std::endl;
        std::cout << std::endl;

        //then we calculate the frequency appearence of each letter at the i position
        std::cout << "There is the frequency appearance of this letter : " << std::endl;
        this->calculateFrequencyLetterSubstr(lettersAtPos);

        //then we show the frequency appearence in a english or french text (choose by user)
        std::cout << std::endl;
        std::string language = (choice == "1") ? "French :" : "English :";
        std::cout << "And now the frequency appareance in " << language << std::endl;
        this->displayLetterFrequencyLangage(choice, alphabet);

        //then we let the user choose which letter he want to replace
        std::string choice_a, choice_b;
        std::cout << "Choose the letter in sub sequence :" << std::endl;
        std::cin >> choice_a;

        std::cout << std::endl;

        //here we let the user to choose which letter the previously letter was encrypted
        std::cout << "Choose the letter in language frequency appearance :" << std::endl;
        std::cin >> choice_b;

        //then we calculate and find the position in alphabet of the letter of the key responsible of the encrypted letter choose by user
        int index = this->calculateDistBetweenLetter(choice_a, choice_b);

        // this->clean(choice_b, alphabet);
        // std::cout << alphabet.at(index) << std::endl;

        //and we add the letter at the previously calculate position in the key string
        key.append(alphabet.substr(index, 1));

        nb_letter_in_key_found++;

        if(nb_letter_in_key_found < key_l)
        {
            //just a previsualization of the key at each iteration
            std::cout << "For now here is the key : " << key << std::endl;
        }
        

    }

    std::cout << "Here is the key you found : " << key << std::endl;

    return key;
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displaySeparateCypher *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::displaySeparateCypher(int key_l)
{
    int i(1);
    //just a print function where we display all the letter of the cypher text by key length sequences  
    for(std::string::iterator it = m_cypher_text.begin(); it != m_cypher_text.end(); ++it)
    {
        std::cout << it[0];

        //and if the position of the next letter in the cypher text is divisible by the key length then we add a space
        //because we start the loop at 1 we prevent to not calculate for one as a divisor of key length
        if(i % key_l == 0)
        {
            std::cout << " ";
        }
        i++;
    }

    std::cout << std::endl;
}

/***********************************************************************************************************************************************************************/
/*********************************************************** displayLetterFrequencyLangage *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::displayLetterFrequencyLangage(std::string choice, std::string alphabet)
{
    //in this function we display the frequency appearance of all letter in an english or french text (according to the choice of the user)
    std::vector<float> tmp = frequency_appearance_french;
    if(choice == "2")
    {
        tmp = frequency_appearance_english;
    }
    
    int i(0);
    for(std::string::iterator it = alphabet.begin(); it != alphabet.end(); ++it)
    {
        std::cout << "[ " <<  it[0] << " : " << tmp[i] << "] ";
        i++;
    }

    std::cout << std::endl;
}

/***********************************************************************************************************************************************************************/
/********************************************************** calculateFrequencyLetterSubstr *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::calculateFrequencyLetterSubstr(std::vector<std::string> tmp)
{
    //In this function we calculate the frequency appearance of each letter at a certain position in sequences of size of the key

    //first we calculate their occurence
    std::map<std::string, int> occ;
    for(std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        occ[it[0]]++;
    }

    //then we transform it in frequency and displaying it
    for(std::map<std::string, int>::iterator it = occ.begin(); it != occ.end(); ++it)
    {
        letter_frequency[it->first] = (float) it->second * 100 / tmp.size();
        std::cout << "[ " <<  it->first << " : " << letter_frequency[it->first] << "] ";
    }

}

/***********************************************************************************************************************************************************************/
/************************************************************************* takeLetterAtPos *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Analysis::takeLetterAtPos(int key_l, int offset, std::vector<std::string> &tmp)
{
    //in this function we recover all letter at a certain position in sequences of size of the key
    //example : with a key length of four
    //adsd rdqs qaeq adsd qzeer
    //if we are in the second iteration (offset variable) of the while loop then we recover all the letter a second position in this sequences
    //-> ddadz
    tmp.clear();
    for(int i(0); i < (int) m_cypher_text.size(); i++)
    {
        if((i % key_l == 0) && (i + offset < (int) m_cypher_text.size()))
        {
            tmp.push_back(m_cypher_text.substr(i + offset, 1));
        }
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************** calculateDistBetweenLetter *****************************************************************************/
/***********************************************************************************************************************************************************************/
int Analysis::calculateDistBetweenLetter(std::string a, std::string b)
{
    //in this function we want to calculate the position of the key that has encrypted the original letter
    // a -> the letter in cypher text choose by user
    // b -> the letter choose by user in the frequency appearance of a text written in a certain language
    int index_a, index_b;

    //we first recover the index of each letter in the alphabet
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i(0); i < (int) alphabet.size(); i++)
    {
        if(a == alphabet.substr(i, 1))
        {
            index_a = i;
        }

        if(b == alphabet.substr(i, 1))
        {
            index_b = i;
        }
    }

    //then we calculate their distances that will give us the index of the corresponding letter in the key
    int dist;
    if(index_b > index_a)
    {
        dist = 26 - (index_b - index_a);
    }
    else
    {
        dist = (index_a - index_b) % 26;
    }

    return dist;
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** clean **********************************************************************************/
/***********************************************************************************************************************************************************************/
// void Analysis::clean(std::string b, std::string &alphabet)
// {
//     int index(0);
//     for(std::string::iterator it = alphabet.begin(); it != alphabet.end(); ++it)
//     {
//         if(b == alphabet.substr(index, 1))
//         {
//             frequency_appearance_english.erase(frequency_appearance_english.begin()+index);
//             frequency_appearance_french.erase(frequency_appearance_french.begin()+index);
//             break;
//         }

//         index++;
//     }

//     alphabet.erase(index, 1);
// }

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