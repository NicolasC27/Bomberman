//
// Created by nicolas on 30/05/17.
//

#include <Wall.hpp>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

Wall::Wall(Wall::State type) : AGameObject(AGameObject::BLOCK), _state(type)
{

}

Wall::~Wall()
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
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName ("cube");
}
