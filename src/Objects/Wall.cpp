//
// Created by nicolas on 30/05/17.
//

#include <Objects/Wall.hpp>
#include <Objects/Item.hpp>

Wall::Wall(MapManager *map, Wall::State type) : AGameObject(map, BLOCK), _state(type), _positionY(0)
{
  _moveSpeed = 800;
}

Wall::~Wall()
{
  _map->addObjects(Ogre::Vector2(_node->getPosition().x,
				 _node->getPosition().z),
  		   new Item(_map, AGameObject::ITEM));
}

void 			Wall::update(Ogre::Real dt)
{
  if (getPositionY() > 0)
    {
      _node->setPosition(_node->getPosition() - (_moveSpeed * dt * Ogre::Vector3(0, 1, 0)));
      setPositionY(_node->getPosition().y);
      if (getPositionY() < 50)
	{
	  Ogre::Vector2	pos(_map->getPosFrom(Ogre::Vector2(_node->getPosition().x, _node->getPosition().z)));
	  AGameObject		*obj = _map->getObjectFrom(pos);
	  MapManager::Character	victim = _map->getCharacterFrom(pos);
	  for (unsigned int i = 0; i < victim.size() ; ++i)
	    victim[i]->destroy();
	  if (obj != NULL)
	    obj->destroy();
	}
    }
  else if (getPositionY() < 0)
    {
      setPositionY(0);
      _node->setPosition(_node->getPosition().x,
			 0,
			 _node->getPosition().z);
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
  // animation ?
}