//
// Created by nicolas on 07/06/17.
//

#include <Ogre.h>
#include <Objects/Bomb.hpp>
#include "Interfaces/ACharacter.hpp"
#include "Objects/Player.hpp"

int Player::_playerID = 1;

Player::Player(AGameObject::Object object) : ACharacter(object, 35), _ID(_playerID++)
{
  _moveSpeed = 400;
  keyCodeType.clear();
  setKey();
}

Player::~Player()
{

}

void 				Player::update()
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

void 				Player::move(MapManager const &map,
					     Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt)
{
    static Ogre::AnimationState *mAnimationState;
    AGameObject			*object;
    mAnimationState = dynamic_cast<Ogre::Entity*>(_obj)->getAnimationState("my_animation");

    Ogre::Vector3 translateVector = evt.timeSinceLastFrame * _moveSpeed * vector;

    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

    _node->translate(translateVector);
    //Rotate the object to the moving direction
    object = map.getObjectFrom(_node->getPosition(), vector);
    if (object != NULL)
      {
	std::cout << "calcul de position entre " << _node->getPosition() << " et " << vector
	      << " = " << _node->getPosition() + vector << std::endl;
    	std::cout << "object proche (position:" << object->getNode()->getPosition() << " ) "
	      << object->getObj()->getBoundingBox() << std::endl;
    	std::cout << "object courant (position:" << _node->getPosition() << " ) "
	      << _obj->getBoundingBox() << std::endl;
	if (_obj->getBoundingBox().intersects(object->getObj()->getBoundingBox()))
	  {
	    std::cout << "----COLLISION----" << std::endl;
	  }
      }
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
    std::cout << "x : " << _node->getPosition().x << "z: " << _node->getPosition().z << std::endl;
}

void Player::action(MapManager const &map, ActionKeyCode action, const Ogre::FrameEvent &evt)
{
  if (action == Player::AT_UP)
    move(map ,Ogre::Vector3(0, 0, -1), evt);
  else
    if (action == Player::AT_DOWN)
      move(map, Ogre::Vector3(0, 0, 1), evt);
    else
      if (action == Player::AT_LEFT)
	move(map, Ogre::Vector3(-1, 0, 0), evt);
      else
	if (action == Player::AT_RIGHT)
	  move(map, Ogre::Vector3(1, 0, 0), evt);
	else
	  if (action == Player::AT_FIRE)
	    {
	      std::cout << "JE PASSE" << std::endl;
	      Bomb *test;

	      test = new Bomb(AGameObject::BOMB);
	      test->setSceneManager(SceneManager);
	      test->createEntity();
	      test->setPosition(_node->getPosition().x, _node->getPosition().y, _node->getPosition().z);
	      test->AttachObject();
	      test->Explosion();
	    }
}

const std::map<OIS::KeyCode, ACharacter::ActionKeyCode> &
Player::getKeyCodeType() const
{
  return keyCodeType;
}
