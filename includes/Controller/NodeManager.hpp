//
// Created by nicolas on 04/06/17.
//

#ifndef BOMBERMAN_NODEMANAGER_HPP_H
#define BOMBERMAN_NODEMANAGER_HPP_H

#include <OgreSceneNode.h>

namespace Controller
{
  class NodeManager {

   private:
    Ogre::SceneNode	*_object;

   public:
    NodeManager(Ogre::SceneNode *node);

    void attachObject(Ogre::MovableObject *obj);
    Ogre::SceneNode *getNodeObject() const;
  };
};
#endif //BOMBERMAN_NODEMANAGER_HPP_H
