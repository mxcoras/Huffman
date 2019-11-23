/*
*Version 0.2
*by Mx, Nov. 23
*/

#include "include/tree.h"
#include "include/encode.h"
#include "include/decode.h"

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        std::string fileName = argv[2];
        std::string wrtName = argv[3];
        if (argv[1] == "comp")
            Encode(fileName, wrtName);
        else if (argv[1] == "extr")
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