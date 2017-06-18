//
// Created by nicolas on 12/06/17.
//

#include "Objects/Item.hpp"
#include <iostream>

Item::Item(MapManager *map, AGameObject::Object object) : AGameObject(map, object, 1)
{
  this->upgrade = rand() % 3;
}

Item::~Item()
{
}

void 			Item::update(Ogre::Real dt)
{
  /*MapManager::Character	charac = _map->getCharacter();
  Ogre::Vector3 	itempos(_node->getPosition());
  Ogre::Vector3 	playerpos;
  
  int	used = 0;
  for (unsigned int i = 0; i < charac.size(); i++)
    {
      playerpos = charac[i]->getNode()->getPosition();
      dist = (itempos.x - playerpos.x) * (itempos.x - playerpos.x) +
	     (itempos.z - playerpos.z) * (itempos.z - playerpos.z);
      if (dist <= 10000)
	{
	  used = 1;
	  _map->_character[_upgrade]->use_item[i]();
	  removeObject();
	}
    }*/
  _node->yaw(Ogre::Degree(5));
}

void 			Item::createEntity()
{
  _obj = SceneManager->createEntity(getName(),  getMeshName());//getMeshPrefab());
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
  if (this->upgrade == 0)
    return "Mat";
  else if (this->upgrade == 1)
      return "Mat_gris";
    else if (this->upgrade == 2)
	return "Mat_red";
}

std::string Item::getMeshName() const
{
  return ("cristal.mesh");
}

Ogre::Vector3 		Item::getScale() const
{
  return Ogre::Vector3(1, 1, 1);
}

double 			Item::getPositionY() const
{
  return 0;
}

Ogre::SceneManager::PrefabType	Item::getMeshPrefab() const
{
  return Ogre::SceneManager::PT_SPHERE;
}

void 			Item::destroy()
{
  _map->removeObject(this);
}

int Item::getUpgrade() const
{
  return upgrade;
}
