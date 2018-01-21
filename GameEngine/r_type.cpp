#include <iostream>
#include "TacosEngine.h"

using namespace TacosEngine;

int main()
{
  Engine engine;
  std::shared_ptr <Scene> scene = std::make_shared<Scene>("Scene1");

  engine.initRessources("init.ressource");

// Scene
  engine.addScene(scene);
  if (scene->getTexture("back") != nullptr)
    std::cout << "ok" << std::endl;

// Sprite background
  /*std::shared_ptr <Sprite> back = std::make_shared<Sprite>("Background", scene, Layout::BACKGROUND);
  back->setTexture(scene->getTexture("back"));
  back->setSize(Vector2(800, 400));
  scene->addSprite(back);*/

// Sprite ship
  /*std::shared_ptr <Sprite> player = std::make_shared<Sprite>("Player", scene, Layout::SCENE);
  player->setTexture(scene->getTexture("ship"));
  player->setSize(Vector2(20, 20));
  std::shared_ptr <PlayerBehaviour> playerBeha = std::make_shared<PlayerBehaviour>("playerBeh", player);
  scene->addComponent(playerBeha);
  scene->addSprite(player);*/

// Load and run scene
  /*engine.loadScene(scene);
  engine.run();*/
  return 0;
}