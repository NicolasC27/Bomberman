//
// Created by nicolas on 30/05/17.
//

#include <Wall.hpp>

Wall::Wall(Wall::State type) : AGameObject(AGameObject::BLOCK), _state(type)
{

}

Wall::~Wall()
{

}

Wall::State Wall::getState() const
{
  return _state;
}

void Wall::setState(Wall::State state)
{
  _state = state;
}
