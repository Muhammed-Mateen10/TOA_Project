#include <bits/stdc++.h>
#include "GTG.hpp"

class DFA
{
    const size_t totalStates;
    std::vector<std::pair<std::string, std::shared_ptr<State<char>>>> states;

public:
    DFA(size_t, const std::string &, bool);
    void addTranstions(const std::string &, const std::string &, char);
    void addState(const std::string &, bool);

    void DFAtoRegex();

    void convertDFAtoGTG();

    bool checkinput(const std::string &) const;
    bool DFAhasState(const std::string &) const;
    void displayStates() const;
    void displayDFA() const;
    bool hasmulfinalstates() const;
    bool finStatehasoutEdge() const;
};
#include "DFA.cpp"