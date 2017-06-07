//
// Created by nicolas on 29/05/17.
//


#include "Common/Manager/GameManager.hpp"

int main(int argc, char **argv)
{
  GameManager app;

  try
    {
      app.run();
    }
  catch (Ogre::Exception &e) {
      std::cerr << "An exception has occured: " << e.getFullDescription();
    }
  return 0;
}