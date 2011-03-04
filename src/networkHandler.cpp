
#include <networkHandler.hpp>


NetworkHandler::NetworkHandler(sf::Mutex* GlobalMutex)
{
    if(listener.Listen(42235))
    {
        globalflags_.Running = true;
        globalflags_.AcceptNew = false;
        this->selector.Add(listener);
        GlobalMutex_ = GlobalMutex;
        Launch();
    }
    else
    {
        std::cout << "Can't open a socket on port 42235.";
        exit(1);
    }
}
NetworkHandler::~NetworkHandler()
{

    //disconnect all clients first
    this->selector.Clear();
    Terminate();
}

void NetworkHandler::Run()
{
    while( globalflags_.Running )
    {
        unsigned int nbSockets = selector.Wait();

        for( unsigned int i = 0; i < nbSockets; i++ )
        {
            sf::SocketTCP iterator = selector.GetSocketReady(i);

            if(iterator == listener)
            {
                sf::IPAddress address;
                sf::SocketTCP newClient;
                listener.Accept(newClient, &address);

                if(globalflags_.AcceptNew)
                {
                    selector.Add(newClient);
                    std::cout << "Client connected: " << address << std::endl;
                }
                else
                {
                    newClient.Close();
                    std::cout << "Client knocked but was rejected: " << address << std::endl;
                }
            }
            else
            {

            }
        }
    }
}
