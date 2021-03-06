/*
 *  CS3421 Assignment 4
 *  Name: Eric Grant
 *  
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//instruction data union
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

union hilo {
    unsigned long long x;
    struct
    {
        unsigned int lo:32;
        unsigned int hi:32;
    } parts;
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
    fprintf(stderr, "could not find inst with opcode %d\n", op);
    exit(0);
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
    fprintf(stderr, "could not find inst with opcode 0 and funct %d\n", op);
    exit(0);
}

//convert value to register
char* valueRegister(int reg){
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
    fprintf(stderr, "register %d does not exist\n", reg);
    exit(0);
}

void printInsruction(union instruction instr, FILE *outputf){
    if (instr.RType.op == 0)
    {
        //RType instructions -- ADD MORE EDGE CASES?
        if (instr.RType.funct == 12) //syscall
        {
            fprintf(outputf, "%s\n", 
            valueFunct(instr.RType.funct));
        } else if (instr.RType.funct == 24 || instr.RType.funct == 26) { //mult and div
            fprintf(outputf, "%s\t$%s,$%s\n",
            valueFunct(instr.RType.funct),
            valueRegister(instr.RType.rs),
            valueRegister(instr.RType.rt));
        } else if (instr.RType.funct == 16 || instr.RType.funct == 18) { //mfhi and mflo
            fprintf(outputf, "%s\t$%s\n",
            valueFunct(instr.RType.funct),
            valueRegister(instr.RType.rd));
        } else { //default
            fprintf(outputf, "%s\t$%s,$%s,$%s\n",
            valueFunct(instr.RType.funct),
            valueRegister(instr.RType.rd),
            valueRegister(instr.RType.rs),
            valueRegister(instr.RType.rt));
        }
    } else {
        //IType instructions -- ADD MORE EDGE CASES?
        if (instr.IType.op == 35 || instr.IType.op == 43) //sw, lw
        {
            fprintf(outputf, "%s\t$%s,%d($%s)\n", 
            valueOpcode(instr.IType.op),
            valueRegister(instr.IType.rt),
            instr.IType.imm,
            valueRegister(instr.IType.rs));
        } else if (instr.IType.op == 2) { //j
            fprintf(outputf, "%s\t%d\n",
            valueOpcode(instr.IType.op),
            instr.IType.imm);
        } else if (instr.IType.op == 4 || instr.IType.op == 5) { //beq, bne
            fprintf(outputf, "%s\t$%s,$%s,%d\n", 
            valueOpcode(instr.IType.op),
            valueRegister(instr.IType.rs),
            valueRegister(instr.IType.rt),
            instr.IType.imm);
        } else { //default
            fprintf(outputf, "%s\t$%s,$%s,%d\n", 
            valueOpcode(instr.IType.op),
            valueRegister(instr.IType.rt),
            valueRegister(instr.IType.rs),
            instr.IType.imm);
        }
    }

    return;
}

int main(int argc, char **argv) {
    //enum
    enum operationR{
        addu = 33,
        and = 36,
        div = 26,
        mfhi = 16,
        mflo = 18,
        mult = 24,
        or = 37,
        slt = 42,
        subu = 35,
        syscall = 12
    };

    enum operationI{
        addiu = 9,
        beq = 4,
        bne = 5,
        lw = 35,
        sw = 43,
        j = 2
    };

    enum reg{
        zero,
        at,
        v0,v1,
        a0,a1,a2,a3,
        t0,t1,t2,t3,t4,t5,t6,t7,
        s0,s1,s2,s3,s4,s5,s6,s7,
        t8,t9,
        k0,k1,
        gp,
        sp,
        fp,
        ra
    };

    //vars
    char testinput[12];
    int textsize;
    int datasize;
    int i = 0;
    union instruction *instrs;
    FILE *inputf = fopen(argv[1], "r");
    FILE *outputf = fopen("log.txt", "w+");

    //get text and data size
    fgets(testinput, 12, inputf);
    sscanf(testinput, "%d %d", &textsize, &datasize);

    //decode instructions
    instrs = malloc(textsize * sizeof(union instruction));
    fprintf(outputf, "insts:\n");
    for (i = 0; i < textsize; i++)
    {
        fgets(testinput, 12, inputf);
        sscanf(testinput, "%x", &(instrs[i].x));
        fprintf(outputf, "%4d: ", i);
        printInsruction(instrs[i], outputf);
    }
    fprintf(outputf, "\n");

    //decode data
    int *data;
    data = malloc(datasize * sizeof(int));
    int dataval;
    fprintf(outputf, "data:\n");
    for (i = 0; i < datasize; i++)
    {
        fgets(testinput, 12, inputf);
        sscanf(testinput, "%x", &dataval);
        data[i] = dataval;
        fprintf(outputf, "%4d: %d\n", i+textsize, dataval);
    }
    fprintf(outputf, "\n");

    //execution
    unsigned int pc = 0;
    int pcShift = 0;
    int regs[32];
    for (i = 0; i < 32; i++)
    {
        regs[i] = 0;
    }
    int hi = 0;
    int lo = 0;
    union hilo hilo;
    regs[gp] = textsize;
    int exit = 0;
    while(1 == 1){
        //exit on running over operations
        if (pc >= textsize)
        {
            fprintf(stderr, "PC is accessing data memory at address %d\n", pc);
            exit = 1;
        }

        if (exit == 1)
        {
            break;
        }

        //execute
        if (instrs[pc].RType.op == 0) //execute RTypes
        {
            if (instrs[pc].RType.funct == addu) {
                regs[instrs[pc].RType.rd] = regs[instrs[pc].RType.rs] + regs[instrs[pc].RType.rt];
            } else if (instrs[pc].RType.funct == and) {
                regs[instrs[pc].RType.rd] = regs[instrs[pc].RType.rs] & regs[instrs[pc].RType.rt];
            } else if (instrs[pc].RType.funct == div) {
                if (regs[instrs[pc].RType.rt] != 0)
                {
                    lo = regs[instrs[pc].RType.rs] / regs[instrs[pc].RType.rt];
                    hi = regs[instrs[pc].RType.rs] % regs[instrs[pc].RType.rt];
                } else {
                    fprintf(stderr, "divide by zero for instruction at %d\n", pc);
                    exit = 1;
                }
            } else if (instrs[pc].RType.funct == mfhi) {
                regs[instrs[pc].RType.rd] = hi;
            } else if (instrs[pc].RType.funct == mflo) {
                regs[instrs[pc].RType.rd] = lo;
            } else if (instrs[pc].RType.funct == mult) {
                hilo.x = regs[instrs[pc].RType.rs] * regs[instrs[pc].RType.rt];
                hi = hilo.parts.hi;
                lo = hilo.parts.lo;
            } else if (instrs[pc].RType.funct == or) {
                regs[instrs[pc].RType.rd] = regs[instrs[pc].RType.rs] | regs[instrs[pc].RType.rt];
            } else if (instrs[pc].RType.funct == slt) {
                regs[instrs[pc].RType.rd] = regs[instrs[pc].RType.rs] < regs[instrs[pc].RType.rt] ? 1 : 0;
            } else if (instrs[pc].RType.funct == subu) {
                regs[instrs[pc].RType.rd] = regs[instrs[pc].RType.rs] - regs[instrs[pc].RType.rt];
            } else if (instrs[pc].RType.funct == syscall) {
                if (regs[v0] == 1) {
                    printf("%d\n", regs[a0]);
                } else if (regs[v0] == 5) {
                    scanf("%d", &regs[v0]);
                } else if (regs[v0] == 10) {
                    fprintf(outputf, "PC: %d\n", pc);
                    fprintf(outputf, "inst: ");
                    printInsruction(instrs[pc], outputf);
                    fprintf(outputf, "exiting simulator\n");
                    exit = 1;
                }
            } else {
                fprintf(stderr, "Illegal instruction: Illegal combination of opcode and funct field values\n");
                exit = 1;
            }
        } else { //execute ITypes
            if (instrs[pc].IType.op == addiu) {
                regs[instrs[pc].IType.rt] = regs[instrs[pc].IType.rs] + instrs[pc].IType.imm;
            } else if (instrs[pc].IType.op == beq) {
                if (regs[instrs[pc].IType.rs] == regs[instrs[pc].IType.rt])
                {
                    pcShift = instrs[pc].IType.imm;
                }
            } else if (instrs[pc].IType.op == bne) {
                if (regs[instrs[pc].IType.rs] != regs[instrs[pc].IType.rt])
                {
                    pcShift = instrs[pc].IType.imm;
                }
            } else if (instrs[pc].IType.op == lw) {
                if (instrs[pc].IType.imm < datasize)
                {
                    regs[instrs[pc].IType.rt] = data[instrs[pc].IType.imm]; //hard coded assuming $gp is always used as register
                } else {
                    fprintf(stderr, "store outside of data memory at address %d\n", instrs[pc].IType.imm + textsize);
                    exit = 1;
                }
            } else if (instrs[pc].IType.op == sw) {
                if (instrs[pc].IType.imm < datasize)
                {
                    data[instrs[pc].IType.imm] = regs[instrs[pc].IType.rt]; //hard coded assuming $gp is always used as register
                } else {
                    fprintf(stderr, "store outside of data memory at address %d\n", instrs[pc].IType.imm + textsize);
                    exit = 1;
                }
            } else if (instrs[pc].JType.op == j) {
                pcShift = instrs[pc].JType.imm - pc;
            } else {
                fprintf(stderr, "Illegal instruction: Illegal combination of opcode and funct field values.\n");
                exit = 1;
            }
        }

        //prevent change to $zero
        regs[zero] = 0;

        //check if exit hit
        if (exit == 1)
        {
            break;
        }
        
        //print PC and instruction
        fprintf(outputf, "PC: %d\n", pc);
        fprintf(outputf, "inst: ");
        printInsruction(instrs[pc], outputf);
        fprintf(outputf, "\n");

        //print regs
        fprintf(outputf, "regs:\n");
        for (i = 0; i < 32; i++)
        {
            char* reg = malloc(6);
            strcpy(reg, "$");
            strcat(reg, valueRegister(i));
            fprintf(outputf, "%8s = %5d", reg, regs[i]);
            if ((i+1) % 4 == 0)
            {
                fprintf(outputf, "\n");
            }
            free(reg);
        }
        fprintf(outputf, "%8s = %5d", "$lo", lo);
        fprintf(outputf, "%8s = %5d", "$hi", hi);
        fprintf(outputf, "\n\n");

        //print data memory:
        fprintf(outputf, "data memory:\n");
        for (i = 0; i < datasize; i++)
        {
            fprintf(outputf, "   data[%3d] = %5d", i, data[i]);
            if ((i+1) % 3 == 0 && i != datasize - 1)
            {
                fprintf(outputf, "\n");
            }
        }
        
        fprintf(outputf, "\n\n\n");

        //increment PC
        if (pcShift == 0)
        {
            pc++;
        } else {
            pc += pcShift;
        }
        pcShift = 0;
    }

    //free allocated memory
    data = NULL;
    free(data);
    free(instrs);

    return 0;
}
