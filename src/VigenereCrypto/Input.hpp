/*  Author : SUZEAU François

    Creation : 01/02/2022

    updated : 
*/

#ifndef INPUT_H
#define INPUT_H

    #include <iostream>
    #include <string>
    #include <algorithm>
    

    class Input {


        private:

            std::string input_user;
            void transformToLowerCase();
            void deleteAllSpecificCaract(const char c_to_find);
            void FindAndReplace();

        public:

            Input();
            ~Input();

            void captureInput();
            std::string getInput() const;
            void transformInput();



    };

#endif