/*
    heikiko2D is a gameserver for the client application nodachi2D.
    Copyright (C) 2010-2011  Paul Predkiewicz

    heikiko2D is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

void NetworkHandler::iterateThroughWaitingSockets( unsigned int nbSockets )
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
