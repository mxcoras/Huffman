/*
*Version 0.4
*by Mx, Nov. 23
*/

#include "include/encode.h"
#include "include/decode.h"

int main(int argc, char *argv[])
{
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
}