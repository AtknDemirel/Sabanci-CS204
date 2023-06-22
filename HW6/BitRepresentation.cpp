//
//  BitRepresentation.cpp
//  atakan.demirel_Demirel_Atakan_6
//
//  Created by Atakan Demirel on 25.12.2022.
//

#include "BitRepresentation.h"
#include <iostream>

template <typename T>
BitRepresentation<T>::BitRepresentation(const vector<bool> & boolVec)
{
    unsigned int bitSize = sizeof(T) * 8;
    data = 0;
    for (unsigned int i = 0; i < bitSize && i < boolVec.size(); i++)
    {
        data = data | ((int)boolVec[boolVec.size() - 1 - i] << i);
        //data <<= 1;
    }
    cout << getBinary() << endl;
    
}

string reverse(const string & binary)
{
    string result = "";
    if (binary.length() == 0)
        return result;
    for (unsigned long long i = binary.length(); i > 0; i--)
        result += binary.at(i - 1);
    
    return result;
}

template <typename T>
string BitRepresentation<T>::getBinary()
{
    string binary = "";
    unsigned int bitSize = sizeof(T) * 8;
    T copy = data;
    for (unsigned int i = 0; i < bitSize; i++)
    {
        if (copy & 1)
            binary += '1';
        else
            binary += '0';
        copy >>= 1;
    }
    return reverse(binary);
}

template <typename T>
string BitRepresentation<T>::getHexadecimal()
{
    if (data >= 0)
    {
        unsigned long long copy = data;
        string result = "";
        short remainder = 0;
        while (copy)
        {
            remainder = copy % 16;
            if (remainder >= 10)
            {
                result += char((remainder - 10) + 'A');
            }
            else
            {
                result += to_string(remainder);
            }
            copy /= 16;
        }
        unsigned int bitSize = sizeof(T) * 2;
        while (result.length() < bitSize)
            result += "0";
        
        return reverse(result);
    }
    else
    {
        long long copy = data;
        string result = "";
        short remainder = 0;
        while (copy)
        {
            remainder = copy % 16;
            if (remainder >= 10)
            {
                result += char((remainder - 10) + 'A');
            }
            else
            {
                result += to_string(remainder);
            }
            copy /= 16;
        }
        unsigned int bitSize = sizeof(T) * 2;
        while (result.length() < bitSize)
            result += "0";
        
        return reverse(result);
    }
}

template <typename T>
void BitRepresentation<T>::setBit(unsigned int location)
{
    unsigned int bitSize = sizeof(T) * 8;
    if (location > bitSize)
        return;
    T copy = data;
    copy >>= location;
    copy |= 1;
    copy <<= location;
    data = data | (1 << location);
}

template <typename T>
void BitRepresentation<T>::unsetBit(unsigned int location)
{
    unsigned int bitSize = sizeof(T) * 8;
    if (location > bitSize)
        return;
    data = data & ~(1 << location);
}

template <typename T>
bool BitRepresentation<T>::isBitSet(unsigned int location)
{
    unsigned int bitSize = sizeof(T) * 8;
    if (location > bitSize)
        return false;
    return data & (1 << location);
}

template <typename T>
T BitRepresentation<T>::getNumber()
{
    return data;
}
