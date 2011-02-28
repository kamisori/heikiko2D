#ifndef HEIKIKO2D_HPP
#define HEIKIKO2D_HPP

#include <string>
#include <vector>
#include <map>
#include <Box2D/Box2D.h>

#include <objects/gameObjectManager.hpp>
#include <inputHandler.hpp>
#include <contactListener.hpp>

const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

const int32 physicsVisualsRatio = 32;
//dont change the scale, it wont work
const sf::Vector2f spritesScale(1.0, 1.0);

const float32 jumpForce = 500.0;
const float32 fallForce = 30.0;
const float32 horizontalForce = 30.0;
const float32 horizontalForceMidAir = 10.0;
const float32 horizontalSpeedLimit = 20.0;

const float32 Fnull = 0.0;

const b2Vec2 EarthGravity(0.0,-9.8);

class heikiko2D
{
    public:
        InputHandler* inputHandlerThread_;
        void runHeikiko2D();

        heikiko2D();
        ~heikiko2D();

        objects::GameObjectManager* globalGameObjectManager_;

        b2World* simulatedWorld_;

        sf::RenderWindow* appWindow_;
        sf::FloatRect ViewRect_;
        sf::View twoDCam_;
        sf::Mutex* GlobalMutex_;
        sf::Vector2f resolution_;
        int32 resolutionColor_;
        sf::Clock Clock_;
        ContactListener* contactListener_;
    protected:

    private:
        void loadLevel();
        void handleSystemEvents();
        void handleInputEvents( objects::SpacialObject* tmpObject );

        void initializePhysics();
        void initializeThreads();
        void calculateNextScene();
        void sendSceneToPlayers();
};

#endif
