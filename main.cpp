//
// Created by root on 29/05/17.
//


#include "Map.hpp"
#include <OgreException.h>

int main()
{
  Map test;
  try
    {
      test.generate();
    }  catch (const Ogre::Exception &exception) {

      std::cerr << exception.what() << std::endl;
      return (EXIT_FAILURE);
    }
}