//
// Created by nicolas on 12/06/17.
//

#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include "Objects/Explosion.hpp"
#include "Objects/Wall.hpp"
#include "Objects/Bomb.hpp"

Bomb::Bomb(MapManager *map, AGameObject::Object object) : AGameObject(map, object, 1), explosionDelay(3)
{

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
  _map->addObjects(Ogre::Vector2(_node->getPosition().x, _node->getPosition().z), new Explosion(_map, AGameObject::BOMB, true, 1, Ogre::Vector3::ZERO));
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

