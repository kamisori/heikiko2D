#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <objects/spacialObject.hpp>
#include <objects/gameObjectManager.hpp>
namespace objects{

    std::string GameObjectManager::fetchFile( std::string* fileName )
    {
        std::ifstream ifs( fileName->c_str(), std::ifstream::in );
        char* buffer;
        if( ifs.is_open() ){
            int length;

            ifs.seekg( 0,std::ios::end );
            length = ifs.tellg();
            ifs.seekg( 0,std::ios::beg );

            buffer = new char[ length +1];
            for(int i = 0; i <= length; i++){
                buffer[i]='\0';
            }

            ifs.read( buffer, length );
            ifs.close();
            std::string outBuff(buffer);

            delete buffer;
            return outBuff;
        }
        std::cout << "File could not be opened: " << fileName << std::endl;
        exit(1);
    }

    FileData* GameObjectManager::parseFile( std::string* fileName )
    {
        std::string fileContent;
        fileContent.clear();
        fileContent.assign( fetchFile( fileName ) );

        if(fileContent.length() > 0)
        {
            std::string objectDivider ("\r\n");
            std::string fieldDivider (";");

            size_t previousObject = 0;
            size_t nextObject = 0;
            size_t objectLength = 0;
            FileData* tmpData = new FileData();

            do
            {
                nextObject = fileContent.find( objectDivider, previousObject );
                if( nextObject == std::string::npos )
                {
                    nextObject = fileContent.length();
                }
                objectLength = nextObject - previousObject;
                if(objectLength > 0)
                {
                    std::string temporaryObjectString = fileContent.substr( previousObject, objectLength );

                    FileObject* tmpObject = parseFileObject( &temporaryObjectString, &fieldDivider );
                    tmpData->push_back( (*tmpObject) );
                }
                previousObject = nextObject + objectDivider.length();
            }
            while( (previousObject < fileContent.length()) && ( nextObject < fileContent.length() ) );
            return tmpData;
        }

        std::cout << "File could not be read: " << fileName << std::endl;
        exit(1);
    }

    FileObject* GameObjectManager::parseFileObject( std::string* object, std::string* fieldDivider )
    {
        size_t previousField = 0;
        size_t nextField = 0;
        size_t fieldLength = 0;
        FileObject* tmpObject = new FileObject();

        do
        {
            nextField = object->find( (*fieldDivider), previousField );
            if( nextField == std::string::npos )
            {
                nextField = object->length();
            }
            fieldLength = nextField - previousField;
            if(fieldLength > 0)
            {
                std::string tmpstr = object->substr( previousField, fieldLength );
                tmpObject->push_back( tmpstr );
            }
            previousField = nextField + fieldDivider->length();
        }
        while( ( previousField < object->length()) && ( nextField < object->length()) );
        return tmpObject;
    }

