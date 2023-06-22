//
//  BitRepresentation.h
//  atakan.demirel_Demirel_Atakan_6
//
//  Created by Atakan Demirel on 25.12.2022.
//

#ifndef BitRepresentation_h
#define BitRepresentation_h
#include <vector>
#include <string>

using namespace std;

template <typename T>
class BitRepresentation
{
private:
    T data;
    
public:
    
    BitRepresentation(T number): data(number) {}
    BitRepresentation(const vector<bool> &);
    string getBinary();
    string getHexadecimal();
    void setBit(unsigned int location);
    void unsetBit(unsigned int location);
    bool isBitSet(unsigned int location);
    T getNumber();
};



#include "BitRepresentation.cpp"

#endif /* BitRepresentation_h */
