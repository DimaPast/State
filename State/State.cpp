#include <iostream>
#include <Windows.h>


class Context;

class State {
public:
    virtual void handle(Context& context) = 0;
    virtual ~State() = default;
};


class ConcreteStateA : public State {
public:
    void handle(Context& context) override;
};


class ConcreteStateB : public State {
public:
    void handle(Context& context) override;
};


class Context {
private:
    State* currentState;

public:
    Context(State* initialState) : currentState(initialState) {}

    void setState(State* newState) {
        currentState = newState;
    }

    void request() {
        currentState->handle(*this);
    }
};


void ConcreteStateA::handle(Context& context) {
    std::cout << "ConcreteStateA обробляє запит." << std::endl;
    
    context.setState(new ConcreteStateB);
    delete this;  
}

// ConcreteStateB (Реалізація для Конкретного стану B)
void ConcreteStateB::handle(Context& context) {
    std::cout << "ConcreteStateB обробляє запит." << std::endl;
    
    context.setState(new ConcreteStateA);
    delete this;  
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Context context(new ConcreteStateA);

    
    context.request();

    
    context.request();

    
    context.request();

    return 0;
}
