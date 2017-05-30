//
// Created by nicolas on 29/05/17.
//

#include "AGameObject.hpp"

AGameObject::AGameObject(Object object)
{

}

AGameObject::~AGameObject()
{

}

AGameObject::AGameObject()
{}

AGameObject::Object AGameObject::getType() const
{
  return _type;
}

void AGameObject::setType(AGameObject::Object type)
{
  _type = type;
}


