#include <networkHandler.hpp>


NetworkHandler::NetworkHandler(unsigned int Port, sf::Mutex* GlobalMutex)
{
    if(listener.Listen(Port))
    {
        globalflags_.Running = true;
        globalflags_.AcceptNew = false;
        this->selector.Add(listener);
        GlobalMutex_ = GlobalMutex;
        Launch();
    }
    else
    {
        std::cout << "Can't open a socket on port " << Port << ".";
        exit(1);
    }
}
NetworkHandler::~NetworkHandler()
{
    this->selector.Clear();
    Terminate();
}

void NetworkHandler::Run()
{
    while( globalflags_.Running )
    {
        iterateThroughWaitingSockets(selector.Wait());
    }
}

void NetworkHandler::iterateThroughWaitingSockets( int nbSockets )
{
	for( unsigned int i = 0; i < nbSockets; i++ )
	{
		sf::SocketTCP newSocket = selector.GetSocketReady(i);

		if(newSocket == listener)
		{
			handleNewClient();
		}
		else
		{
			handleKnownClient( newSocket );
		}
	}
}

void NetworkHandler::handleNewClient()
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

void NetworkHandler::handleKnownClient(sf::SocketTCP newSocket)
{
	sf::Packet packet;
	if(newSocket.Receive(packet) == sf::Socket::Done)
	{
		std::string message;
		packet >> message;
		std::cout << message << std::endl;
	}
	else
	{
		selector.Remove(newSocket);
	}
}
