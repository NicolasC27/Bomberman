//
// Created by nicolas on 30/05/17.
//

#include <Objects/Wall.hpp>
#include <OgreEntity.h>

Wall::Wall(Wall::State type) : AGameObject(BLOCK), _state(type)
{

}

Wall::~Wall()
{

}

void 			Wall::update()
{

}

Wall::State 		Wall::getState() const
{
  return _state;
}

void 			Wall::setState(Wall::State state)
{
  _state = state;
}

std::string 		Wall::getName() const
{
    return  "Wall_" + std::to_string(_id);
}

void			Wall::createEntity()
{
  _obj = SceneManager->createEntity(getName(), Ogre::SceneManager::PT_CUBE);
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
}

std::string		Wall::getMaterialName() const
{
  if (getState() == Wall::State::UNBREAKABLE)
    return std::string("Objects/Cube/Wall");
  if (getState() == Wall::State::BREAKABLE)
    return std::string("Objects/Cube/Block");

}

Ogre::SceneManager::PrefabType		Wall::getMeshPrefab() const
{
  return (Ogre::SceneManager::PT_CUBE);
}

std::string 		Wall::getMeshName() const
{
  return ("cube.mesh");
}

Ogre::Vector3 		Wall::getScale() const
{
  return (Ogre::Vector3(1.0, 1.0, 1.0));

  if (getState() == Wall::State::UNBREAKABLE)
    return (Ogre::Vector3(1.0, 1.0, 1.0));
//    return Ogre::Vector3(0.9, 0.9, 0.9);
  if (getState() == Wall::State::BREAKABLE)
    return Ogre::Vector3(0.8, 0.8, 0.8);
}

double 		Wall::getPositionY() const
{
  return (0);
  if (getState() == Wall::State::UNBREAKABLE)
    return (0);
//    return ((-(100 - (100 * 0.9)) + 10) / 2);
  if (getState() == Wall::State::BREAKABLE)
    return ((-(100 - (100 * 0.8) + 10)) / 2) + 6;
}
