/*  Author : SUZEAU François

    Creation : 03/02/2022

    Purpose : Module of Exercice 6 for Part Two
*/

#ifndef ANALYSIS_H
#define ANALYSIS_H

    #include <iostream>
    #include <string>
    #include <map>

    #define OCCURENCE 1
    #define SEQUENCE_A 2

    typedef struct sequence_calculate {

        unsigned int occurences = 0; //the total count of occurences the sequence has
        bool already_calculate = false; //sometimes a sequence can be calculate twice so we prevent that here
        unsigned int distance_between_occ = 0;

    } sequence_calculate;
    

    class Analysis {


        private:

            std::string m_cypher_text;
            std::map<std::string, sequence_calculate> occcurence_table;
            std::map<std::string, sequence_calculate> better_sequence;
            
            void findOccurrence(std::string sequence);
            void extractSequenceToAnalyse();


        public:

            Analysis(std::string cypher_text);
            Analysis();
            ~Analysis();

            void calculateOccurences();
            void calculateKeylength();

            std::map<std::string, sequence_calculate> getCalculationTable(int type) const;
            void setCypherText(std::string const text);
    };

#endif