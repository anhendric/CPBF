#ifndef TEXTSTREAM_H
#define TEXTSTREAM_H

#include "ClassPad.h"

class PegTextStream
{
    protected:
        PegTextBox* target;
    public:
        PegTextStream() {target = 0;}
        PegTextStream(PegTextBox* t) {target = t;}
        virtual ~PegTextStream() {}
        
        void SetTarget(PegTextBox* t) {target = t;}
        
        PegTextStream& operator <<(char* s);
        PegTextStream& operator <<(char c);
        PegTextStream& operator <<(int i);
};

#endif
