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
}

Bomb::~Bomb()
{

}

void 			Bomb::update(Ogre::Real dt)
{
  float 		scale;

  explosionDelay -= dt;
  scale = 40 - (20 * explosionDelay / 3);
  _node->setScale(scale, scale, scale);

  if (explosionDelay <= 0.5)
    _map->getEngine()->play2D(_map->getExplosion());
  if (explosionDelay <= 0)
    {
      this->explode();
      _map->removeObject(this);
    }
}

void 			Bomb::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshName());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
  _node->yaw(Ogre::Degree(90));
  _node->pitch(Ogre::Degree(90));
}

void			Bomb::explode()
{
  _map->addObjects(Ogre::Vector2(_node->getPosition().x, _node->getPosition().z),
		   new Explosion(_map, AGameObject::EXPLOSION, true,
				 _power, Ogre::Vector3::ZERO));
  _player->setCurrBomb(_player->getCurrBomb() + 1);
}

AGameObject::State 	Bomb::getState() const
{
  return BREAKABLE;
}

std::string 		Bomb::getName() const
{
  return  "Bomb_" + std::to_string(_id);
}

std::string 		Bomb::getMaterialName() const
{
  return "BombTexture";
}

std::string Bomb::getMeshName() const
{
  return "bomb.mesh";
}

Ogre::Vector3 		Bomb::getScale() const
{
  return Ogre::Vector3(40, 40, 40);
}

double 			Bomb::getPositionY() const
{
  return (-50);
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