//
// Created by nicolas on 04/06/17.
//

#include "Controller/NodeManager.hpp"

Controller::NodeManager::NodeManager(Ogre::SceneNode *node) : _object(node)
{

}

void Controller::NodeManager::attachObject(Ogre::MovableObject *obj)
{
  _object = _object->createChildSceneNode();
  _object->attachObject(obj);
}

Ogre::SceneNode *Controller::NodeManager::getNodeObject() const
{
  return _object;
}
