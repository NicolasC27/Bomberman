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

Ogre::Vector2		Player::getPosFrom(Ogre::Vector3 const &tmp) const
{
  return (Ogre::Vector2(tmp.x - std::fmod(tmp.x, 100), tmp.z - std::fmod(tmp.z, 100)));
}

Ogre::Vector2		&Player::getPosFrom(Ogre::Vector2 &tmp) const
{
  float                 diffx = std::fmod(tmp.x, 100);
  float                 diffy = std::fmod(tmp.y, 100);

  tmp.x -= diffx;
  tmp.y -= diffy;
  if (diffx > 50.0f)
    tmp.x +=  100;
  if (diffy > 50.0f)
    tmp.y += 100;
  return (tmp);
}

bool			Player::Collide(MapManager const &map, Ogre::Vector3 const &m) const
{
  Ogre::Vector2         mov(m.x, m.z);
  std::vector<Ogre::Vector2>	 pos = this->getFrontObstacle(mov);
  Ogre::AxisAlignedBox	aab1(_obj->getWorldBoundingBox());
  aab1.setMinimum(aab1.getMinimum() * 1.05f);
  aab1.setMaximum(aab1.getMaximum() * 1.05f);
  Ogre::AxisAlignedBox	aab2;
  AGameObject		*ptr;

  for (unsigned int i = 0; i < pos.size(); ++i)
    {
      if ((ptr = map.getObjectFrom(this->getPosFrom(pos[i]))) != NULL)
	{
	  ptr->getNode()->showBoundingBox(true);
	  aab2 = ptr->getObj()->getWorldBoundingBox();
	  std::cout << _node->getPosition() << " intesects " << aab2.getCenter() << " ?" << std::endl;
	  if (aab1.intersects(aab2))
	    return (true);
	}
    }
  return (false);
}

std::vector<Ogre::Vector2> const	Player::getFrontObstacle(Ogre::Vector2 const &mov) const
{
  std::vector<Ogre::Vector2>	pos;
  Ogre::Vector2			tmp(_node->getPosition().x,
				    _node->getPosition().z);

  tmp = this->getPosFrom(tmp);
  std::cout << "pos " << _node->getPosition() << " direction : " << mov << " which gives " << tmp << std::endl;
  if (mov.x > 0.0)
    {
      pos.push_back(tmp + Ogre::Vector2(100, -100));
      pos.push_back(tmp + Ogre::Vector2(100, 0));
      pos.push_back(tmp + Ogre::Vector2(100, 100));
    }
  else if (mov.x < 0.0)
    {
	pos.push_back(tmp + Ogre::Vector2(-100, -100));
	pos.push_back(tmp + Ogre::Vector2(-100, 0));
	pos.push_back(tmp + Ogre::Vector2(-100, 100));
    }
  else if (mov.y > 0.0)
    {
	  pos.push_back(tmp + Ogre::Vector2(-100, 100));
	  pos.push_back(tmp + Ogre::Vector2(0, 100));
	  pos.push_back(tmp + Ogre::Vector2(100, 100));
    }
  else if (mov.y < 0.0)
    {
	    pos.push_back(tmp + Ogre::Vector2(-100, -100));
	    pos.push_back(tmp + Ogre::Vector2(0, -100));
	    pos.push_back(tmp + Ogre::Vector2(100, -100));
    }
  return (pos);
}

void			Player::move(MapManager const &map,
				     Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt)
{
  static Ogre::AnimationState *mAnimationState;
  Ogre::Vector3 translateVector = evt.timeSinceLastFrame * _moveSpeed * vector;

  mAnimationState = dynamic_cast<Ogre::Entity*>(_obj)->getAnimationState("my_animation");
  mAnimationState->setLoop(true);
  mAnimationState->setEnabled(true);
  if (translateVector != Ogre::Vector3::ZERO)
  {
    Ogre::Vector3 src = _node->getOrientation() * Ogre::Vector3::UNIT_Z;
    Ogre::Vector3 mDirection = vector;
    mDirection.normalise();
    translateVector *= this->Collide(map, translateVector) ? -10 : 1;
    _node->translate(translateVector);
    if ((1.0f + src.dotProduct(mDirection)) < 0.0001f)
      _node->yaw(Ogre::Degree(180));
    else
    {
      Ogre::Quaternion quat = src.getRotationTo(mDirection);
      _node->rotate(quat);
    }
    //  _node->translate(translateVector);
  }
  mAnimationState->addTime(evt.timeSinceLastFrame * 1.5f);
}

void			Player::action(MapManager const &map, ActionKeyCode action, const Ogre::FrameEvent &evt)
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

const std::map<OIS::KeyCode, ACharacter::ActionKeyCode>	&Player::getKeyCodeType() const
{
  return (keyCodeType);
}
