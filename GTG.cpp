#include <bits/stdc++.h>
// bool GTG::GTGhasState(const std::string &any) const
// {
//     for (auto i : states)
//         if (i.first == any)
//             return true;
//     return false;
// }
void GTG::display() const
{
    std::cout << "\n GTG \n";
    for (auto i : states)
    {
        i.second.get()->displayState();
    }
}

void GTG::addTransition(const std::string &source, const std::string &dest, const std::string &sym)
{
    std::pair<std::string, std::shared_ptr<State<std::string>>> j;
    for (auto i : states)
        if (i.first == dest)
        {
            j = i;
            break;
        }
    for (auto i : states)
    {
        if (i.first == source)
        {
            i.second.get()->addTransitions(j.second, sym);
        }
    }
}

void GTG::addState(const std::string &name, bool isFinal)
{
    states.emplace_back(name, std::make_shared<State<std::string>>(name, isFinal));
}

std::string GTG::extractre()
{
    for (auto i = states.rbegin(); i != states.rend(); ++i)
    {
        if (i == states.rend() - 1) // initial state
            continue;
        if (!((*i).second.get()->isfinal))
        {

            int ret = 1;
            while (ret == 1)
            {
                ret = addparalleltransition(*i);
            }
            for (auto [k, v] : (*i).second.get()->transitions)
            {
                if (v.get()->name != (*i).first)
                    addparalleltransition({v.get()->name, v});
            }
            removetransitions(*i);
            remove(states.begin(), states.end(), *i);
            states.pop_back();
            // ++i;
        }
    }
    addparalleltransition(states.at(0));
    // states.at(0).second.get()->transitions.erase("^");
    for (auto [k, v] : states.at(0).second.get()->transitions)
    {
        if (v.get()->isfinal)
            return k;
    }
}
int GTG::addparalleltransition(std::pair<std::string, std::shared_ptr<State<std::string>>> rem)
{
    for (auto [k, v] : rem.second.get()->transitions)
    {
        for (auto [key, val] : rem.second.get()->transitions)
        {
            if (key == k)
                continue;
            else
            {
                if (v.get()->name == val.get()->name)
                { //same state multiple ouputs
                    rem.second.get()->addTransitions(v, "(" + k + "+" + key + ")");
                    rem.second.get()->transitions.erase(k);
                    rem.second.get()->transitions.erase(key);
                    return 1;
                }
            }
        }
    }
    return 0;
}

std::string GTG::removeselfloop(std::pair<std::string, std::shared_ptr<State<std::string>>> rem)
{
    std::string ret;
    for (auto [k, v] : rem.second.get()->transitions)
    {
        if (v.get()->name == rem.first)
        {
            ret += k;
            return "(" + ret + ")" + "*";
        }
    }
    return ret;
}

void GTG::removetransitions(std::pair<std::string, std::shared_ptr<State<std::string>>> toremove)
{
    for (auto &i : states)
    {
        if (i == toremove)
            continue;

        std::string r;
        r += removeselfloop(toremove);
        std::string ou;
        i.second.get()->outputfor(toremove.second, ou);
        if (!ou.empty())
        {
            i.second.get()->transitions.erase(ou);
            ou += r;
            for (auto [k, v] : toremove.second.get()->transitions)
            {
                i.second.get()->transitions.erase(r);
                i.second.get()->addTransitions(v, ou + k);
            }
        }
    }
    toremove.second.get()->transitions.clear();
}

std::string GTG::extractre2()
{
    int x = 0;
    for (auto i = states.begin(); i != states.end(); ++i)
    {
        if (x == 0) // initial state
        {
            ++x;
            continue;
        }
        if (!((*i).second.get()->isfinal))
        {

            int ret = 1;
            while (ret == 1)
            {
                ret = addparalleltransition(*i);
            }
            for (auto [k, v] : (*i).second.get()->transitions)
            {
                if (v.get()->name != (*i).first)
                    addparalleltransition({v.get()->name, v});
            }
            removetransitions(*i);
            remove(states.begin(), states.end(), *i);
            states.pop_back();
            --i;
        }
    }
    addparalleltransition(states.at(0));

    // states.at(0).second.get()->transitions.erase("^");
    for (auto [k, v] : states.at(0).second.get()->transitions)
    {
        if (v.get()->isfinal)
            return k;
    }
}