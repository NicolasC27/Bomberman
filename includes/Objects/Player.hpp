//
// Created by nicolas on 07/06/17.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP


#include <MapManager.hpp>
#include <Interfaces/AGameObject.hpp>
#include <Interfaces/ACharacter.hpp>
#include <vector>
#include "PlayerSettings.hpp"

class Player : public ACharacter
{
 public:
  enum {
    POWERUP,
    MAXBOMBUP,
    SPEEDUP,
    BOMB,
    UPNBR
  };
  enum {
    NORMALBOMB,
    SKULLBOMB,
    LASERBOMB,
    NBRBOMB
  };
  Player(MapManager *map, Object object, int id);
  virtual ~Player();

  void 			move(Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt);
  void 			setKey();

  void			action(ActionKeyCode, const Ogre::FrameEvent &);

  void 			update(Ogre::Real);
  virtual void 		destroy();
  void			reset();
  void      		tick();

  const std::map<OIS::KeyCode, ActionKeyCode>	&getKeyCodeType() const;

protected:
  Ogre::Vector3 translateVector;
  int			_ID;
 public:
  int getID() const;

private:
  Ogre::Vector3 _vector;
  Ogre::FrameEvent _evt;
  PlayerSettings	settings;
  std::vector<void (Player::*)(void)>	_powerUp;

  std::vector<Ogre::Vector2> const	getFrontObstacle(Ogre::Vector2 const &) const;

  bool			Collide(Ogre::Vector3 &);
  void 			fire();

 public:

  int 			getBombmax() const;
  int 			getCurrBomb() const;
  int 			getPowerbomb() const;
  int	 		getMovespeed() const;
  int			getPoint() const;
  int 			getBombType() const;
  std::string		getMaterialName() const;

  void 			setStat();

  void 			setMovespeed(Ogre::Real);
  void 			setBombmax(int);
  void 			setCurrBomb(int);
  void 			setPoints(int);
  void 			setPowerbomb(int);
  void 			setBombType(int);

  void	  		powerUp();
  void			maxBombUp();
  void  		speedUp();
  void 			skullBomb();
  void 			laserBomb();

};
#endif //BOMBERMAN_PLAYER_HPP
