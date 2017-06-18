//
// HudManager.cpp for cpp_indie_studio in /home/ikirame/Documents/Projects/cpp_indie_studio/src
// 
// Made by Valentin Gérard
// Login   <valentin.gerard@epitech.eu>
// 
// Started on  Sat Jun 17 23:18:26 2017 Valentin Gérard
// Last update Sun Jun 18 13:43:20 2017 Valentin Gérard
//

#include <iomanip>
#include "HudManager.hh"

int			sizeHeight = 0;
int			sizeWidth = 0;

HudManager::HudManager(GameManager *gameManager) : _gameManager(gameManager)
{
  this->_mOverlaySystem.reset(OGRE_NEW Ogre::OverlaySystem);
  if (this->_mOverlaySystem.get() == NULL)
    throw Ogre::Exception(0, "HudManager", "HudManager");
  this->_gameManager->getSceneManager()->addRenderQueueListener(this->_mOverlaySystem.get());
  this->_mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
  if (this->_mOverlayManager == NULL)
    throw Ogre::Exception(0, "HudManager", "HudManager");
  this->_mOverlay = this->_mOverlayManager->create("HudOverlay");
  if (this->_mOverlay == NULL)
    throw Ogre::Exception(0, "HudManager", "HudManager");
  this->_mFontManager = Ogre::FontManager::getSingletonPtr();
  if (this->_mFontManager == NULL)
    throw Ogre::Exception(0, "HudManager", "HudManager");
  this->createFont("Vera", 64);
  this->setupHudPlayerOne();
  this->setupHudPlayerTwo();
  this->setHeightSize(this->_gameManager->_Window->getHeight());
  this->setWidthSize(this->_gameManager->_Window->getWidth());
}

void	HudManager::setHeightSize(int height)
{
  this->_sizeHeight = height;
}

void	HudManager::setWidthSize(int width)
{
  this->_sizeWidth = width;
}

HudManager::~HudManager()
{}

void			HudManager::createFont(const std::string &fontName, int size)
{
  Ogre::ResourcePtr	font;

  font = this->_mFontManager->create(fontName, "General");
  if (font.get() == NULL)
    return ;
  font->setParameter("type", "truetype");
  font->setParameter("source", "fonts/" + fontName + ".ttf");
  font->setParameter("size", std::to_string(size));
  font->setParameter("resolution", "96");
  font->load();
}

void				HudManager::setupHudPlayerOne()
{
  Ogre::OverlayContainer       	*hudPanelPlayerOne;
  Ogre::TextAreaOverlayElement 	*hudTextBomb;
  Ogre::TextAreaOverlayElement 	*hudTextSpeed;
  Ogre::TextAreaOverlayElement 	*hudTextScore;

  hudPanelPlayerOne = static_cast<Ogre::OverlayContainer*>(this->_mOverlayManager->createOverlayElement("Panel", "HudPanelPlayerOne"));
  hudTextBomb = static_cast<Ogre::TextAreaOverlayElement*>(this->_mOverlayManager->createOverlayElement("TextArea", "hudTextBomb"));
  hudTextSpeed = static_cast<Ogre::TextAreaOverlayElement*>(this->_mOverlayManager->createOverlayElement("TextArea", "hudTextSpeed"));
  hudTextScore = static_cast<Ogre::TextAreaOverlayElement*>(this->_mOverlayManager->createOverlayElement("TextArea", "hudTextScore"));

  if (hudPanelPlayerOne == NULL || hudTextBomb == NULL ||
      hudTextSpeed == NULL || hudTextScore == NULL)
    return ;
  hudPanelPlayerOne->setMaterialName("hudPlayerOne");
  hudPanelPlayerOne->setDimensions(281, 627);
  hudPanelPlayerOne->setPosition(0, 0);
  hudPanelPlayerOne->setMetricsMode(Ogre::GMM_PIXELS);
  this->_mOverlay->add2D(hudPanelPlayerOne);
  hudTextBomb->setMetricsMode(Ogre::GMM_PIXELS);
  hudTextBomb->setPosition(170, 425);
  hudTextBomb->setDimensions(100, 100);
  hudTextBomb->setCaption("0");
  hudTextBomb->setCharHeight(64);
  hudTextBomb->setFontName("Vera");
  hudTextBomb->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
  hudTextBomb->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));
  hudPanelPlayerOne->addChild(hudTextBomb);
  hudTextSpeed->setMetricsMode(Ogre::GMM_PIXELS);
  hudTextSpeed->setPosition(170, 325);
  hudTextSpeed->setDimensions(100, 100);
  hudTextSpeed->setCaption("0");
  hudTextSpeed->setCharHeight(64);
  hudTextSpeed->setFontName("Vera");
  hudTextSpeed->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
  hudTextSpeed->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));
  hudPanelPlayerOne->addChild(hudTextSpeed);
  hudTextScore->setMetricsMode(Ogre::GMM_PIXELS);
  hudTextScore->setPosition(170, 525);
  hudTextScore->setDimensions(100, 100);
  hudTextScore->setCaption("0");
  hudTextScore->setCharHeight(64);
  hudTextScore->setFontName("Vera");
  hudTextScore->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
  hudTextScore->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));
  hudPanelPlayerOne->addChild(hudTextScore);
}

