#include <bits/stdc++.h>
#include "State.hpp"

class GTG
{
    std::vector<std::pair<std::string, std::shared_ptr<State<std::string>>>> states;

public:
    GTG() {}
    void addState(const std::string &, bool isfinal);
    void addTransition(const std::string &, const std::string &, const std::string &);
    void removetransitions(std::pair<std::string, std::shared_ptr<State<std::string>>>);
    std::string extractre();
    int addparalleltransition(std::pair<std::string, std::shared_ptr<State<std::string>>>);
    std::string removeselfloop(std::pair<std::string, std::shared_ptr<State<std::string>>>);
    std::string extractre2();
    void display() const;
};
#include "GTG.cpp"