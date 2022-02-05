/*  Author : SUZEAU François

    Creation : 03/02/2022

    Purpose : Module of Exercice 6 for Part Two
*/

#ifndef ANALYSIS_H
#define ANALYSIS_H

    #include <iostream>
    #include <string>
    #include <map>

    typedef struct sequence_calculate {

        unsigned int occurences = 0; //the total count of occurences the sequence has
        bool already_calculate = false; //sometimes a sequence can be calculate twice so we prevent that here

    } sequence_calculate;
    

    class Analysis {


        private:

            std::string m_cypher_text;
            std::map<std::string, sequence_calculate> calculate_table;
            
            unsigned int findOccurrence(std::string sequence);

        public:

            Analysis(std::string cypher_text);
            Analysis();
            ~Analysis();

            void calculateOccurences();

            std::map<std::string, sequence_calculate> getCalculationTable() const;
            void setCypherText(std::string const text);
    };

#endif