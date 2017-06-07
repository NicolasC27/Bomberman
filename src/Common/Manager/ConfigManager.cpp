//
// Created by nicolas on 06/06/17.
//

#include <iostream>
#include "Common/Manager/ConfigManager.hpp"

ConfigManager::ConfigManager(Ogre::Root *Root) : _Root(Root)
{
  initializeRoot();
  initializeConfigRender();

}

ConfigManager::~ConfigManager()
{

}
bool 			ConfigManager::initializeConfigRender()
{
  render = _Root->getRenderSystemByName("OpenGL Rendering Subsystem");

  _Root->setRenderSystem(render);
  render->setConfigOption("Full Screen", "No");
  render->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
  render->setConfigOption("VSync", "Yes");

  Ogre::ConfigOptionMap map = render->getConfigOptions();
  for(Ogre::ConfigOptionMap::const_iterator it = map.begin(); it != map.end(); it++)
    {
      std::cout << it->first << std::endl;
      for(int i = 0; i < it->second.possibleValues.size(); i++)
	std::cout << "  " << it->second.possibleValues[i] << std::endl;
    }

  if(!(_Root->restoreConfig() || _Root->showConfigDialog())) {
      return false;
    }
}

void 			ConfigManager::initializeRoot()
{
  _Root = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

  configFile.load("resources.cfg");

  Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
  Ogre::String secName, typeName, archName;
  while (seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for (i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		  archName, typeName, secName);
	}
    }
}

Ogre::Root *ConfigManager::getRoot() const
{
  return _Root;
}
