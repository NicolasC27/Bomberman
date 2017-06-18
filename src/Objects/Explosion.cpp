//
// Created by nicolas on 12/06/17.
//

#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include <Interfaces/ACharacter.hpp>
#include "Objects/Explosion.hpp"

Explosion::Explosion(std::shared_ptr<MapManager> &map, AGameObject::Object object, int isRoot, int Length,
		     Ogre::Vector3 direction)
	: AGameObject(map, object, 1), _IsRoot(isRoot), _Length(Length), _Direction(direction),
	  _extend(false)
{
  _obj = NULL;
  lifeTimeRemaning = LIFE_DURATION;
  delayExtend = EXTEND_DELAY;
}

Explosion::~Explosion()
{

}

void 			Explosion::update(Ogre::Real dt)
{
  if (lifeTimeRemaning > 0)
    lifeTimeRemaning-= dt;
  else
    {
      _map->removeObject(this);
      return ;
    }

  delayExtend -= dt;
  if (delayExtend <= 0)
    {
      if (_Length > 0)
	{
	  if (_IsRoot)
	    {
	      checkVictim(_node->getPosition(), Ogre::Vector3::ZERO);
	      extendFire(Ogre::Vector3::UNIT_X);
	      extendFire(-Ogre::Vector3::UNIT_X);
	      extendFire(Ogre::Vector3::UNIT_Z);
	      extendFire(-Ogre::Vector3::UNIT_Z);
	    }
	  else
	    extendFire(_Direction);
	  _extend = true;
	}
    }
}

bool 			Explosion::checkVictim(Ogre::Vector3 const &pos, Ogre::Vector3 const &direction)
{
  AGameObject		*obj = _map->getObjectFrom(pos);
  MapManager::Character	victim = _map->getCharacterFrom(Ogre::Vector2(pos.x, pos.z));
  bool 			ret = false;
  AGameObject		*tmp;
  /*if (!_extend && obj != NULL && obj->getType() == AGameObject::EXPLOSION)
    {
      --_Length;
      extendFire(direction + _Direction);
      return (false);
    }*/
  if (!_extend && (obj == NULL || obj->getType() == AGameObject::ITEM))
    ret = true;
  for (MapManager::Character::const_iterator it = victim.begin(); it != victim.end(); )
    {
      tmp = *it;
      ++it;
      tmp->destroy();
    }
  if (!_extend && obj != NULL)
    obj->destroy();
  return (ret);
}

void 			Explosion::extendFire(Ogre::Vector3 const &direction)
{
  Ogre::Vector3 pos = (_node->getPosition() + direction * MapManager::boxWidth);

  if (checkVictim(pos, direction))
    _map->addObjects(Ogre::Vector2(pos.x, pos.z),
		     new Explosion(_map, AGameObject::EXPLOSION, false, _Length - 1, direction));
}

void 			Explosion::createEntity()
{
  particleSystem = SceneManager->createParticleSystem(getNameExplosion(), "Examples/Smoke");
}

AGameObject::State 	Explosion::getState() const
{
  return BREAKABLE;
}

std::string 		Explosion::getName() const
{
  return  "Explosion_" + std::to_string(_id);
}

std::string 		Explosion::getNameExplosion() const
{
  objectId += 1;
  return  "ExplosionExplosion_" + std::to_string(objectId);
}

std::string 		Explosion::getMaterialName() const
{
  return "Objects/Explosion";
}

std::string 		Explosion::getMeshName() const
{
  return "Sphere.mesh";
}

Ogre::Vector3 		Explosion::getScale() const
{
  return Ogre::Vector3(0.8, 0.8, 0.80);
}


double 			Explosion::getPositionY() const
{
  return 0;
}

Ogre::SceneManager::PrefabType	Explosion::getMeshPrefab() const
{
  return Ogre::SceneManager::PT_SPHERE;
}

