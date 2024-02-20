#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdint>
#include <utility>
#include<random>
#include<algorithm>
#include "FiniteAutomaton.h"

class Grammar
{
public:
    Grammar() = default;
    ~Grammar() = default;
    bool verifyGrammar();
    bool isRegular();
    void generateWord();
    std::string getGenerateWord();
    std::pair<std::string, std::string>generareRandom(std::vector<std::pair<std::string, std::string>>& v);
    void printGrammar();
    void readGrammar();
   
    bool intersectionVnWithVt();//1) VN intersecat VT = vida 
    bool isStartInVn();//2) Start apartine Vn;
    bool hasNonterminalOnLeft();//3) pentru fiecare regulă, membrul stâng conține cel puțin un neterminal 
    bool hasSProduction();//4) există cel puțin o producție care are în stânga doar S 
    bool onlyElementFromVnAndVt(); //5) fiecare producție conține doar elemente din VN și VT
    bool CanGenerateLambda() const noexcept;

    friend std::ostream& operator<<(std::ostream& cout, Grammar& word);
    friend std::istream& operator>>(std::istream& cin, Grammar& word);

    std::vector<char> getVn() const;
    std::vector<char> getVt() const;
    char getStart() const;
    std::vector<std::pair<std::string, std::string>> getProduction() const;

private:
    static const char lambda = '@';
    std::vector<char>Vn, Vt;
    std::vector<std::pair<std::string, std::string>>Production;
    char Start;
};