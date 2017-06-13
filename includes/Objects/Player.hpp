//
// Created by nicolas on 07/06/17.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include "Controller/KeyController.hpp"
#include "Interfaces/ACharacter.hpp"

class Player : public ACharacter
{
 public:
  Player(Object object);
  virtual ~Player();

  void 			move(Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt);
  void 			setKey();

  void			action(ActionKeyCode, const Ogre::FrameEvent &);

  const std::map<OIS::KeyCode, ActionKeyCode>	&getKeyCodeType() const;

  KeyController		*key;

 protected:
  int			_ID;
  static int		_playerID;


};
#endif //BOMBERMAN_PLAYER_HPP
