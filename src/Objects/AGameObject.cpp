//
// Created by nicolas on 29/05/17.
//

#include <OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include "Interfaces/AGameObject.hpp"

int AGameObject::objectId = 1;

AGameObject::AGameObject(Object object) : _collision(new Collision(0)), _type(object)
{
  _id = AGameObject::objectId++;
}

AGameObject::AGameObject(AGameObject::Object object, double r) : _collision(new Collision(r)),  _type(object)
{
  _id = AGameObject::objectId++;
}

AGameObject::~AGameObject()
{

}

void 			AGameObject::setSceneManager(Ogre::SceneManager *SceneManager)
{
  AGameObject::SceneManager = SceneManager;
  setNode(AGameObject::SceneManager->getRootSceneNode()->createChildSceneNode());
}

Ogre::MovableObject 	*AGameObject::getObj() const
{
  return _obj;
}

void 			AGameObject::setPosition(int x, int y, int z)
{
  _node->setPosition(x, y, z);
  _collision->setOrigin(Ogre::Vector2(x , z));
}


void 			AGameObject::setNode(Ogre::SceneNode *node)
{
  _node = node;
}

void 			AGameObject::AttachObject()
{
  _node->scale(getScale());
  _node->attachObject(_obj);
}

AGameObject::Object 	AGameObject::getType() const
{
  return _type;
}

void 			AGameObject::setType(AGameObject::Object type)
{
  _type = type;
}

void 			AGameObject::setObj(Ogre::MovableObject *obj)
{
  _obj = obj;
}








