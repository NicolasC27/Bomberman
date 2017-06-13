//
// Created by nicolas on 12/06/17.
//

#include <Interfaces/AGameObject.hpp>
#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include "Objects/Bomb.hpp"

Bomb::Bomb(AGameObject::Object object) : AGameObject(object, 1)
{

}

Bomb::~Bomb()
{

}

void 			Bomb::update()
{

}

void 			Bomb::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshPrefab());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
}

void			Bomb::Explosion()
{
  Ogre::SceneNode	*test;
// create a particle system named explosions using the explosionTemplate
  Ogre::ParticleSystem* particleSystem = SceneManager->createParticleSystem("explosions", "explosionTemplate");

// fast forward 1 second  to the point where the particle has been emitted
  particleSystem->fastForward(1.0);

// attach the particle system to a scene node
  test->attachObject(particleSystem);
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

