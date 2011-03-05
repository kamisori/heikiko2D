#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

struct networkFlags{
    bool Running;
    bool AcceptNew;
};

class NetworkHandler :public sf::Thread
{
    private:
        virtual void Run();
        sf::SelectorTCP selector;
        sf::SocketTCP listener;
    public:
        sf::Mutex* GlobalMutex_;
        networkFlags globalflags_;
        NetworkHandler(unsigned int Port, sf::Mutex* GlobalMutex);
        ~NetworkHandler();
};
#endif
