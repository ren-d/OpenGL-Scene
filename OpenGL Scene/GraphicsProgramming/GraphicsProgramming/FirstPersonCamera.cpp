#include "FirstPersonCamera.h"


FirstPersonCamera::FirstPersonCamera(Input* in, float fspeed, bool isStatic)
{
	//variable initialisation and definitions
	input = in;
	position = Vector3(0, 0, 6);
	rotation = Vector3(0, 0, 0);
	lookat = Vector3(0, 0, 0);
	up = Vector3(0, 1, 0);
	m_speed = fspeed;
	m_isStatic = isStatic;
}


FirstPersonCamera::~FirstPersonCamera()
{

}

void FirstPersonCamera::update(float dt, int width, int height)
{
	//sets mouse to middle of the screen
	glutWarpPointer(width / 2, height / 2);
	mouseDistanceMoved = Vector3(input->getMouseX(), input->getMouseY(), 0); //gets how far the mouse moved this frame
	screenSize = Vector3(width / 2, height / 2, 0); //finds middle of the screen
	//math
	float cosR, cosP, cosY;
	float sinR, sinP, sinY;
	cosY = cosf(rotation.x * 3.1415 / 180);
	cosP = cosf(rotation.y * 3.1415 / 180);
	cosR = cosf(rotation.z * 3.1415 / 180);
	sinY = sinf(rotation.x * 3.1415 / 180);
	sinP = sinf(rotation.y * 3.1415 / 180);
	sinR = sinf(rotation.z * 3.1415 / 180);

	//gets forward vector
	forward.x = sinY * cosP * m_speed * dt;
	forward.y = sinP * m_speed * dt;
	forward.z = cosP * -cosY * m_speed * dt;
	//gets up vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	//gets right vector
	right = forward.cross(up);

	lookat = position + forward;
}

void FirstPersonCamera::handleInput(float dt)
{
	//use controllable movement if the camera type isn't static
	switch (m_isStatic)
	{
	case true:
		break;
	case false:
		//user wasd input
		if (input->isKeyDown('w'))
		{
			position.add(forward);
		}

		if (input->isKeyDown('s'))
		{
			position.subtract(forward);
		}

		if (input->isKeyDown('a'))
		{
			position.subtract(right);
		}

		if (input->isKeyDown('d'))
		{
			position.add(right);

		}

		//rotates camera via mouse controls
		rotation.setX(rotation.x + (mouseDistanceMoved.x - screenSize.x) * 2 * dt);
		rotation.setY(rotation.y - (mouseDistanceMoved.y - screenSize.y) * 2 * dt);
		break;
	}
	
}

Vector3 FirstPersonCamera::getPosition()
{
	return position;
}

Vector3 FirstPersonCamera::getRotation()
{
	return rotation;
}

Vector3 FirstPersonCamera::getLookat()
{
	return lookat;
}

Vector3 FirstPersonCamera::getUp()
{
	return up;
}

void FirstPersonCamera::setPosition(Vector3 pos)
{
	position = pos;
}

void FirstPersonCamera::setRotation(Vector3 rot)
{
	rotation = rot;
}

