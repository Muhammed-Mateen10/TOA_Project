#include "DFA.hpp"
int main()
{

    //DFA 1
    freopen("input2.txt", "r", stdin);
    int statescount;
    char output;
    std::string statename;
    std::string src;
    std::string dest;

    int isfinal;
    std::cin >> statescount >> statename >> isfinal;
    DFA dfa(statescount, statename, isfinal);
    for (int i = 0; i < statescount - 1; ++i)
    {
        std::cin >> statename >> isfinal;
        dfa.addState(statename, isfinal);
    }
    while (std::cin >> src >> dest >> output)
    {
        dfa.addTranstions(src, dest, output);
    }
    dfa.displayDFA();
    dfa.DFAtoRegex();
}