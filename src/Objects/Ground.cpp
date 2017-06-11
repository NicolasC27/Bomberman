//
// Created by nicolas on 30/05/17.
//

#include "Objects/Ground.hpp"
#include <OgreEntity.h>
#include <Ogre.h>

Ground::Ground(Ground::State type) : AGameObject(AGameObject::NOTHING), _state(type)
{

}

Ground::~Ground()
{

}

Ground::State 		Ground::getState() const
{
  return _state;
}

void 			Ground::setState(AGameObject::State state)
{
  _state = state;
}

std::string 		Ground::getName() const
{
    return  "Ground_" + std::to_string(_id);
}

void 			Ground::CreateOwnEntity()
{

}

void			Ground::createEntity()
{
  _obj = SceneManager->createEntity(getName(),Ogre::SceneManager::PT_CUBE);
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName ("Objects/Ground/BumpyMetal");
//  dynamic_cast <Ogre::Entity*>(_obj)->setMaterial(mMaterial);
}

std::string		Ground::getMaterialName() const
{
  if (getState() == Ground::State::UNBREAKABLE)
    return std::string("cube/wall");
  if (getState() == Ground::State::BREAKABLE)
    return std::string("cube/block");

}

Ogre::SceneManager::PrefabType		Ground::getMeshPrefab() const
{
  return (Ogre::SceneManager::PT_CUBE);
}

std::string Ground::getMeshName() const
{
  return ("cube.mesh");
}

Ogre::Vector3 Ground::getScale() const
{
    return Ogre::Vector3(1, 1, 1);
}

double Ground::getPositionY() const
{
  return (-100.0f);
};