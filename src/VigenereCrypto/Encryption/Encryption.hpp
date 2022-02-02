/*  Author : SUZEAU François

    Creation : 02/02/2022

    Purpose : Module of Exercice 3, 4 and 5 of Part One
*/

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

    #include <iostream>
    #include <string>
    #include <map>
    

    class Encryption {


        private:

            std::map<const char, unsigned int> alphabetic_code;
            std::string text_encrypted;
            std::string text_decrypted;

            char transformLetter(const char m, const char b);
            char reverseLetter(const char m, const char b);
            void searchLetter(unsigned int code, char &n);

        public:

            Encryption();
            ~Encryption();

            void VigenereEncryption(std::string text, std::string key);
            void VigenereDecryption(std::string key);

            std::string getEncrypted() const;
            std::string getDecrypted() const;

    };

#endif