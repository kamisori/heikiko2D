#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct flags{
    bool Running;
    bool Stop;
    bool Save;
};

class InputHandler :public sf::Thread
{
    private:
        virtual void Run();
    public:
        sf::Mutex* GlobalMutex_;
        flags globalflags_;
        InputHandler(sf::Mutex* GlobalMutex);
        ~InputHandler();
};
#endif
