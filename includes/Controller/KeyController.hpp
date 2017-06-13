//
// Created by nicolas on 12/06/17.
//

#ifndef BOMBERMAN_KEYCONTROLLER_HPP
#define BOMBERMAN_KEYCONTROLLER_HPP

#include <OIS/OIS.h>
#include <Ogre.h>

class KeyController
{

  OIS::Keyboard 	*_keyboard;
  OIS::JoyStick		*_joystick;

 public:
  Ogre::ConfigFile 	_Conf;
  bool 			_Loaded;


  KeyController();

  virtual ~KeyController();

  OIS::KeyCode GetOISKeyCode(const std::string& value);
  OIS::KeyCode GetInputName( const std::string& section, const std::string& type);

  void setKeyboard(OIS::Keyboard *keyboard);
  void setJoystick(OIS::JoyStick *joystick);

};
#endif //BOMBERMAN_KEYCONTROLLER_HPP
