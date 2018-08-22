#include "ALF_std.h"
#include <iostream>

int main(){
    ALF::BYTES::Bytes *bytes = new ALF::BYTES::Bytes("Ola k ase", 10);
    std::cout<<bytes->getBytes()<<std::endl;
    bytes->setBytes("autobus o k ase", 16);
    std::cout<<bytes->getBytes()<<std::endl;
    return 0;
}
