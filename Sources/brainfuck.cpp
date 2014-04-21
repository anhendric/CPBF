#include "brainfuck.h"

unsigned short brainfuck_compile(char *in, unsigned short *out)
{
    short a_acc = 256;
    short s_acc = 256;
    
    unsigned int pc = 0;
    
    unsigned int loops[64];
    unsigned char l = 0;
    
    // Store PR in the stack so we can get it back whenever a subroutine call (JSR) overrides it
    out[pc++] = 0x4F22; // STS.L PR,@-R15
    
    for(char *p = in;;p++)
    {
        char q = *p;
        
        if(q!='+' && q!='-' && q!='<' && q!='>' && q!='[' && q!=']' && q!='.' && q!=',' && q!=0) continue;
        
        if(a_acc<256 && q!='+' && q!='-')
        {
            out[pc++] = 0x6340;                        // MOV.B @R4,R3
            out[pc++] = 0x7300 + (unsigned char)a_acc; // ADD #imm,R3
            out[pc++] = 0x2430;                        // MOV.B R3,@R4
            a_acc = 256;
        }
        else if(s_acc<256 && q!='<' && q!='>')
        {
            out[pc++] = 0x7400 + (unsigned char)s_acc; // ADD #imm,R4
            s_acc = 256;
        }
        
        switch(q)
        {
            // Accumulate consecutive - and + symbols, we don't really want a sequence of ADD #1,...
            // 256 is considered as a null value, which means that we haven't started to accumulate that value yet.
            case '+':
                if(a_acc==256) a_acc=0; // initialize accumulator
                a_acc++;
                break;
            case '-':
                if(a_acc==256) a_acc=0;
                a_acc--;
                break;
            // Same here, for > and <
            case '>':
                if(s_acc==256) s_acc=0;
                s_acc++;
                break;
            case '<':
                if(s_acc==256) s_acc=0;
                s_acc--;
                break;
            case '[':
                out[pc++] = 0x6240; // MOV.B @R4,R2
                out[pc++] = 0x2228; // TST R2,R2
                out[pc++] = 0x8900; // BT [end of loop], this will be set later
                loops[l++] = pc-1;
                break;
            case ']':
                if(l==0) return BF_ERR_MISSING_LOOP_START;
                out[pc++] = 0x6240; // MOV.B @R4,R2
                out[pc++] = 0x2228; // TST R2,R2
                out[pc++] = 0x8B00 + (unsigned char)(loops[--l]-pc); // BF [beginning of loop]
                out[loops[l]] += (pc-loops[l]-2); // setting last BT
                break;
            case ',':
                // We want to store the values of R4, R5 and R6 somewhere so we can take them back
                // once the function is called
                out[pc++] = 0x2F66; // MOV.L R6,@-R15
                out[pc++] = 0x2F56; // MOV.L R5,@-R15
                out[pc++] = 0x2F46; // MOV.L R4,@-R15
                out[pc++] = 0x450B; // JSR @R5
                out[pc++] = 0x0009; // NOP
                out[pc++] = 0x64F6; // MOV.L @R15+,R4
                out[pc++] = 0x65F6; // MOV.L @R15+,R5
                out[pc++] = 0x66F6; // MOV.L @R15+,R6
                break;
            case '.':
                // Same here
                out[pc++] = 0x2F66; // MOV.L R6,@-R15
                out[pc++] = 0x2F56; // MOV.L R5,@-R15
                out[pc++] = 0x2F46; // MOV.L R4,@-R15
                out[pc++] = 0x460B; // JSR @R6
                out[pc++] = 0x0009; // NOP
                out[pc++] = 0x64F6; // MOV.L @R15+,R4
                out[pc++] = 0x65F6; // MOV.L @R15+,R5
                out[pc++] = 0x66F6; // MOV.L @R15+,R6
                break;
        }
        if(q == 0) break;
    }
    
    if(l>0) return BF_ERR_MISSING_LOOP_END;
    
    out[pc++] = 0x4F26; // LDS.L @R15+,PR
    out[pc++] = 0x000B; // RTS
    out[pc++] = 0x0009; // NOP
    
    return BF_ERR_NONE;
}
