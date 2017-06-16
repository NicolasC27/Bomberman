//
// Created by nicolas on 29/05/17.
//

#include <OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <OgreNode.h>
#include "Interfaces/AGameObject.hpp"
#include <OgreAxisAlignedBox.h>

int AGameObject::objectId = 1;

AGameObject::AGameObject(MapManager *map, Object object) : _type(object), _map(map)
{
  _id = AGameObject::objectId++;
}

AGameObject::AGameObject(MapManager *map, AGameObject::Object object, double r) : _type(object), _map(map)
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
  Ogre::Vector3		max;
  Ogre::Vector3		min;

  _node->setPosition(x, y, z);
//  _node->showBoundingBox(true);
}


void 			AGameObject::setNode(Ogre::SceneNode *node)
{
  _node = node;
}

void 			AGameObject::AttachObject()
{
  _node->setScale(getScale());
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

Ogre::SceneNode *AGameObject::getNode() const
{
  return _node;
}
