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

#ifndef SPACIALOBJECT_HPP
#define SPACIALOBJECT_HPP

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

namespace objects
{
    //const uint32 sizeOfcontactIDlist = 16;
    class SpacialObject
    {
    	public:
            std::string getSpacialObjectId();
            b2Body* getB2Body();
            std::string getVisualAppearance();
            void setBottomObject( SpacialObject* bottomObject );
            void removeBottomObject( SpacialObject* bottomObject );
            bool standsOnSomething();
            void iJumped();
            float getAngleOffsetForAnimation();
            SpacialObject( std::string spacialObjectId, std::string materialId, b2Vec2 position );
                            /*string* audialAppearanceId,*/ /*float objectHealth,*/ /*float objectHardness*/
            ~SpacialObject();
    	protected:

    	private:

            float angleOffsetForAnimation_;
            std::vector< std::string > bottom;

            sf::Vector2f moveObject( sf::Vector2f addThis );
            std::string       spacialObjectId_;
            b2Body* b2Body_;
//    		float               objectHealth_;              //objects can be damaged
//    		float               objectHardness_;            //some objects resist damage better than others
                                                            //combined with collision, this means, you can
                                                            //use anything and everything as a shield against attacks.
//          float               objectTemperature_;
//          float               objectMoisture_;
//          pointer to material holding having certain properties,
//          like, meltable, flamable, temperature for meltpoint/inflamationpoint whatever

            std::string   visualAppearance_;          //null means, this is either a zone for a script,
                                                            //or something is attached to the ground, like a
                                                            //pole for a line or something

            //AudioAppearance*    audialAppearance_;        //basically the same as visualAppearance.
                                                            //holds the samples this objects can play.
//probably not neccessary:
            //Attachment*         attachedTo_;              //Attach one Object to another
                                                            //in example: Flashlight to Shovel
                                                            //attachmentStrength determines if object can be removed
                                                            //objectHealth must be higher than attachment strength, else object breaks during removal
                                                            //orientation relative to attached object
                                                            //attached at top, bottom, hind, front, one side or the other
//probably neccessary
            //Script*             objectScript_;            //also for AI
    };
}

#endif
