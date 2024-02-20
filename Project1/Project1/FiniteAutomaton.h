#pragma once
#include"Grammar.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>


class FiniteAutomaton
{
public:
    FiniteAutomaton() {};
    FiniteAutomaton(std::vector<char> states, std::vector<char> alphabet, char initialState, std::vector<char> finalStates);
    ~FiniteAutomaton() = default;
    FiniteAutomaton(const FiniteAutomaton&);
    //VerifyAutomaton:
    bool VerifyInitailStateToFinalState();
    bool VerifyUniqueStates();
    bool VerifyUniqueAlphabet();
    bool VerifyIntialState();
    bool VerifyFinalState();
    bool VerifyTransitions();
    void initializationStates();
    void initializationTransition(std::vector<std::pair<std::string, std::string>> production);
    bool VerifyAutomaton();
    void PrintAutomaton();
    bool CheckWord(const char& currentState, const std::string& currentWord) const;
    bool IsDeterministic();

    bool IsValidState(char state) const;
    bool IsValidSymbol(char symbol) const;

    // Define setters
    void setStates(std::vector<char> states);
    void setAlphabet(std::vector<char> alphabet);
    void setInitialState(char initialState);
    void setTransition(std::unordered_map<char, std::unordered_map<char, std::vector<char>>> transition);
    void setFinalStates(std::vector<std::pair<std::string, std::string>> production, std::vector<char>states);
    char getRandomCharacter();
    // Define getters
    std::vector<char> getStates() const;
    std::vector<char> getAlphabet() const;
    char getInitialState() const;
    std::unordered_map<char, std::unordered_map<char, std::vector<char>>> getTransition() const;
    std::vector<char> getFinalStates() const;

private:
    std::vector<char> m_states; // Q = Vn reunit cu {T}
    std::vector<char> m_alphabet; // sigma = Vt
    char m_initialState; // q0 = start -> starea initiala
    std::unordered_map<char, std::unordered_map<char, std::vector<char>>> m_transition; // δ
    //A a -> C
    //A b -> C
    std::vector<char> m_finalStates; // F -> multime starilor finale
};
