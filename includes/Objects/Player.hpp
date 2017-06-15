//
// Created by nicolas on 07/06/17.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include "Interfaces/ACharacter.hpp"

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


};
#endif //BOMBERMAN_PLAYER_HPP
