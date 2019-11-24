/*
*Version 0.7
*by Mx, Nov. 24
*/

#include "include/encode.h"
#include "include/decode.h"

#define DEBUG
#define DEBUG_COMP//压缩调试
//#define DEBUG_EXTR//解压调试
//#define DEBUG_BOTH//综合调试

int main(int argc, char *argv[])
{
#ifndef DEBUG

    if (argc == 4)
    {
        std::string fileName(argv[2]);
        std::string wrtName(argv[3]);
        std::string parameter(argv[1]);
        if (parameter == "comp")
            Encode(fileName, wrtName);
        else if (parameter == "extr")
            Decode(fileName, wrtName);
    }
    else
    {
        std::cout << "Error parameter, exiting..." << std::endl;
        Sleep(1000);
        exit(1);
    }
    std::cout << "Success." << std::endl;
    system("PAUSE");
    return 0;

#endif //DEBUG
//---------------------
#ifdef DEBUG_COMP

    Encode("test.txt", "test.comp");
    std::cout << "Success." << std::endl;
    system("PAUSE");
    return 0;

#endif //DEBUG_COMP
//---------------------
#ifdef DEBUG_EXTR

    Decode("test.comp", "test.txt");
    std::cout << "Success." << std::endl;
    system("PAUSE");
    return 0;

#endif //DEBUG_EXTR
//---------------------
#ifdef DEBUG_BOTH

    std::string str;
    std::cin >> str;
    if (str=="comp")
        Encode("test.txt", "test.comp");
    else
        Decode("test.comp", "test.txt");
    std::cout << "Success." << std::endl;
    system("PAUSE");
    return 0;

#endif //DEBUG_BOTH
}