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

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <objects/spacialObject.hpp>
#include <objects/gameObjectManager.hpp>
#include <main.hpp>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include <iostream>

namespace objects
{
    void SpacialObject::setBottomObject( SpacialObject* bottomObject )
    {
        this->bottom.push_back( bottomObject->getSpacialObjectId() );
    }

    void SpacialObject::removeBottomObject( SpacialObject* bottomObject )
    {
        for(std::vector<std::string>::iterator it = this->bottom.begin(); it < this->bottom.end(); it++ )
        {
            if(it->compare(bottomObject->getSpacialObjectId()) == 0)
            {
                this->bottom.erase(it);
            }
        }
    }

    void SpacialObject::iJumped()
    {
        this->bottom.clear();
    }

    bool SpacialObject::standsOnSomething()
    {
        return !(this->bottom.empty());
    }

    std::string SpacialObject::getSpacialObjectId()
    {
        return spacialObjectId_;
    }

    b2Body* SpacialObject::getB2Body()
    {
        return b2Body_;
    }

    std::string SpacialObject::getVisualAppearance()
    {
        return visualAppearance_;
    }

    SpacialObject::SpacialObject( std::string spacialObjectId, std::string materialId, b2Vec2 position )
    {
        spacialObjectId_.assign( spacialObjectId );

        Material* temporaryMaterial;
        temporaryMaterial = b2WorldAndVisualWorld.globalGameObjectManager_->provideMaterial( materialId );

        this->visualAppearance_.assign(temporaryMaterial->getVisualAppearanceId());
        this->angleOffsetForAnimation_ = temporaryMaterial->getAngleOffsetForAnimation();
        b2FixtureDef* fixtureDefinition = temporaryMaterial->createFixtureDefinition();
        b2BodyDef* bodyDefinition = temporaryMaterial->createBodyDefinition();

        bodyDefinition->userData = this;
        bodyDefinition->position.x = position.x;
        bodyDefinition->position.y = position.y;
        this->b2Body_ = b2WorldAndVisualWorld.simulatedWorld_->CreateBody( bodyDefinition );


        if( temporaryMaterial->thisIsACircle() )
        {
            fixtureDefinition->shape = temporaryMaterial->createCircleShape();
        }
        else
        {
            fixtureDefinition->shape = temporaryMaterial->createPolygonShape();
        }

        this->b2Body_->CreateFixture( fixtureDefinition );
    }

    SpacialObject::~SpacialObject()
    {
        b2WorldAndVisualWorld.simulatedWorld_->DestroyBody(this->b2Body_);
    }

}
