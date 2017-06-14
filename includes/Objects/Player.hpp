//
// Created by nicolas on 07/06/17.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include <MapManager.hpp>
#include <Interfaces/AGameObject.hpp>
#include <Interfaces/ACharacter.hpp>

class Player : public ACharacter
{
 public:
  Player(AGameObject::Object object);
  virtual ~Player();

  void 			move(MapManager const &, Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt);
  void 			setKey();

  void			action(MapManager const &, ActionKeyCode, const Ogre::FrameEvent &);

  void 			update();

  const std::map<OIS::KeyCode, ActionKeyCode>	&getKeyCodeType() const;

 protected:
  int			_ID;
  static int		_playerID;


};
#endif //BOMBERMAN_PLAYER_HPP
