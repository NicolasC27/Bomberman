//
// Created by nicolas on 12/06/17.
//

#include "Objects/Item.hpp"

Item::Item(MapManager *map, AGameObject::Object object) : AGameObject(map, object, 1)
{
  this->upgrade = rand() % 3;//NB_UPGRADE;
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
  return "Sphere.mesh";//mesh_item[this->upgrade];
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

void 			Item::destroy()
{
  _map->removeObject(this);
}

int Item::getUpgrade() const
{
  return upgrade;
}