    void GameObjectManager::loadMaterials( std::string materialFile )
    {
        FileData* dataFromFile = parseFile( &materialFile );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileObject::iterator itEntry;
            FileObject tmp = (*itData);
            itEntry = tmp.begin();

            std::string materialId = (*itEntry);
            itEntry++;
            std::string visualAppearanceId = (*itEntry);
            itEntry++;

            bodyDefinition bodyDefinitionTemplate;

            bodyDefinitionTemplate.position_.x = 0.0;
            bodyDefinitionTemplate.position_.y = 0.0;

            if( (*itEntry).compare( "static" ) == 0 ){
                bodyDefinitionTemplate.type_ = STATIC;
            }
            else if ( (*itEntry).compare( "dynamic" ) == 0 ){
                bodyDefinitionTemplate.type_ = DYNAMIC;
            }
            else if ( (*itEntry).compare( "kinematic" ) == 0 ){
                bodyDefinitionTemplate.type_ = KINEMATIC;
            }
            else{
                exit(1);
            }
            itEntry++;
            bodyDefinitionTemplate.angle_ = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.linearVelocity_.x = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.linearVelocity_.y = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.angularVelocity_ = atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.linearDamping_ =  atof((*itEntry).c_str());
            itEntry++;
            bodyDefinitionTemplate.angularDamping_ = atof((*itEntry).c_str());
            itEntry++;

            if( (*itEntry).compare( "allowSleep" ) == 0 ){
                bodyDefinitionTemplate.allowSleep_ = true;
            }
            else if( (*itEntry).compare( "denySleep" ) == 0 ){
                bodyDefinitionTemplate.allowSleep_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "awake" ) == 0 ){
                bodyDefinitionTemplate.awake_ = true;
            }
            else if( (*itEntry).compare( "asleep" ) == 0 ){
                bodyDefinitionTemplate.awake_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "denyRotation" ) == 0 ){
                bodyDefinitionTemplate.denyRotation_ = true;
            }
            else if( (*itEntry).compare( "allowRotation" ) == 0 ){
                bodyDefinitionTemplate.denyRotation_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "isBullet" ) == 0 ){
                bodyDefinitionTemplate.isBullet_ = true;
            }
            else if( (*itEntry).compare( "isNoBullet" ) == 0 ){
                bodyDefinitionTemplate.isBullet_ = false;
            }
            else{
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "active" ) == 0 ){
                bodyDefinitionTemplate.active_ = true;
            }
            else if( (*itEntry).compare( "inactive" ) == 0 ){
                bodyDefinitionTemplate.active_ = false;
            }
            else{
                exit(1);
            }

            itEntry++;
            fixtureDefinition fixtureDefinitionTemplate;
            fixtureDefinitionTemplate.friction_ = atof((*itEntry).c_str());
            itEntry++;
            fixtureDefinitionTemplate.restitution_ = atof((*itEntry).c_str());
            itEntry++;
            fixtureDefinitionTemplate.density_ = atof((*itEntry).c_str());
            itEntry++;
            if( (*itEntry).compare( "isSensor") == 0 ){
                fixtureDefinitionTemplate.isSensor_ = true;
            }
            else if( (*itEntry).compare( "isNoSensor" ) == 0 ){
                fixtureDefinitionTemplate.isSensor_ = false;
            }
            itEntry++;

            circle tmpCircle;
            polygon tmpPolygon;
            box tmpBox;
            float  angleOffsetForAnimation = 0;
            if( (*itEntry).compare( "circle" ) == 0 ){
                itEntry++;
                tmpCircle.center.x = atof((*itEntry).c_str());
                itEntry++;
                tmpCircle.center.y = atof((*itEntry).c_str());
                itEntry++;
                tmpCircle.radius = atof((*itEntry).c_str());

                Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, tmpCircle );
                this->materialLibrary_.push_back( temporaryMaterial );
            }
            else
            {
                Shape shapeType;
                if( (*itEntry).compare( "edge" ) == 0 ){
                    shapeType = EDGE;
                    itEntry++;
                    tmpPolygon.countOfVertices = 2;
                    tmpPolygon.vertices[0].x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpPolygon.vertices[0].y = atof((*itEntry).c_str());
                    itEntry++;
                    tmpPolygon.vertices[1].x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpPolygon.vertices[1].y = atof((*itEntry).c_str());

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpPolygon );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else if( (*itEntry).compare( "axisAlignedBox" ) == 0 ){
                    shapeType = ALIGNED_BOX;
                    itEntry++;

                    tmpBox.halfSize.x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.halfSize.y = atof((*itEntry).c_str());

                    tmpBox.center.x = 0;
                    tmpBox.center.x = 0;
                    tmpBox.angle = 0;

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpBox );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else if( (*itEntry).compare( "orientedBox" ) == 0 ){
                    shapeType = ORIENTED_BOX;

                    itEntry++;
                    tmpBox.halfSize.x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.halfSize.y = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.center.x = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.center.y = atof((*itEntry).c_str());
                    itEntry++;
                    tmpBox.angle = atof((*itEntry).c_str());
                    angleOffsetForAnimation = tmpBox.angle;

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpBox );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else if( (*itEntry).compare( "polygon" ) == 0 ){
                    shapeType = POLYGON;
                    itEntry++;
                    tmpPolygon.countOfVertices = atoi((*itEntry).c_str());

                    for( unsigned int i = 0; i < tmpPolygon.countOfVertices; i++ )
                    {
                        itEntry++;
                        tmpPolygon.vertices[i].x = atof((*itEntry).c_str());
                        itEntry++;
                        tmpPolygon.vertices[i].y = atof((*itEntry).c_str());
                    }

                    Material* temporaryMaterial = new Material( materialId, visualAppearanceId, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpPolygon );
                    this->materialLibrary_.push_back( temporaryMaterial );
                }
                else
                {
                    exit(1);
                }

            }

        }
    }

    void GameObjectManager::loadObjects( std::string spacialObjectsFile )
    {
        FileData* dataFromFile = parseFile( &spacialObjectsFile );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileObject::iterator itEntry;
            FileObject tmp = (*itData);
            itEntry = tmp.begin();

            std::string objectId = (*itEntry);
            itEntry++;
            std::string materialId = (*itEntry);
            itEntry++;
            b2Vec2 position;
            position.x = atof((*itEntry).c_str());
            itEntry++;
            position.y = atof((*itEntry).c_str());

            SpacialObject* temporaryObject = new SpacialObject( objectId, materialId, position );
            if( temporaryObject != NULL )
            {
                this->spacialObjects_.push_back( temporaryObject );
            }
        }
    }

    Material* GameObjectManager::provideMaterial( std::string materialId )
    {
        std::vector< Material* >::iterator it;
        for( it = this->materialLibrary_.begin(); it < this->materialLibrary_.end(); it++ )
        {
            if( materialId.compare( (*it)->getMaterialId() ) == 0 )
            {
                return (*it);
            }
        }
        exit(1);
    }

    SpacialObject* GameObjectManager::nextSpacialObject( int current )
    {
         std::vector< SpacialObject* >::iterator it;
         it = this->spacialObjects_.begin();
         it += current;
         if( it < this->spacialObjects_.end() )
         {
            return (*it);
         }
         return NULL;
    }

    GameObjectManager::GameObjectManager()
    {
    }

    GameObjectManager::~GameObjectManager()
    {
        this->spacialObjects_.clear();
        this->materialLibrary_.clear();
    }
}
