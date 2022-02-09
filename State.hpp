#include <memory>
#include <map>

template <typename T>
class State
{
public:
    State(const std::string &, bool);
    const std::string name;
    void addTransitions(std::shared_ptr<State<T>>, T);
    std::shared_ptr<State<T>> nextState(char) const;
    void displayState() const;
    bool HasOutEdgeon(std::shared_ptr<State<T>>) const;

    bool isfinal;
    void outputfor(std::shared_ptr<State<T>>, T &);
    std::map<T, std::shared_ptr<State<T>>> transitions;

private:
};
#include "State.cpp"
