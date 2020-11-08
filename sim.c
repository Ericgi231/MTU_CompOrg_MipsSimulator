/*
 *  CS3421 Assignment 4
 *  Name: Eric Grant
 *
 */
#include <stdio.h>

//RType data union
union instruction {
    unsigned int x;
    struct
    {
        unsigned int funct:6;
        unsigned int shamt:5;
        unsigned int rd:5;
        unsigned int rt:5;
        unsigned int rs:5;
        unsigned int op:6;
    } RType;
    struct
    {
        unsigned int imm:16;
        unsigned int rt:5;
        unsigned int rs:5;
        unsigned int op:6;
    } IType;
    struct
    {
        unsigned int imm:26;
        unsigned int op:6;
    } JType;
};

//convert value to opcode
char* valueOpcode(int op){
    if (op == 9)
    {
        return "addiu";
    }
    if (op == 4)
    {
        return "beq";
    }
    if (op == 5)
    {
        return "bne";
    }
    if (op == 35)
    {
        return "lw";
    }
    if (op == 43)
    {
        return "sw";
    }
    if (op == 2)
    {
        return "j";
    }
}

//convert value to funct
char* valueFunct(int op){
    if (op == 33)
    {
        return "addu";
    }
    if (op == 36)
    {
        return "and";
    }
    if (op == 26)
    {
        return "div";
    }
    if (op == 16)
    {
        return "mfhi";
    }
    if (op == 18)
    {
        return "mflo";
    }
    if (op == 24)
    {
        return "mult";
    }
    if (op == 37)
    {
        return "or";
    }
    if (op == 42)
    {
        return "slt";
    }
    if (op == 35)
    {
        return "subu";
    }
    if (op == 12)
    {
        return "syscall";
    }
}

//convert value to register
char* registerValue(int reg){
    if (reg == 0) {
        return "zero";
    }
    if (reg == 1) {
        return "at";
    }
    if (reg == 2) {
        return "v0";
    }
    if (reg == 3) {
        return "v1";
    }
    if (reg == 4) {
        return "a0";
    }
    if (reg == 5) {
        return "a1";
    }
    if (reg == 6) {
        return "a2";
    }
    if (reg == 7) {
        return "a3";
    }
    if (reg == 8) {
        return "t0";
    }
    if (reg == 9) {
        return "t1";
    }
    if (reg == 10) {
        return "t2";
    }
    if (reg == 11) {
        return "t3";
    }
    if (reg == 12) {
        return "t4";
    }
    if (reg == 13) {
        return "t5";
    }
    if (reg == 14) {
        return "t6";
    }
    if (reg == 15) {
        return "t7";
    }
    if (reg == 16) {
        return "s0";
    }
    if (reg == 17) {
        return "s1";
    }
    if (reg == 18) {
        return "s2";
    }
    if (reg == 19) {
        return "s3";
    }
    if (reg == 20) {
        return "s4";
    }
    if (reg == 21) {
        return "s5";
    }
    if (reg == 22) {
        return "s6";
    }
    if (reg == 23) {
        return "s7";
    }
    if (reg == 24) {
        return "t8";
    }
    if (reg == 25) {
        return "t9";
    }
    if (reg == 26) {
        return "k0";
    }
    if (reg == 27) {
        return "k1";
    }
    if (reg == 28) {
        return "gp";
    }
    if (reg == 29) {
        return "sp";
    }
    if (reg == 30) {
        return "fp";
    }
    if (reg == 31) {
        return "ra";
    }
}

int main(int argc, char **argv) {
    //vars
    char testinput[12];
    int textsize;
    int datasize;
    union instruction *instrs;
    FILE *inputf = fopen(argv[1], "r");
    FILE *outputf = fopen("log.txt", "w+");

    fgets(testinput, 12, inputf);
    sscanf(testinput, "%d %d", &textsize, &datasize);

    int regs[32];
    int *data;
    data = malloc(datasize * sizeof(int));
    unsigned int pc;
    int dataval;

    //decode
    fprintf(outputf, "insts:\n");
    instrs = malloc(textsize * sizeof(union instruction));
    for (int i = 0; i < textsize; i++)
    {
        fgets(testinput, 12, inputf);
        sscanf(testinput, "%x", &(instrs[i].x));
        if (instrs[i].RType.op == 0)
        {
            fprintf(outputf, "%5d: %s\n", i, valueFunct(instrs[i].RType.funct));
        } else {
            fprintf(outputf, "%5d: %s\n", i, valueOpcode(instrs[i].IType.op));
        }
    }

    fprintf(outputf, "\ndata:\n");
    
    for (int i = 0; i < datasize; i++)
    {
        fgets(testinput, 12, inputf);
        sscanf(testinput, "%x", &dataval);
        data[i] = dataval;
        fprintf(outputf, "%5d: %d\n", i+textsize, dataval);
    }

    fprintf(outputf, "\n");

    //execution
    //while(1==1){

    //}

    return 0;
}
