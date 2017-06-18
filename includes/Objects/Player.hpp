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
    THROWING,
    PUSHING,
    GODMOD,
    GHOSTMODE
  };
  Player(MapManager *map, Object object, int id =_playerID);
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

 protected:
  static int		_playerID;

private:
  Ogre::Vector3 _vector;
  Ogre::FrameEvent _evt;
  PlayerSettings	settings;
  std::vector<void (Player::*)(void)>	_powerUp;

  std::vector<Ogre::Vector2> const	getFrontObstacle(Ogre::Vector2 const &) const;
  Ogre::Vector2				&getPosFrom(Ogre::Vector2 &) const;

  bool			Collide(Ogre::Vector3 &);
  void 			fire();

 public:

  float 		getNextFireDelay() const;
  float 		getIntervFire() const;
  int 			getBombmax() const;
  int 			getDelaybomb() const;
  int 			getPowerbomb() const;
  float 		getMovespeed() const;
  float 		getProtectDelay() const;
  int                   getAbility() const;
  int                   getMode() const;
  int			getPoint() const;

  void 			setNextFireDelay(Ogre::Real);
  void 			setIntervFire(Ogre::Real);
  void 			setDelaybomb(Ogre::Real);
  void 			setMovespeed(Ogre::Real);
  void 			setBombmax(int);
  void 			setPoints(int);
  void 			setPowerbomb(int);
  void                  setAbility(int);
  void                  setMode(int);

  void	  		powerUp();
  void			maxBombUp();
  void  		speedUp();
  void  		throwing();
  void  		pushing();
  void  		godmode();
  void  		ghostmode();
};
#endif //BOMBERMAN_PLAYER_HPP
