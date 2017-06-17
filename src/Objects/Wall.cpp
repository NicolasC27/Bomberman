//
// Created by nicolas on 30/05/17.
//

#include <Objects/Wall.hpp>

Wall::Wall(MapManager *map, Wall::State type) : AGameObject(map, BLOCK), _state(type), _positionY(0)
{
  _moveSpeed = 800;
}

Wall::~Wall()
{

}

void 			Wall::update(Ogre::Real dt)
{
  Ogre::Vector3		translateVector = _moveSpeed * dt * Ogre::Vector3(0, 1, 0);

  if (getPositionY() > 0)
    {
      _node->setPosition(_node->getPosition().x,
			 _node->getPosition().y - translateVector.y,
			 _node->getPosition().z);
      setPositionY(_node->getPosition().y);
    }
  else if (getPositionY() <= 0)
    {
      _node->setPosition(_node->getPosition().x,
			 0,
			 _node->getPosition().z);
      setPositionY(0);
    }
}

Wall::State 		Wall::getState() const
{
  return _state;
}

void 			Wall::setState(Wall::State state)
{
  _state = state;
}

std::string 		Wall::getName() const
{
    return  "Wall_" + std::to_string(_id);
}

void			Wall::createEntity()
{
  _obj = SceneManager->createEntity(getName(), Ogre::SceneManager::PT_CUBE);
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());

  static_cast<Ogre::Entity*>(_obj)->getMesh()->_setBounds(Ogre::AxisAlignedBox(-42, -42, -42, 42, 42, 42));

//  _node->showBoundingBox(true);
}

std::string		Wall::getMaterialName() const
{
  if (getState() == Wall::State::UNBREAKABLE)
    return std::string("Objects/Cube/Wall");
  if (getState() == Wall::State::BREAKABLE)
    return std::string("Objects/Cube/Block");

}

Ogre::SceneManager::PrefabType		Wall::getMeshPrefab() const
{
  return (Ogre::SceneManager::PT_CUBE);
}

std::string 		Wall::getMeshName() const
{
  return ("cube.mesh");
}

Ogre::Vector3 		Wall::getScale() const
{
  return (Ogre::Vector3(1.0, 1.0, 1.0));
}

double 		Wall::getPositionY() const
{
  return _positionY;
}

void		Wall::setPositionY(int positionY)
{
  _positionY = positionY;
}

void 		Wall::destroy()
{
  if (_state == BREAKABLE)
    _map->removeObject(this);
  // and drop powerup
  // animation ?
}