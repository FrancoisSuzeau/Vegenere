/*  Author : SUZEAU François

    Creation : 02/02/2022

    Purpose : Module of Exercice 3 of Part One
*/

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

    #include <iostream>
    #include <string>
    #include <map>
    

    class Encryption {


        private:

            std::map<const char, unsigned int> alphabetic_code;
            char transformLetter(const char m, const char b);

            std::string text_encrypted;

        public:

            Encryption();
            ~Encryption();

            void VigenereEncryption(std::string text, std::string key);
            std::string getEncrypted() const;


            
    };

#endif