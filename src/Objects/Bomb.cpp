//
// Created by nicolas on 12/06/17.
//

#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include "Objects/Explosion.hpp"
#include "Objects/Bomb.hpp"

Bomb::Bomb(Player *player, MapManager *map, AGameObject::Object object) :
	AGameObject(map, object, 1),  explosionDelay(3), _player(player), _power(player->getPowerbomb())
{
std::cout << "create bomb with power  " << _power << std::endl;
}

Bomb::~Bomb()
{
}

void 			Bomb::update(Ogre::Real dt)
{
  explosionDelay -= dt;
  float scale = 1 - (0.5 * explosionDelay / 3);
  _node->setScale(scale, scale, scale);

  if (explosionDelay <= 0)
    {
      this->explode();
      _player->setBombmax(_player->getBombmax() + 1);
      _map->removeObject(this);
    }
}

void 			Bomb::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshPrefab());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
}

void			Bomb::explode()
{
  _map->addObjects(Ogre::Vector2(_node->getPosition().x, _node->getPosition().z),
		   new Explosion(_map, AGameObject::EXPLOSION, true,
				 _power, Ogre::Vector3::ZERO));
}

AGameObject::State 	Bomb::getState() const
{
  return BREAKABLE;
}

std::string 		Bomb::getName() const
{
  return  "Bomb_" + std::to_string(_id);
}

std::string 		Bomb::getNameExplosion() const
{
  objectId += 1;
  return  "BombExplosion_" + std::to_string(objectId);
}

std::string 		Bomb::getMaterialName() const
{
  return "Objects/Bomb";
}

std::string Bomb::getMeshName() const
{
  return "Sphere.mesh";
}

Ogre::Vector3 		Bomb::getScale() const
{
  return Ogre::Vector3(0.8, 0.8, 0.80);
}


double 			Bomb::getPositionY() const
{
  return 0;
}

Ogre::SceneManager::PrefabType	Bomb::getMeshPrefab() const
{
  return Ogre::SceneManager::PT_SPHERE;
}

void 			Bomb::destroy()
{
  explode();
  _map->removeObject(this);
}