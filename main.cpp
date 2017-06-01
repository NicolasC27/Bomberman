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
  Root* root = new Root;

  // Configures the application
  if (!root->restoreConfig())
    root->showConfigDialog();
  root->saveConfig();

  // Create a render window
  RenderWindow* window = root->initialise(true, "Tutorial 1");

  // Create a new scene manager.
  SceneManager* sceneManager = root->createSceneManager(ST_GENERIC);
  sceneManager->setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));

  // Create a new camera
  Camera* camera = sceneManager->createCamera("Camera");
  camera->setPosition(Ogre::Vector3(0,0,15));
  camera->lookAt(Ogre::Vector3(0,0,0));
  camera->setNearClipDistance(5);

  // Add our model to our resources and index it
  ResourceGroupManager::getSingleton().addResourceLocation("Media/packs/Sinbad.zip", "Zip");
  ResourceGroupManager::getSingleton().addResourceLocation("Media/", "FileSystem");
  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  Light* light1 = sceneManager->createLight("Light1");
  light1->setType(Ogre::Light::LT_POINT);
  // Set Light Color
  light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
  // Set Light Reflective Color
  light1->setSpecularColour(1.0f, 0.0f, 0.0f);
  // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
  light1->setAttenuation(10, 0.5, 0.045, 0.0);

  Entity* lightEnt = sceneManager->createEntity("LightEntity", "models/sphere.mesh");
  SceneNode* lightNode = sceneManager->createSceneNode("LightNode");
  lightNode->attachObject(lightEnt);
  lightNode->attachObject(light1);
  lightNode->setScale(0.01f, 0.01f, 0.01f);
  lightNode->setPosition(0, 4, 10);
  sceneManager->getRootSceneNode()->addChild(lightNode);


  // Using the camera create a viewport and set the background color to black
  Viewport* viewport = window->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));

  // Use the viewport to set the aspect ratio of the camera
  camera->setAspectRatio(Real(viewport->getActualWidth()) /
			 Real(viewport->getActualHeight()));

  // Create an instance of our model and add it to the scene
  Entity* ent = sceneManager->createEntity("Sinbad.mesh");
  SceneNode* entNode = sceneManager->createSceneNode("Character");
  entNode->attachObject(ent);
  sceneManager->getRootSceneNode()->addChild(entNode);
  entNode->setPosition(0,0,0);

  EventManager* myListener = new EventManager();
  myListener->initialize(entNode, window, camera);
  root->addFrameListener(myListener);

  // Tell root to start rendering
  root->startRendering();

  // Cleanup
  delete root;

  return 0;

}

int 		main()
{
  try
    {
      Map map;
      map.generateObjects();
//      test();
    }  catch (const Ogre::Exception &exception) {

      std::cerr << exception.what() << std::endl;
      return (EXIT_FAILURE);
    }
}
