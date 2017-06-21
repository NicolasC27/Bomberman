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
  _node->yaw(Ogre::Degree(dt * 200));
}

void 			Item::createEntity()
{
  _obj = SceneManager->createEntity(getName(),  getMeshName());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
  static_cast<Ogre::Entity*>(_obj)->getMesh()->_setBounds(Ogre::AxisAlignedBox(-40, 0.0, -40, 40, 40, 40));
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
  switch (this->upgrade)
    {
      case Player::BOMB:
	return (bombType == 1) ? "mutant_M_red" : "mutant_M_red";
        break;
      case Player::MAXBOMBUP:
	return "Mat_gris";
        break;
      case Player::POWERUP:
	return "Mat_red";
        break;
      case Player::SPEEDUP:
      default:
	return "Mat";
        break;
    }
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
