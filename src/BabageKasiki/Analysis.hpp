/*  Author : SUZEAU François

    Creation : 03/02/2022

    Purpose : Module of Exercice 6 for Part Two
*/

#ifndef ANALYSIS_H
#define ANALYSIS_H

    #include <iostream>
    #include <string>
    

    class Analysis {


        private:

            std::string m_cypher_text;
            
            unsigned int findOccurrence(std::string sequence);

        public:

            Analysis(std::string cypher_text);
            ~Analysis();

            void calculateOccurences();
    };

#endif