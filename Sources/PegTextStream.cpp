#include "PegTextStream.h"

PegTextStream& PegTextStream::operator <<(char* s)
{
    target->Append(s);
    target->Resize(target->mReal);
    return *this;
}

PegTextStream& PegTextStream::operator <<(char c)
{
    PEGCHAR s[2] = {c, 0};
    target->Append(s);
    target->Resize(target->mReal);
    return *this;
}

PegTextStream& PegTextStream::operator <<(int i)
{
    PEGCHAR s[10];
    s[9] = 0;
    
    bool n = false;
    int k = 8;
    if(i<0) {i=-i;n=true;}
    
    do
    {
        s[k--] = '0'+(i%10);
        i/=10;
    } while(i);
     
     if(n) s[k--] = '-';
     PEGCHAR *s2 = s+k+1;
     
     target->Append(s2);
     target->Resize(target->mReal);
     return *this;
}

