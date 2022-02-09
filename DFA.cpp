
DFA::DFA(size_t totalStates, const std::string &InitStateName, bool isinitfinal) : totalStates(totalStates)
{
    addState(InitStateName, isinitfinal);
}
bool DFA::DFAhasState(const std::string &any) const
{
    for (auto i : states)
        if (i.first == any)
            return true;
    return false;
}

void DFA::addTranstions(const std::string &source, const std::string &dest, char sym)
{
    if (!DFAhasState(source))
        throw source + " State " + "doesnt exist";
    if (!DFAhasState(dest))
        throw dest + " State " + "doesnt exist";
    std::pair<std::string, std::shared_ptr<State<char>>> j;
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

void DFA::addState(const std::string &name, bool isFinal)
{
    for (auto i : states)
        if (name == i.first)
            throw "State " + name + " Already exists";
    states.emplace_back(name, std::make_shared<State<char>>(name, isFinal));
}

bool DFA::checkinput(const std::string &input) const
{
    auto cur = states.at(0).second;
    for (auto i : input)
    {
        cur = cur.get()->nextState(i);
        if (cur == nullptr)
            return false;
    }
    if (cur->isfinal)
        return true;
    return false;
}

void DFA::displayStates() const
{
    std::cout << "\nStates:";
    std::cout << "\nInitial State : " << states.at(0).second->name;
    std::cout << "\nNon Final states : ";
    for (auto i : states)
    {
        if (!i.second->isfinal)
            std::cout << i.second->name << ' ';
    }
    std::cout << "\nFinal State(s) : ";
    for (auto i : states)
    {
        if (i.second->isfinal)
            std::cout << i.second->name << ' ';
    }
}

void DFA::displayDFA() const
{
    std::cout << "\n DFA \n";
    for (auto i : states)
    {
        i.second.get()->displayState();
    }
}

std::string format(std::string x)
{
    int i = 0;
    for (i = 0; i < x.size() - 1; ++i)
    {
        if (x[i] == '^' && x[i + 1] != '+')
        {
            x[i] = x[i + 1];
        }
    }
    x[i + 1] = '\0';
    return x;
}
void DFA::convertDFAtoGTG()
{
    GTG gtg;
    for (auto &i : states)
    {
        if (i.second.get()->HasOutEdgeon(states.at(0).second)) //checking if initial has any incoming edges
        {
            states.insert(states.begin(), {"init", std::make_shared<State<char>>("init", false)});
            states.at(0).second.get()->addTransitions(states.at(1).second, '^');
            break;
        }
    }
    int flag = hasmulfinalstates();
    if (flag || finStatehasoutEdge())
    {
        states.emplace_back("fin", std::make_shared<State<char>>("fin", true));
        for (auto &i : states)
        {
            if (i.second.get()->isfinal && i.second.get()->name != "fin")
            {
                i.second.get()->isfinal = false;
                i.second.get()->addTransitions((*(states.end() - 1)).second, '^');
            }
        }
    }
    for (auto i : states)
        gtg.addState(i.first, i.second.get()->isfinal);
    for (auto i : states)
        for (auto transi : i.second.get()->transitions)
        {
            std::string sym = "";
            gtg.addTransition(i.first, transi.second.get()->name, sym += transi.first);
        }
    gtg.display();
    std::string regex;
    if (flag)
        regex = gtg.extractre();
    else
        regex = gtg.extractre2();
    regex = format(regex);
    std::cout << "Regular Expression is: " << regex;
}

bool DFA::finStatehasoutEdge() const
{
    for (auto i : states)
    {
        if (i.second.get()->isfinal && !i.second.get()->transitions.empty())
            return true;
    }
    return false;
}

void DFA::DFAtoRegex()
{
    convertDFAtoGTG();
}

bool DFA::hasmulfinalstates() const
{
    int cnt = 0;
    for (auto i : states)
    {
        if (i.second.get()->isfinal)
        {
            ++cnt;
            if (cnt > 1)
                return true;
        }
    }
    return false;
}
