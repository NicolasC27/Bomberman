//
// Created by nicolas on 29/05/17.
//

#include <OgreSceneManager.h>
#include "Objects/AGameObject.hpp"

int AGameObject::objectId = 1;

AGameObject::AGameObject(Object object)
{
  _id = AGameObject::objectId++;
}

AGameObject::AGameObject()
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