void				HudManager::setupHudPlayerTwo()
{
  Ogre::OverlayContainer       	*hudPanelPlayerTwo;
  Ogre::TextAreaOverlayElement 	*hudTextBomb;
  Ogre::TextAreaOverlayElement 	*hudTextSpeed;
  Ogre::TextAreaOverlayElement 	*hudTextScore;

  hudPanelPlayerTwo = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "HudPanelPlayerTwo"));
  if (hudPanelPlayerTwo == NULL)
    return ;
  hudPanelPlayerTwo->setMaterialName("hudPlayerTwo");
  hudPanelPlayerTwo->setDimensions(281, 627);
  hudPanelPlayerTwo->setPosition(0, 0);
  hudPanelPlayerTwo->setMetricsMode(Ogre::GMM_PIXELS);
  this->_mOverlay->add2D(hudPanelPlayerTwo);
}

void					HudManager::showHud(MapManager *mapManager)
{
  Ogre::OverlayContainer		*hudPanelPlayerOne;
  Ogre::OverlayContainer		*hudPanelPlayerTwo;
  Ogre::TextAreaOverlayElement		*hudTextBomb;
  Ogre::TextAreaOverlayElement		*hudTextSpeed;
  Ogre::TextAreaOverlayElement		*hudTextScore;
  double				percentHeight;
  double				percentWidth;

  hudPanelPlayerOne = static_cast<Ogre::OverlayContainer*>(this->_mOverlayManager->getOverlayElement("HudPanelPlayerOne"));
  percentHeight = ((this->_gameManager->_Window->getHeight() * 100) / this->_sizeHeight);
  percentWidth = ((this->_gameManager->_Window->getWidth() * 100) / this->_sizeWidth);
  hudPanelPlayerOne->setPosition(0, 0);
  hudPanelPlayerOne->setDimensions(281.0 * (percentWidth / 100), 627.0 * (percentHeight / 100));
  hudPanelPlayerOne->setDimensions(281.0 * (percentWidth / 100), 627.0 * (percentHeight / 100));

  hudPanelPlayerTwo = static_cast<Ogre::OverlayContainer*>(this->_mOverlayManager->getOverlayElement("HudPanelPlayerTwo"));
  percentHeight = ((this->_gameManager->_Window->getHeight() * 100) / this->_sizeHeight);
  percentWidth = ((this->_gameManager->_Window->getWidth() * 100) / this->_sizeWidth);
  hudPanelPlayerTwo->setPosition(this->_gameManager->_Window->getWidth() - (281 * (percentWidth / 100)), 0);
  hudPanelPlayerTwo->setDimensions(281.0 * (percentWidth / 100), 627.0 * (percentHeight / 100));

  hudTextBomb = static_cast<Ogre::TextAreaOverlayElement*>(this->_mOverlayManager->getOverlayElement("hudTextBomb"));
  hudTextBomb->setPosition(170 * (percentWidth / 100), 425 * (percentHeight / 100));
  hudTextBomb->setCharHeight(64 * (percentHeight / 100));

  hudTextSpeed = static_cast<Ogre::TextAreaOverlayElement*>(this->_mOverlayManager->getOverlayElement("hudTextSpeed"));
  hudTextSpeed->setPosition(170 * (percentWidth / 100), 325 * (percentHeight / 100));
  hudTextSpeed->setCharHeight(64 * (percentHeight / 100));

  hudTextScore = static_cast<Ogre::TextAreaOverlayElement*>(this->_mOverlayManager->getOverlayElement("hudTextScore"));
  hudTextScore->setPosition(170 * (percentWidth / 100), 525 * (percentHeight / 100));
  hudTextScore->setCharHeight(64 * (percentHeight / 100));
  
  this->_mOverlay->show();
}

void			HudManager::showPause(MapManager *mapManager)
{
}
