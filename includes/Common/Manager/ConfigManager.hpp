//
// Created by nicolas on 06/06/17.
//

#ifndef BOMBERMAN_CONFIGMANAGER_HPP
#define BOMBERMAN_CONFIGMANAGER_HPP

#include <OgreConfigOptionMap.h>
#include <Ogre.h>

class ConfigManager {

  Ogre::Root 		*_Root;
  Ogre::RenderSystem 	*render;
  Ogre::ConfigFile	configFile;

 public:
  ConfigManager(Ogre::Root *Root);
  virtual ~ConfigManager();

  Ogre::Root 		*getRoot() const;

 private:
  bool 			initializeConfigRender();
  void 			initializeRoot();
};
#endif //BOMBERMAN_CONFIGMANAGER_HPP
