//
// Created by nicolas on 07/06/17.
//

#include <Ogre.h>
#include "Objects/Bomb.hpp"
#include "Interfaces/ACharacter.hpp"
#include "Objects/Player.hpp"

int Player::_playerID = 1;

Player::Player(MapManager *map, AGameObject::Object object) : ACharacter(map, object, 35), _ID(_playerID++)
{
  _moveSpeed = 400;
  keyCodeType.clear();
  setKey();
}

Player::~Player()
{

}

void 				Player::update(Ogre::Real dt)
{

}

void 				Player::setKey()
{
  if (_ID <= 2)
    {
      if (_ID == 1)
	{
	  keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_LEFT, AT_LEFT));
	  keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_RIGHT, AT_RIGHT));
	  keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_UP, AT_UP));
	  keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_DOWN, AT_DOWN));
	  keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_E, AT_FIRE));
	} else if (_ID == 2)
	  {
	    keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_A, AT_LEFT));
	    keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_D, AT_RIGHT));
	    keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_W, AT_UP));
	    keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_S, AT_DOWN));
	    keyCodeType.insert(std::pair<OIS::KeyCode, ActionKeyCode>(OIS::KC_T, AT_FIRE));

	  }
    }
}

void 				Player::move(Ogre::Vector3 const &vector,
						 const Ogre::FrameEvent &evt)
{
    static Ogre::AnimationState *mAnimationState;

    mAnimationState = dynamic_cast<Ogre::Entity*>(_obj)->getAnimationState("my_animation");

    Ogre::Vector3 translateVector = evt.timeSinceLastFrame * _moveSpeed * vector;

    Collision *test;

    test = new Collision((Ogre::Vector2(100, 100)));

    test->setOrigin(Ogre::Vector2(200, 200));
  static_cast<Ogre::Entity*>(_obj)->getMesh()->_setBounds(Ogre::AxisAlignedBox(-125.152 * 0.3, -0.594098, -34.2034, 149.101 * 0.3, 185.54, 36.3049));
  _node->showBoundingBox(true);


  if (*_collision == *test)
    std::cout << "COLLISION" << std::endl;
  else
    {

    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

    _node->translate(translateVector);
    //Rotate the object to the moving direction
      _collision->setOrigin(Ogre::Vector2(_node->getPosition().x - 50, _node->getPosition().z) - 50);

      if (translateVector != Ogre::Vector3::ZERO)
	{
	  Ogre::Vector3 src = _node->getOrientation() * Ogre::Vector3::UNIT_Z;
	  Ogre::Vector3 mDirection = vector;
	  mDirection.normalise();

	  if ((1.0f + src.dotProduct(mDirection)) < 0.0001f)
	    {
	      _node->yaw(Ogre::Degree(180));
	    } else
	    {
	      Ogre::Quaternion quat = src.getRotationTo(mDirection);
	      _node->rotate(quat);

	    } // else
	}
      mAnimationState->addTime(evt.timeSinceLastFrame * 1.5);
      std::cout << "x : " << _node->getPosition().x << "z: " << _node->getPosition().z
		<< std::endl;
    }
}

void Player::action(ActionKeyCode action, const Ogre::FrameEvent &evt)
{
  if (action == Player::AT_UP)
    move(Ogre::Vector3(0, 0, -1), evt);
  else
    if (action == Player::AT_DOWN)
      move(Ogre::Vector3(0, 0, 1), evt);
    else
      if (action == Player::AT_LEFT)
	move(Ogre::Vector3(-1, 0, 0), evt);
      else
	if (action == Player::AT_RIGHT)
	  move(Ogre::Vector3(1, 0, 0), evt);
	else
	  if (action == Player::AT_FIRE)
	    {
	      _map->addObjects(Ogre::Vector2(_node->getPosition().x, _node->getPosition().z), new Bomb(_map, AGameObject::BOMB));
	    }
}

const std::map<OIS::KeyCode, ACharacter::ActionKeyCode> &
Player::getKeyCodeType() const
{
  return keyCodeType;
}
