﻿//
// Created by dlely on 2020/11/13.
//

#ifndef MYCOMPILER_MIPSTRANSLATOR_H
#define MYCOMPILER_MIPSTRANSLATOR_H

#include "IRCodeManager.h"
#include "SymbolTable.h"
#include "ActiveOptimize.h"

#define MIPS_PRINT(word) mipsFile << word << "\n";
#define MIPS_CODE(code) mipsFile << "\t" << code << "\n";

#define p_reg (isGlobal ? $gp : $fp)

#define RD1 thisCode->obj[0]
#define RS2 thisCode->obj[1]
#define RT3 thisCode->obj[2]

#define $gp reg_gp
#define $fp reg_fp

#define CONDITION(condition, str1, str2, str3, str4)\
if (branch_when_true) {\
if (isImm1 && isImm2) {\
if (condition) {\
MIPS_CODE("j\t" << (thisCode->p_next->obj[0].str))\
}\
} else if (!isImm1 && isImm2) {\
MIPS_CODE(str1 << "\t\t" << rs2s << ",\t" << to_string(value2) << ",\t" << (thisCode->p_next->obj[0].str))\
} else if (isImm1 && !isImm2) {\
MIPS_CODE(str2 << "\t\t" << rt3s << ",\t" << to_string(value1) << ",\t" << (thisCode->p_next->obj[0].str))\
} else {\
MIPS_CODE(str1 << "\t\t" << rs2s << ",\t" << rt3s << ",\t" << (thisCode->p_next->obj[0].str))\
}\
} else {\
if (isImm1 && isImm2) {\
if (!(condition)) {\
MIPS_CODE("j\t" << (thisCode->p_next->obj[0].str))\
}\
} else if (!isImm1 && isImm2) {\
MIPS_CODE(str3 << "\t\t" << rs2s << ",\t" << to_string(value2) << ",\t" << (thisCode->p_next->obj[0].str))\
} else if (isImm1 && !isImm2) {\
MIPS_CODE(str4 << "\t\t" << rt3s << ",\t" << to_string(value1) << ",\t" << (thisCode->p_next->obj[0].str))\
} else {\
MIPS_CODE(str3 << "\t\t" << rs2s << ",\t" << rt3s << ",\t" << (thisCode->p_next->obj[0].str))\
}\
}

#define PMMD_REG_JUDGE \
if (RD1.str[0] == '@') {\
int rdRegNum = getTRegFree(RD1.str);\
if (rdRegNum != -1) {\
saveToMemory = false;   \
rd1s = "$t" + to_string(rdRegNum);\
}\
} else {\
int srdRegNum = getSRegName(RD1.str);\
if(srdRegNum != -1) {\
saveToMemory = false;\
rd1s = "$s" + to_string(srdRegNum);\
}\
}\

class MipsTranslator {
private:
    string reg_gp = "$gp";
    string reg_fp = "$fp";

    explicit MipsTranslator(ofstream &mipsFile, IRCodeManager &irCode, ActiveOptimize &pronActive, SymbolTable &symbolTable);

    ofstream &mipsFile;
    IRCodeManager &irCode;
    ActiveOptimize &activeOpt;
    SymbolTable &symbolTable;

    void translateCode(FuncSym *funcPtr, const list<ThreeAddCode *>& codeList);

public:
    static MipsTranslator &getInstance(ofstream &mipsFile, IRCodeManager &irCode, ActiveOptimize &pronActive, SymbolTable &symbolTable);

    void translate();

    void loadValue(GoalObject &goalObject, string &regName, bool ifGen, bool &isImm, int &value);

    void loadValue(GoalObject &goalObject, string &regName, bool ifGen, bool &isImm, int &value, bool &regChange);

    void saveValue(string &obj, const string &regName);

    int getTRegName(string &name);

    int getTRegFree(string &name);

    int getSRegName(string &name);

    int getSRegFree(string &name);
};


#endif //MYCOMPILER_MIPSTRANSLATOR_H
