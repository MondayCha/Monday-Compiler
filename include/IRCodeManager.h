﻿//
// Created by dlely on 2020/11/11.
//

#ifndef MYCOMPILER_IRCODEMANAGER_H
#define MYCOMPILER_IRCODEMANAGER_H

#include <iostream>
#include <string>
#include <list>
#include "typeList.h"

using namespace std;

class ThreeAddCode;

struct stringData {
    string label;
    string content;
};

class IRCodeManager {
private:
    explicit IRCodeManager(ofstream &tmpCodeFile);

    list<ThreeAddCode *> threeAddCodeList;
    list<stringData> stringDataList;
public:
    ofstream &ircodeFile;

    static IRCodeManager &getInstance(ofstream &tmpCodeFile);

    void addThreeAddCode(ThreeAddCode *code);

    void addStringData(stringData pronString);

    list<ThreeAddCode *> getThreeAddCodeList();

    list<stringData> getStringDataList();

    bool updateLastCode(string &ans);
};

struct GoalObject {
    int branch;
    string str; // lower
    SymbolType type;
    int num;
};

class ThreeAddCode {
private:
    OperatorType op;
    GoalObject obj[3];
    ThreeAddCode *p_next = nullptr;

    friend class IRCodeManager;

    friend class MipsTranslator;

    friend class FuncSym;

    friend class ActiveOptimize;

    void setObj(int index, string pronStr);

    void setObj(int index, SymbolType pronSym);

    void setObj(int index, int pronNum);

    void setNext(ThreeAddCode *pron_next);

public:
    ThreeAddCode(OperatorType op, string rd, string rs, string rt);

    ThreeAddCode(OperatorType op, SymbolType rd, string rs, string rt);

    ThreeAddCode(OperatorType op, SymbolType rrd, string rrs, int rrt);

    ThreeAddCode(OperatorType op, SymbolType rrd, int rrs, string rrt);

    ThreeAddCode(OperatorType op, string rrd, string rrs, int rrt);

    ThreeAddCode(OperatorType op, string rrd, int rrs, string rrt);

    ThreeAddCode(OperatorType op, string rrd, int rrs, int rrt);

    ThreeAddCode(OperatorType op, string rrd, SymbolType rrs, string rrt);

    ThreeAddCode(OperatorType op, int rrd, SymbolType rrs, string rrt);

    string toString();

    string opTypeToString(OperatorType op);

    string branchToString(int index);

    ThreeAddCode *getNext();

    string toMidString();
};

#endif //MYCOMPILER_IRCODEMANAGER_H
