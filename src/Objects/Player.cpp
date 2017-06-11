//
// Created by nicolas on 07/06/17.
//

#include "Interfaces/AGameObject.hpp"
#include "Interfaces/ACharacter.hpp"
#include "Objects/Player.hpp"

Player::Player(AGameObject::Object object) : ACharacter(object, 5)
{

}

Player::~Player()
{

}
