#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <heikiko2D.hpp>
#include <Box2D/Box2D.h>
#include <inputHandler.hpp>
#include <iostream>

//initializes the inputhandler thread and the network thread.
void heikiko2D::initializeThreads()
{
    GlobalMutex_ = new sf::Mutex();
    inputHandlerThread_ = new InputHandler(GlobalMutex_);
    networkHandlerThread_ = new NetworkHandler( this->listeningPort, GlobalMutex_);
}

//initializes the physics engine
    //creates the contact listener
    //creates the game object manager
void heikiko2D::initializePhysics()
{
    this->contactListener_ = new ContactListener();
    this->globalGameObjectManager_ = new objects::GameObjectManager();
    bool doSleep = true;
    this->simulatedWorld_ = new b2World(EarthGravity, doSleep);
    this->simulatedWorld_->SetContactListener(contactListener_);
}

//load the level data here
//needs a way to dynamically load a level later, to spawn multiple servers, each with their own leveldata.
//a server is only spawn, if a player wants to go to that other servers level.
//probably this wont be that easy, it is very likely that if there is a high load on a serving machine, we wont have more than two or three server processes running...
//also at the moment i dont know anything about how much overhead a single player creates...
void heikiko2D::loadLevel()
{
    std::string materialFile ( "data/materials.data" );
    std::string objectFile ( "data/spacialObjects.data" );

    this->globalGameObjectManager_->loadMaterials( materialFile );
    this->globalGameObjectManager_->loadObjects( objectFile );
}

//handle system events here, like saving, shutting down or halting the server
void heikiko2D::handleSystemEvents()
{
    while (inputHandlerThread_->globalflags_.Running)
    {
        if (inputHandlerThread_->globalflags_.Save)
        {
            inputHandlerThread_->globalflags_.Save = false;
            std::cout << "Saved." << std::endl;
        }

        if (inputHandlerThread_->globalflags_.Stop )
        {
            std::cout << "Bye." << std::endl;
            inputHandlerThread_->globalflags_.Running = false;
        }

        if( inputHandlerThread_->globalflags_.AcceptNew )
        {
            std::cout << "Listener is open for new connections." << std::endl;
            networkHandlerThread_->globalflags_.AcceptNew = true;
            inputHandlerThread_->globalflags_.AcceptNew = false;
        }

        if( inputHandlerThread_->globalflags_.DenyNew )
        {
            std::cout << "Listener is closed for new connections." << std::endl;
            networkHandlerThread_->globalflags_.AcceptNew = false;
            inputHandlerThread_->globalflags_.DenyNew = false;
        }
    }
}

//handle input events from the clients here
void heikiko2D::handleInputEvents(objects::SpacialObject* tmpObject)
{
//    bool standing = tmpObject->standsOnSomething();
//    b2Body* tmpB2Body = tmpObject->getB2Body();
//    b2Vec2 position = tmpB2Body->GetPosition();
//    b2Vec2 linearVelocity = tmpB2Body->GetLinearVelocity();
//    b2Vec2 tmpForce;
//
//    tmpForce.x = Fnull;
//    tmpForce.y = Fnull;
//    GlobalMutex_->Lock();
//    if( standing && /*here is the message for jumping*/false && (Clock_.GetElapsedTime() >= 0.125))
//    {
//        //tmpForce.y = 50.0 * cos(angle);
//        //tmpForce.x = 50.0 * sin(angle);
//        tmpForce.y = jumpForce;
//        tmpForce.x = Fnull;
//
//        tmpB2Body->ApplyForce( tmpForce, position );
//        tmpObject->iJumped();
//        inputHandlerThread_->globalflags_.ApplyForceUpwardToPlayer = false;
//        Clock_.Reset();
//    }
//    if(/*here is the message for crouching*/false)
//    {
//        //tmpForce.y = -50.0 * cos(angle);
//        //tmpForce.x = -50.0 * sin(angle);
//        tmpForce.y = -1 * fallForce;
//        tmpForce.x = Fnull;
//        tmpB2Body->ApplyForce( tmpForce, position );
//    }
//    if(/*here is the message for running left*/false)
//    {
//        tmpForce.y = Fnull;
//        if( linearVelocity.x > (-1 * horizontalSpeedLimit) )
//        {
//            if(standing)
//                tmpForce.x = -1 * horizontalForce;
//            else
//                tmpForce.x = -1 * horizontalForceMidAir;
//            tmpB2Body->ApplyForce( tmpForce, position);
//        }
//    }
//    if(/*here is the message for running right*/false)
//    {
//        tmpForce.y = Fnull;
//        if( linearVelocity.x < horizontalSpeedLimit )
//        {
//            if(standing)
//                tmpForce.x = horizontalForce;
//            else
//                tmpForce.x = horizontalForceMidAir;
//            tmpB2Body->ApplyForce( tmpForce, position);
//        }
//    }
//    GlobalMutex_->Unlock();
}

//calculate the next scene
//maybe this should be in its own thread (though same thread as the input message handling maybe)
void heikiko2D::calculateNextScene()
{
    simulatedWorld_->Step(timeStep,velocityIterations,positionIterations);
    simulatedWorld_->ClearForces();
}

//send the scene to each player, only that part which is in his/her viewrange
void heikiko2D::sendSceneToPlayers()
{
//iterate through list of players
//find range of their FOV
//send data of objects in players FOV
     /*int i = 0;
        //objects::SpacialObject* tmpObject = globalGameObjectManager_->nextSpacialObject( i );
        while( false )
        {
            b2Body* tmpB2Body = tmpObject->getB2Body();
            b2Vec2 position = tmpB2Body->GetPosition();
            float32 angle = tmpB2Body->GetAngle();

            std::string objectID = tmpObject->getSpacialObjectId();


            if( objectID.compare( "player" ) == 0 ){

                sf::Vector2f tmpPos;
                tmpPos.x = (position.x*physicsVisualsRatio);
                tmpPos.y = -(position.y*physicsVisualsRatio);

                twoDCam_.SetCenter(tmpPos);
                appWindow_->SetView(twoDCam_);

                handleInputEvents(tmpObject);
            }

            objects::Animation* tmpAnim = tmpObject->getVisualAppearance()->getCurrentAnimation();
            sf::Sprite* tmpSprite = tmpAnim->getNextFrame();

            tmpSprite->Scale(spritesScale);
            tmpSprite->SetPosition( (position.x*physicsVisualsRatio) , -(position.y*physicsVisualsRatio) );
            tmpSprite->SetRotation( (angle + tmpObject->getAngleOffsetForAnimation()) *(180/3.14159265f) );
            appWindow_->Draw( (*tmpSprite) );

            i++;
            tmpObject = globalGameObjectManager_->nextSpacialObject( i );
        }*/
}

void heikiko2D::runHeikiko2D()
{
    while (inputHandlerThread_->globalflags_.Running)
    {
        handleSystemEvents();
        calculateNextScene();
        sendSceneToPlayers();
    }
}

heikiko2D::heikiko2D()
{
    //start network thread
        //listen for incoming connections
        //accept incoming connections, ?authenticate player? add player to playerslist
        //iterate through playerslist and send objectdata
    initializePhysics();
    loadLevel();
    this->listeningPort = 42235;
    initializeThreads();
}

heikiko2D::~heikiko2D(){
    delete this->globalGameObjectManager_;
}
