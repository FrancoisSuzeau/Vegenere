/*  Author : SUZEAU François

    Creation : 03/02/2022

    Purpose : Module of Exercice 6, 7, 8 (Babbage and Kasiki method), 11, 12 (Friedman Test) and 14 (frequency analysis for Part Two
*/

#ifndef ANALYSIS_H
#define ANALYSIS_H

    #include <iostream>
    #include <string>
    #include <map>
    #include <vector>
    #include <algorithm>
    #include <math.h>
    #include <cassert>

    #define OCCURENCE 1
    #define SEQUENCE_A 2

    #define DIVISOR_KEY 3
    #define FRIEDMAN_KEY 4

    #define FRENCH 5
    #define ENGLISH 6

    typedef struct sequence_calculate {

        unsigned int occurences = 0; //the total count of occurences the sequence has
        bool already_calculate = false; //sometimes a sequence can be calculate twice so we prevent that here
        std::vector<unsigned int> distances;

    } sequence_calculate;
    

    class Analysis {


        private:

            std::string m_cypher_text;
            int key_length;
            int L;
            std::map<std::string, sequence_calculate> occcurence_table;
            std::map<std::string, sequence_calculate> better_sequence;
            std::map<std::string, int> letter_occurence;

            std::vector<float> frequency_appearance_french;
            std::vector<float> frequency_appearance_english;

            std::map<int, int> divisor_frequency;
            
            unsigned int findOccurrence(std::string sequence);
            void calculateDistance();
            void extractSequenceToAnalyse();

            void calculateDistantDivisorFrequency(int distance);

            int findMaxFrequency();

            void displaySeparateCypher(int key_l);

            

            std::vector<std::string> decrypted_cypher;


        public:

            Analysis(std::string cypher_text);
            Analysis();
            ~Analysis();

            void calculateOccurences();
            void calculateKeylength();
            void friedmanTest();
            void frequencyAnalysis(int key_l);

            std::map<std::string, sequence_calculate> getCalculationTable(int type) const;
            void setCypherText(std::string const text);

            int getKeyLenght(int choice) const;


    };

#endif