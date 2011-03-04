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
