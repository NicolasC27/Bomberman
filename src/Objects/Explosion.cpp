//
// Created by nicolas on 12/06/17.
//

#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include "Objects/Explosion.hpp"

Explosion::Explosion(MapManager *map, AGameObject::Object object, int isRoot, int Length,
		     Ogre::Vector3 direction)
	: AGameObject(map, object, 1), _IsRoot(isRoot), _Length(Length), _Direction(direction)
{
  _obj = NULL;
  lifeTimeRemaning = LIFE_DURATION;
  delayExtend = EXTEND_DELAY;
  std::cout << "explosion toward " << direction << " have " << _Length << " case to stop" << std::endl;
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
	      extendFire(Ogre::Vector3::UNIT_X);
	      extendFire(-Ogre::Vector3::UNIT_X);
	      extendFire(Ogre::Vector3::UNIT_Z);
	      extendFire(-Ogre::Vector3::UNIT_Z);
	    }
	  else
	    extendFire(_Direction);
	}
    }

}

void 			Explosion::extendFire(Ogre::Vector3 direction)
{
  Ogre::Vector3 pos = (_node->getPosition() + direction * MapManager::boxWidth);
  MapManager::Character	charac = _map->getCharacterFrom(Ogre::Vector2(pos.x, pos.z));
  AGameObject		*obj = _map->getObjectFrom(pos);

  for (unsigned int i = 0; i < charac.size() ; ++i)
    charac[i]->destroy();
  if (obj == NULL || obj->getType() == ITEM)
    _map->addObjects(Ogre::Vector2(pos.x, pos.z),
		     new Explosion(_map, AGameObject::EXPLOSION, false, _Length - 1, direction));
  if (obj != NULL)
    obj->destroy();
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

