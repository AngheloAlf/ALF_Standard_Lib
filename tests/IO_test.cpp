#include "ALF_std.h"

#include <iostream>
#include <string>

int main(){
    std::string outMessage("weaita: ");

    std::string output = ALF::IO::raw_input(outMessage);
    std::cout<<output<<std::endl;

    char *otherOut = ALF::IO::raw_input("la wea: ");
    std::cout<<otherOut<<std::endl;
    return 0;
}
