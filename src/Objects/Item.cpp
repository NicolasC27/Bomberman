//
// Created by nicolas on 12/06/17.
//



#include <Interfaces/AGameObject.hpp>
#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include "Objects/Item.hpp"

Item::Item(AGameObject::Object object) : AGameObject(object, 1)
{
  this->upgrade = rand() % NB_UPGRADE;
}

Item::~Item()
{
}

void 			Item::update()
{
}

void 			Item::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshPrefab());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
}

AGameObject::State 	Item::getState() const
{
  return BREAKABLE;
}

std::string 		Item::getName() const
{
  return  "Item_" + std::to_string(_id);
}

std::string 		Item::getMaterialName() const
{
  return "Objects/Item";
}

std::string Item::getMeshName() const
{
  return mesh_item[this->upgrade];
}

Ogre::Vector3 		Item::getScale() const
{
  return Ogre::Vector3(0.8, 0.8, 0.80);
}


double 			Item::getPositionY() const
{
  return 0;
}

Ogre::SceneManager::PrefabType	Item::getMeshPrefab() const
{
  return Ogre::SceneManager::PT_SPHERE;
}

