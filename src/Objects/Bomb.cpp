//
// Created by nicolas on 12/06/17.
//

#include <Interfaces/AGameObject.hpp>
#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include "Objects/Bomb.hpp"

Bomb::Bomb(MapManager *map, AGameObject::Object object) : AGameObject(map, object, 1)
{

}

Bomb::~Bomb()
{

}

void 			Bomb::update(Ogre::Real dt)
{

}

void 			Bomb::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshPrefab());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
}

void			Bomb::Explosion()
{
    Ogre::SceneNode* particlenode= SceneManager->getRootSceneNode()->createChildSceneNode();

    Ogre::ParticleSystem* ps1= SceneManager->createParticleSystem(getName(), "Examples/Smoke");

    particlenode->setPosition(Ogre::Vector3(_node->getPosition().x, _node->getPosition().y, _node->getPosition().z));
    particlenode->attachObject(ps1);

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

