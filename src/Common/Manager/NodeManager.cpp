//
// Created by nicolas on 04/06/17.
//

#include "Common/Manager/NodeManager.hpp"

NodeManager::NodeManager(Ogre::SceneNode *node) : _object(node)
{

}

void NodeManager::attachObject(Ogre::MovableObject *obj)
{
  _object = _object->createChildSceneNode();
  _object->attachObject(obj);
}

Ogre::SceneNode *NodeManager::getNodeObject() const
{
  return _object;
}
