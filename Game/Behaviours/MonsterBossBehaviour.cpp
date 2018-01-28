//
// Created by simon on 27/01/18.
//

#include "MonsterBossBehaviour.h"
#include "../GameEngine/Rigidbody/Rigidbody.hpp"
#include "../GameEngine/Collider/Collider.hpp"
#include "../GameEngine/Animation/Animation.hpp"
#include "AnimationBehaviour.hpp"

namespace TacosEngine
{
    void MonsterBossBehaviour::update(const Input &)
    {
        ++can_shoot;
        auto pos = _object->getTransform().getPosition();
        auto rb = getComponent<Rigidbody>();
        auto playerPos = std::vector<std::pair<float, float> >();
        auto player = _object->getScene()->findByName("Player");
        if (player)
        {
            auto tmp = player->getTransform().getPosition();
            playerPos.push_back(std::make_pair<float, float>(tmp.get_x(), tmp.get_y()));
        } else
        {
            playerPos.push_back(std::make_pair<float, float>(100, 100));
        }
        std::pair<float, float> bestmove = _ia->getBestMove(playerPos, std::make_pair(pos.get_x(), pos.get_y()));
        //      std::pair<float, float> bestmove = _ia->getBestMove(pos.get_x(), pos.get_y());
        bestmove.first = 0;
        auto dir = Vector2(bestmove.first, bestmove.second);
        //      std::cout << "OKEK"<<std::endl;
        _object->getTransform().setDirection(dir);
        _object->getTransform().setSpeed(1);
        rb->addForce(dir * _object->getTransform().getSpeed());
        if (can_shoot == tick_per_shoot)
        {
            shoot();
            can_shoot = 0;
        }
        if (this->_health <= 0)
            this->setDestroy(true);
    }

    void MonsterBossBehaviour::shoot()
    {
        int i = 0;
        while (i < 6)
        {
            i = i + 2;
            auto bullet = std::make_shared<Sprite>("bullet" + this->getGameObjectName(), this->_object->getScene(),
                                                   Layout::SCENE);
            bullet->setTexture(_object->getScene()->getTexture("laserBoss"));
            bullet->setSize(Vector2(30, 30));
            bullet->getTransform().setPosition(_object->getTransform().getPosition() - Vector2(60, 40 - i * 25));
            bullet->getTransform().setSpeed(_object->getTransform().getSpeed() + 3);
            auto col = std::make_shared<Collider>("Collider" + bullet->getInstanceName(), bullet, bullet->getSize(),
                                                  bullet->getTransform().getPosition(), true);
            auto rbody = std::make_shared<Rigidbody>("Rigidbody" + bullet->getInstanceName(), bullet);
            auto beha = std::make_shared<BulletBehaviour>("bulletbeha" + bullet->getInstanceName(), bullet,
                                                          Vector2(-1, 0));
            this->_object->getScene()->addGameObject(bullet);
            this->_object->getScene()->addComponent(col);
            this->_object->getScene()->addComponent(rbody);
            this->_object->getScene()->addComponent(beha);
        }
    }

    void MonsterBossBehaviour::onCollide(GameObject &other)
    {
        if (other.getInstanceName().find("bulletPlayer") != std::string::npos &&
            other.getInstanceName().find(getInstanceName()) == std::string::npos)
        {
            this->_health = this->_health - other.getComponent<BulletBehaviour>()->get_damages();
            if (this->_health <= 0)
            {
                std::cout << "Explosion" << std::endl;
                auto explosion = std::make_shared<Sprite>("explosion", this->_object->getScene(),
                                                          Layout::SCENE);

                std::vector<ITexture*>      explosionFrames;
                explosionFrames.push_back(_object->getScene()->getTexture("explosion1"));
                explosionFrames.push_back(_object->getScene()->getTexture("explosion2"));
                explosionFrames.push_back(_object->getScene()->getTexture("explosion3"));

                explosion->setTexture(_object->getScene()->getTexture("explosion1"));
                explosion->setSize(Vector2(150, 150));
                explosion->getTransform().setPosition(_object->getTransform().getPosition());
                explosion->getTransform().setSpeed(0.0);
                explosion->setActive(true);
                std::shared_ptr<Animation>       explosionAnim =
                        std::make_shared<Animation>("explosionAnim", explosion,
                                                    false, 20, explosionFrames);
                auto beha = std::make_shared<AnimationBehaviour>("endAnim", explosion);


                this->_object->getScene()->addGameObject(explosion);
                this->_object->getScene()->addComponent(explosionAnim);
                this->_object->getScene()->addComponent(beha);
            }
        }
    }
}