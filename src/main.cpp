//
// Created by nicolas on 29/05/17.
//


#include "Map.hpp"
#include <Ogre.h>
#include "EventManager.hpp"

using namespace Ogre;

static int		test()
{
  // Create an instance of the OGRE Root Class
  Ogre::Root *root;

  root = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

  Ogre::ConfigFile configFile;

  configFile.load("resources.cfg");

  Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();

  Ogre::String secName, typeName, archName;

  while (seci.hasMoreElements())

    {

      secName = seci.peekNextKey();

      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();

      Ogre::ConfigFile::SettingsMultiMap::iterator i;

      for (i = settings->begin(); i != settings->end(); ++i)

	{

	  typeName = i->first;

	  archName = i->second;

	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(

		  archName, typeName, secName);

	}

    }

  Ogre::RenderSystem *rs = root->getRenderSystemByName("OpenGL Rendering Subsystem"); // Pour OpenGL : "OpenGL Rendering Subsystem"

  root->setRenderSystem(rs);

  rs->setConfigOption("Full Screen", "No");

  rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");

  rs->setConfigOption("VSync", "Yes");

  Ogre::ConfigOptionMap map = rs->getConfigOptions();

  for(Ogre::ConfigOptionMap::const_iterator it = map.begin(); it != map.end(); it++)

    {

      std::cout << it->first << std::endl; // affiche la clé, par exemple "Full Screen"

      for(int i = 0; i < it->second.possibleValues.size(); i++)           // affiche les valeurs possible pour cette clé

	std::cout << "  " << it->second.possibleValues[i] << std::endl; // par exemple : "Yes", "No"

    }

//


  // Create a render window
  RenderWindow* window = root->initialise(true, "Tutorial 1");

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


  // Create a new scene manager.
  SceneManager* sceneManager = root->createSceneManager(ST_GENERIC);
  sceneManager->setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));

  // Create a new camera
  Camera* camera = sceneManager->createCamera("Camera");
  camera->setPosition(Ogre::Vector3(200,200,200));
  camera->lookAt(Ogre::Vector3(0,0,0));
  camera->setNearClipDistance(5);

  // Add our model to our resources and index it
//  ResourceGroupManager::getSingleton().addResourceLocation("media/packs/Sinbad.zip", "Zip");
//  ResourceGroupManager::getSingleton().addResourceLocation("media/", "FileSystem");
//  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

//  Plane plan(Vector3::UNIT_Y, 0);
//  MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//					  plan, 500, 500, 1, 1, true, 1, 1, 1, Vector3::UNIT_Z);
//
//  Entity *sol= sceneManager->createEntity("EntiteSol", "sol");
//
//  sol->setMaterialName("Examples/GrassFloor");
//


//  Entity* lightEnt = sceneManager->createEntity("LightEntity", "models/sphere.mesh");
//  SceneNode* lightNode = sceneManager->createSceneNode("LightNode");
//  lightNode->attachObject(lightEnt);
//  lightNode->attachObject(light1);
//  lightNode->setScale(0.01f, 0.01f, 0.01f);
//  lightNode->setPosition(0, 4, 10);
//  sceneManager->getRootSceneNode()->addChild(lightNode);


  // Using the camera create a viewport and set the background color to black
  Viewport* viewport = window->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));

  // Use the viewport to set the aspect ratio of the camera
  camera->setAspectRatio(Real(viewport->getActualWidth()) /
			 Real(viewport->getActualHeight()));

  sceneManager->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

  // Create an instance of our model and add it to the scene
  Ogre::Entity* ent = sceneManager->createEntity("cube", "cube.mesh");
  sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
  ent->setMaterialName("cube");


// // Create an instance of the MyFrameListener Class and add it to the root object
  EventManager* myListener = new EventManager(window, camera);
  root->addFrameListener(myListener);

  // Tell root to start rendering
  root->startRendering();

  // Cleanup
  delete root;

  return 0;

}

int 			main()
{
  try
    {
//      Map map;
//      map.generateObjects();
      test();
    }  catch (const Ogre::Exception &exception) {

      std::cerr << exception.what() << std::endl;
      return (EXIT_FAILURE);
    }
}
