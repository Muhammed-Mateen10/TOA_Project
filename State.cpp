#include <bits/stdc++.h>
template <typename T>
State<T>::State(const std::string &name, bool isFinal) : name(name), isfinal(isFinal) {}

template <typename T>
void State<T>::addTransitions(std::shared_ptr<State<T>> to, T sym)
{
    if (transitions.find(sym) == transitions.end())
        transitions.insert(std::pair<T, std::shared_ptr<State<T>>>(sym, to));
    else
        throw "DFA cannot have 2 transitions for same symbol";
}

template <typename T>
void State<T>::displayState() const
{
    std::cout << "\nState Label:" << this->name << '\n';
    std::cout << "Transitions:";
    for (auto i : transitions)
        std::cout << "\nOn Input:" << i.first << ' ' << name << "->" << i.second.get()->name;
    std::cout << '\n';
}

template <typename T>
std::shared_ptr<State<T>> State<T>::nextState(char OnInput) const
{
    auto i = transitions.find(OnInput);
    if (i != transitions.end())
    {
        return i->second;
    }
    return nullptr;
}

template <typename T>
bool State<T>::HasOutEdgeon(std::shared_ptr<State<T>> s) const
{
    for (auto i : transitions)
        if (i.second == s)
            return true;
    return false;
}

template <typename T>
void State<T>::outputfor(std::shared_ptr<State<T>> s, T &k)
{
    for (auto [key, v] : transitions)
        if (v == s)
            k = key;
}