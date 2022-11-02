#include "Lighting.h"

Lighting::Lighting()
{
	//create light objects and push them to the lights vector
	Light* light_one = new Light(Light::LightType::SPOTLIGHT, 0);

	light_one->setPosition(Vector3(0.0f, 10.0f, 0.0f));
	light_one->setDiffuse(Vector3(1.0f, 1.0f, 1.0f));
	light_one->setDirection(Vector3(0.0f, -1.0f, 0.0f));
	light_one->setCutoff(30);
	light_one->setExponent(50);
	lights.push_back(light_one);

	Light* light_two = new Light(Light::LightType::POINT, 1);
	light_two->setPosition(Vector3(0.0f, 50.0f, 0.0f));
	light_two->setDiffuse(Vector3(0.6f, 0.6f, 0.5f));
	light_two->setAttenuation(0.0f);
	lights.push_back(light_two);

	Light* light_three = new Light(Light::LightType::POINT, 2);
	light_three->setPosition(Vector3(-27.0f, 18.5f, -29.0f));
	light_three->setDiffuse(Vector3(1.0f, 0.0f, 0.0f));
	light_three->setAttenuation(0.4f);
	lights.push_back(light_three);

	Light* light_four = new Light(Light::LightType::POINT, 3);
	light_four->setPosition(Vector3(-35.0f, 26.8f, 0.0f));
	light_four->setDiffuse(Vector3(1.0f, 0.0f, 0.0f));
	light_four->setAttenuation(0.3f);
	lights.push_back(light_four);

	Light* light_five = new Light(Light::LightType::SPOTLIGHT, 4);
	light_five->setPosition(Vector3(5.4f, 5.0f, 2.0f));
	light_five->setDiffuse(Vector3(1.0f, 0.0f, 1.0f));
	light_five->setDirection(Vector3(0.0f, -1.0f, 0.0f));
	light_five->setCutoff(50.0f);
	light_five->setExponent(50.0f);
	light_five->setAttenuation(0.4f);
	lights.push_back(light_five);


}

Lighting::~Lighting()
{

}

void Lighting::update(float dt)
{

}

void Lighting::handleInput(float dt, Input* input)
{

	//handles input for the interactable spotlight
	//
	// e - red
	// r - green
	// t - blue
	// default - purple
	//
	if (input->isKeyDown('e'))
	{
		lights[4]->setDiffuse(Vector3(1.0f, 0.0f, 0.0f));
	}
	else if (input->isKeyDown('r'))
	{
		lights[4]->setDiffuse(Vector3(0.0f, 1.0f, 0.0f));
	}
	else if (input->isKeyDown('t'))
	{
		lights[4]->setDiffuse(Vector3(0.0f, 0.0f, 1.0f));
	}
	else
	{
		lights[4]->setDiffuse(Vector3(1.0f, 0.0f, 1.0f));
	}

}

void Lighting::render()
{
	//renders all lights
	for (Light* light : lights)
	{
		light->render();
	}
}

void Lighting::enableLight(int id)
{
	lights[id]->enable();
}

void Lighting::disableLight(int id)
{
	lights[id]->disable();
}

GLfloat* Lighting::getPosition(int id)
{
	return lights[id]->getPosition();
}