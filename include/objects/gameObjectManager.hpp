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

#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <objects/spacialObject.hpp>
#include <objects/material.hpp>

namespace objects
{
    typedef std::vector< std::string > FileObject;
    typedef std::vector< FileObject > FileData;

    class GameObjectManager
    {
    	public:
            FileData* parseFile( std::string* fileName );

            void loadMaterials( std::string materialFile );
            void loadObjects( std::string spacialObjectsFile );

            Material* provideMaterial( std::string materialId );

            SpacialObject* nextSpacialObject( int current );

    		GameObjectManager();
    		~GameObjectManager();
    	private:
    	FileObject* parseFileObject( std::string* object, std::string* dataDivider );
    	std::string fetchFile( std::string* fileName );

    	SpacialObject*                      player_;
    	std::vector< SpacialObject* >       spacialObjects_;
    	std::vector< Material* >            materialLibrary_;
    };

}

#endif
