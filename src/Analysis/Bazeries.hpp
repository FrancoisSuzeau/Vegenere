/*  Author : SUZEAU François

    Creation : 15/02/2022

    Purpose : Module of Exercice 15 and 16 for Part Three
*/

#ifndef BAZERIES_H
#define BAZERIES_H

    #include <iostream>
    #include <string>
    #include <map>
    #include <vector>
    #include <algorithm>
    #include <math.h>
    #include <cassert>
    

    class Bazeries {


        private:

            std::string     m_cypher_text;

            std::map<std::string, int>  map_position;

            std::string     likelyWordAtPos(std::string likely_word, int position);
            int             calculateDistance(std::string a, std::string b);


        public:

            Bazeries(std::string const cypher_text);
            ~Bazeries();

            void likelyWordAnalysis(int key_length);


    };

#endif