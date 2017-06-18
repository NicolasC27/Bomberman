//
// HudManager.hh for cpp_indie_studio in /home/ikirame/Documents/Projects/cpp_indie_studio/src
// 
// Made by Valentin Gérard
// Login   <valentin.gerard@epitech.eu>
// 
// Started on  Sat Jun 17 23:19:24 2017 Valentin Gérard
// Last update Sun Jun 18 12:24:44 2017 Valentin Gérard
//

#ifndef HUDMANAGER_HH_
# define HUDMANAGER_HH_

# include <memory>

# include <OgreFrameListener.h>
# include <OgreException.h>
# include <OIS/OIS.h>
# include <Ogre.h>
# include <OgreException.h>
# include <OgreOverlaySystem.h>
# include <OgreOverlayContainer.h>
# include <Overlay/OgreFontManager.h>
# include <Overlay/OgreOverlayManager.h>
# include <Overlay/OgreTextAreaOverlayElement.h>
# include "Common/Manager/GameManager.hpp"
# include "MapManager.hpp"

class HudManager
{
private:
  std::unique_ptr<Ogre::OverlaySystem>	_mOverlaySystem;
  Ogre::OverlayManager			*_mOverlayManager;
  Ogre::Overlay				*_mOverlay;
  Ogre::FontManager			*_mFontManager;

  int					_sizeHeight;
  int					_sizeWidth;

  MapManager				*_mapManager;
  GameManager				*_gameManager;

  void			setupHudPlayerOne();
  void			setupHudPlayerTwo();
  void			createFont(const std::string &fontName, int size);

public:
  HudManager(GameManager *gameManager);
  ~HudManager();

  void	setHeightSize(int height);
  void	setWidthSize(int width);
  
  void	showHud(MapManager *mapManager);
  void	showPause(MapManager *mapManager);
};

#endif /* !HUDMANAGER_HH_ */
