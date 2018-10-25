#ifndef __CharStack__
#define __CharStack__

#include <iostream>
#include <string>
#include "charlist.h"

using namespace std;

class CharStack
{
private:
    CharList list;
public:
    bool IsEmpty() const;
    void Push(char elem);
    char Pop();
    char Top() const;
    void Clear();

    friend ostream& operator<< (ostream& os, CharStack& stack);  // stream insertion operator
    operator string();                                          // casting operator
    //////////////////////////////////////////
    // Do not change the above prototype.
    // Add member function(s) below if you need.



    // Do not change the below.
    ///////////////////////////////////////////
};

#endif //__CharStack__

