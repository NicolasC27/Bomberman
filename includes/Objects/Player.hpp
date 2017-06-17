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
  Player(MapManager *map, Object object);
  virtual ~Player();

  void 			move(Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt);
  void 			setKey();

  void			action(ActionKeyCode, const Ogre::FrameEvent &);

  void 			update(Ogre::Real);

  const std::map<OIS::KeyCode, ActionKeyCode>	&getKeyCodeType() const;

protected:
  int			_ID;
  static int		_playerID;

private:

  PlayerSettings	settings;

  std::vector<Ogre::Vector2> const	getFrontObstacle(Ogre::Vector2 const &) const;
  Ogre::Vector2				&getPosFrom(Ogre::Vector2 &) const;

  bool			Collide(Ogre::Vector3 &) const;
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
  
  
  void 			setNextFireDelay(Ogre::Real nextFireDelay);
  void 			setIntervFire(Ogre::Real intervFire);
  void 			setDelaybomb(Ogre::Real delaybomb);
  void 			setMovespeed(Ogre::Real movespeed);
  void 			setBombmax(int bombmax);
  void 			setPowerbomb(int powerbomb);
  void                  setAbility(int ability);
  void                  setMode(int mod);
  
};
#endif //BOMBERMAN_PLAYER_HPP
