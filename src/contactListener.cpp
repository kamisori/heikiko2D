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

#include <contactListener.hpp>
#include <objects/spacialObject.hpp>
#include <iostream>


ContactListener::ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Body* bodyA = fixtureA->GetBody();
    objects::SpacialObject* actorA = (objects::SpacialObject*)bodyA->GetUserData();

    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyB = fixtureB->GetBody();
    objects::SpacialObject* actorB = (objects::SpacialObject*)bodyB->GetUserData();

    std::string IDa = actorA->getSpacialObjectId();
    std::string IDb = actorB->getSpacialObjectId();

    if( IDa.compare("player") == 0 || IDb.compare("player") == 0 )
    {
        b2Manifold* contactsManifold = contact->GetManifold();
        std::string face;
        if( contactsManifold->type == b2Manifold::e_faceA )
        {
            face = IDa;
        }
        else if( contactsManifold->type == b2Manifold::e_faceB )
        {
            face = IDb;
        }

        if( IDa.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->setBottomObject(actorB);
            std::cout << IDa <<" is on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDb.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->setBottomObject(actorA);
            std::cout << IDb <<" is on top of " << IDa << ". " << face << " b" <<std::endl;
        }
        else if( IDb.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->setBottomObject(actorB);
            std::cout << IDa <<" is on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDa.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->setBottomObject(actorA);
            std::cout << IDb <<" is on top of " << IDa << ". " << face << " b" <<std::endl;
        }
        else
        {
            std::cout << IDa << " and " << IDb << " are equaly high. " << face <<std::endl;
        }

std::cout << "a "  << bodyA->GetPosition().y << " " << bodyA->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;
std::cout << "b "  << bodyB->GetPosition().y << " " << bodyB->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;

    }
    return;
}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Body* bodyA = fixtureA->GetBody();
    objects::SpacialObject* actorA = (objects::SpacialObject*)bodyA->GetUserData();

    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyB = fixtureB->GetBody();
    objects::SpacialObject* actorB = (objects::SpacialObject*)bodyB->GetUserData();

    std::string IDa = actorA->getSpacialObjectId();
    std::string IDb = actorB->getSpacialObjectId();

    if( IDa.compare("player") == 0 || IDb.compare("player") == 0 )
    {
        b2Manifold* contactsManifold = contact->GetManifold();
        std::string face;
        if( contactsManifold->type == b2Manifold::e_faceA )
        {
            face = IDa;
        }
        else if( contactsManifold->type == b2Manifold::e_faceB )
        {
            face = IDb;
        }

        if( IDa.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->removeBottomObject(actorB);
            std::cout << IDa <<" is no longer on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDb.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->removeBottomObject(actorA);
            std::cout << IDb <<" is no longer on top of " << IDa << ". " << face << " b" <<std::endl;
        }
        else if( IDb.compare( face ) == 0 &&
            IDa.compare("player") == 0 &&
            bodyA->GetPosition().y > bodyB->GetPosition().y &&
            ( ( bodyA->GetPosition().y - bodyB->GetPosition().y ) > 0.984375 ) /*&&
            bodyA->GetPosition().y > bodyA->GetWorldPoint(contactsManifold->localPoint).y */)

        {
            actorA->removeBottomObject(actorB);
            std::cout << IDa <<" is no longer on top of " << IDb << ". " << face << " a" <<std::endl;
        }
        else if(    IDa.compare( face ) == 0 &&
                    IDb.compare("player") == 0 &&
                    bodyB->GetPosition().y > bodyA->GetPosition().y &&
                    ( ( bodyB->GetPosition().y - bodyA->GetPosition().y ) > 0.984375 )/* &&
                    bodyB->GetPosition().y > bodyB->GetWorldPoint(contactsManifold->localPoint).y */)
        {
            actorB->removeBottomObject(actorA);
            std::cout << IDb <<" is no longer on top of " << IDa << ". " << face << " b" <<std::endl;
        }
std::cout << "--a "  << bodyA->GetPosition().y << " " << bodyA->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;
std::cout << "--b "  << bodyB->GetPosition().y << " " << bodyB->GetWorldPoint(contactsManifold->localPoint).y <<std::endl;

    }
    return;
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ // handle pre-solve event
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{ // handle post-solve event
}
