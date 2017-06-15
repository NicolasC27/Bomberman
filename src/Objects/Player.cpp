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

Ogre::Vector2		&Player::getPosFrom(Ogre::Vector2 &tmp, Ogre::Vector3 const &mov) const
{
  float 		diffx = std::fmod(tmp.x, 100);
  float 		diffy = std::fmod(tmp.y, 100);

  tmp.x -= diffx;
  tmp.y -= diffy;
  /*if (mov.x == 1)
    {
      tmp.y += diffy < 50.0 ? 100 : 0;
      tmp.x += 100;
    }
  else if (mov.z == 1)
    {
      tmp.x += diffx < 50.0 ? 100 : 0;
      tmp.y += 100;
    }
  */return (tmp);
}

bool			Player::Collide(MapManager const &map, Ogre::Vector3 const &mov) const
{
  std::vector<Ogre::Vector2>	const pos = this->getFrontObstacle(mov);
  Ogre::AxisAlignedBox	aab1 = _obj->getWorldBoundingBox();
  Ogre::AxisAlignedBox	aab2;
  AGameObject		*ptr;

  for (unsigned int i = 0; i < pos.size(); ++i)
    {
      std::cout << "search " << pos[i] << std::endl;
      // vérifie si il y a collision
      if ((ptr = map.getObjectFrom(pos[i])) != NULL)
	{
	  aab2 = ptr->getObj()->getWorldBoundingBox();
	  std::cout << aab2 << " intesects " << aab1 << " ?" << std::endl;
	  if (aab1.intersects(aab2))
	    return (true);
	}
    }
  std::cout << std::endl;
  return (false);
}

std::vector<Ogre::Vector2> const	Player::getFrontObstacle(Ogre::Vector3 const &mov) const
{
  std::vector<Ogre::Vector2>	pos;
  Ogre::Vector2			tmp(_node->getPosition().x + mov.x,
				    _node->getPosition().z + mov.z);

  tmp = this->getPosFrom(tmp, mov);
  std::cout << _node->getPosition() << " direction : " << mov << "which gives " << tmp << std::endl;
  pos.push_back(tmp);
  /*if (mov.x > 0.0)
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
  else
    {
      pos.push_back(tmp + Ogre::Vector2(-100, -100));
      pos.push_back(tmp + Ogre::Vector2(0, -100));
      pos.push_back(tmp + Ogre::Vector2(100, -100));
    }
  for (unsigned int i = 0; i < pos.size(); ++i)
    pos[i] = this->getPosFrom(pos[i]);*/
  //tmp = this->getPosFrom(tmp, mov);
  pos.push_back(tmp - Ogre::Vector2(100, -100));
  pos.push_back(tmp - Ogre::Vector2(100, 0));
  pos.push_back(tmp - Ogre::Vector2(100, 100));
  pos.push_back(tmp - Ogre::Vector2(-100, -100));
  pos.push_back(tmp - Ogre::Vector2(-100, 0));
  pos.push_back(tmp - Ogre::Vector2(-100, 100));
  pos.push_back(tmp - Ogre::Vector2(0, 100));
  pos.push_back(tmp - Ogre::Vector2(0, -100));
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
    //_node->translate(translateVector);
    //Rotate the object to the moving direction
      /*{
	std::cout << "translate vector : " << translateVector;
	translateVector.perpendicular();
	std::cout << "perpandicular translate vector : " << translateVector << std::endl;
	_node->translate(translateVector / -2);
	std::cout << "----COLLISION----" << std::endl;
      }
    else
      {*/
	if (translateVector != Ogre::Vector3::ZERO)
	  {
	    Ogre::Vector3 src = _node->getOrientation() * Ogre::Vector3::UNIT_Z;
	    Ogre::Vector3 mDirection = vector;
	    mDirection.normalise();
	    translateVector *= this->Collide(map, translateVector) ? -1 : 1;
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
      //}

    mAnimationState->addTime(evt.timeSinceLastFrame * 1.5);
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
