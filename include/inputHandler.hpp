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
