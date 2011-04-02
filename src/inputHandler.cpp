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

#include <inputHandler.hpp>

InputHandler::InputHandler(sf::Mutex* GlobalMutex)
{
    GlobalMutex_ = GlobalMutex;
    globalflags_.Running = true;
    globalflags_.Save = false;
    globalflags_.Stop = false;
    globalflags_.AcceptNew = false;
    Launch();
}
InputHandler::~InputHandler()
{
    Terminate();
}

void InputHandler::Run()
{
    int fails = 0;
    std::string input;
    std::cout << "Let's go..." << std::endl << std::endl;
    while( globalflags_.Running )
    {
        std::cout << "#? : ";
        std::cin >> input;
        std::cin.sync();
        std::cout << std::endl;

        if(input.compare("halt") == 0)
        {
            std::cout << "Comming to a grinding halt..." << std::endl;
            globalflags_.Stop = true;
            globalflags_.Save = false;
        }
        else if(input.compare("shutdown") == 0)
        {
            std::cout << "Shutting down..." << std::endl;
            globalflags_.Stop = true;
            globalflags_.Save = true;
        }
        else if(input.compare("save") == 0)
        {
            std::cout << "Saving..." << std::endl;
            globalflags_.Stop = false;
            globalflags_.Save = true;
        }
        else if(input.compare("open") == 0)
        {
            std::cout << "Opening listener..." << std::endl;
            globalflags_.AcceptNew = true;
        }
        else if(input.compare("close") == 0)
        {
            std::cout << "Closing listener..." << std::endl;
            globalflags_.DenyNew = true;
        }
        else if(input.compare("help") == 0 || input.compare("h") == 0 || input.compare("?") == 0  || fails > 1 )
        {
            if(fails > 1)
            {
                fails = 0;
                std::cout << "Didn't get it the first time, eh? No Problem, here we go again:" << std::endl;
            }

            std::cout << "help/h/?\tPrints this message." << std::endl;
            std::cout << "save\t\tSaves all data." << std::endl;
            std::cout << "shutdown\tSaves all data and shuts the server down." << std::endl;
            std::cout << "halt\t\tStops the server ungracefully." << std::endl;
            std::cout << "close\t\tDeny all incoming new connections." << std::endl;
            std::cout << "open\t\tAccept all incoming new connections." << std::endl;
            std::cout << std::endl;
        }
        else
        {
            fails++;
            std::cout << "Say what?" << std::endl;
        }
    }
}
