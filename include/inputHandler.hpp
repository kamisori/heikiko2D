#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <SFML/System.hpp>

struct inputFlags{
    bool Running;
    bool Stop;
    bool Save;
    bool AcceptNew;
    bool DenyNew;
};

class InputHandler :public sf::Thread
{
    private:
        virtual void Run();
    public:
        sf::Mutex* GlobalMutex_;
        inputFlags globalflags_;
        InputHandler(sf::Mutex* GlobalMutex);
        ~InputHandler();
};
#endif
