#include "BitRepresentation.h"
#include <iostream>
using namespace std;

int main()
{
    unsigned int number = 31;
    BitRepresentation<unsigned int> s(number);

    cout << s.getNumber() << endl;
    cout << s.getBinary() << endl;
    s.setBit(48);
    cout << s.getBinary() << endl;
    s.setBit(5);
    cout << s.getNumber() << endl;
    cout << s.isBitSet(48) << endl;
    s.unsetBit(27);
    cout << s.getHexadecimal() << endl;

    vector<bool> v1 = { true, false, true, false };
    BitRepresentation<char> v(v1);
    cout << v.getBinary() << endl;
    cout << v.getHexadecimal() << endl;
    v.setBit(2);
    cout << v.getHexadecimal() << endl;
    v.unsetBit(0);
    cout << v.getBinary() << endl;
    v.setBit(31);
    cout << v.getBinary() << endl;
    cout << v.isBitSet(1) << endl;
    cout << v.getHexadecimal() << endl;

    return 0;
}
