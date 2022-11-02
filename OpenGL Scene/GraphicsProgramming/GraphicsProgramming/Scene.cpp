#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	glutSetCursor(GLUT_CURSOR_NONE);
	// Store pointer for input class
	input = in;
	initialiseOpenGL();
	
	// Other OpenGL / render setting should be applied here.
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//custom class definitions & initialisation
	textureLoader = new TextureLoader();
	lighting = new Lighting();
	skybox = new Skybox(textureLoader->useTexture("Skybox"));
	create = new Create();

	//camera definitions & initialisation
	camera1 = new FirstPersonCamera(in, 15, true);
	camera2 = new FirstPersonCamera(in, 15, false);
	camera1->setPosition(Vector3(8.0f, 1.5f, 6.0f));
	camera1->setRotation(Vector3(-70.0f, 20.0f, 0.0f));
	currentCamera = camera1;

	// Initialise scene variables
	rot = 0;
	rotdir = -1;
	wireframeMode = false;
}

void Scene::handleInput(float dt)
{
	// Handle user input

	currentCamera->handleInput(dt);


	//input for interactables
	//
	// c - change perspective to free cam with extra lighting
	// x - change perspective to fixed cam with decreased lighting
	// f - change rotation direction of the ender dragon
	// q - toggle wireframe mode

	if (input->isKeyDown('c'))
	{
		currentCamera = camera2;
		lighting->enableLight(1);
	}

	if (input->isKeyDown('x'))
	{
		currentCamera = camera1;
		lighting->disableLight(1);
	}

	if (input->isKeyDown('f') && rotdir != 1)
	{
		rotdir = 1;
		input->setKeyUp('f');
	}
	else if(input->isKeyDown('f') && rotdir != -1)
	{
		rotdir = -1;
		input->setKeyUp('f');
	}

	if (input->isKeyDown('q') && !wireframeMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		wireframeMode = true;
		input->setKeyUp('q');
	}
	else if (input->isKeyDown('q') && wireframeMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		wireframeMode = false;
		input->setKeyUp('q');
	}

	//deals with lighting input & interactability
	lighting->handleInput(dt, input);
	
}

void Scene::update(float dt)
{
	// update scene related variables.

	currentCamera->update(dt, width, height);
	lighting->update(dt);

	//changes position of the floating objects to appear to 'bob' up and down
	floating = 1 + sin(timet * 0.05) * 0.5;
	timet++;
	rot++;
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	
	

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	// Reset transformations
	glLoadIdentity();

	// Set the camera

	gluLookAt(currentCamera->getPosition().x, currentCamera->getPosition().y, currentCamera->getPosition().z, currentCamera->getLookat().x, currentCamera->getLookat().y, currentCamera->getLookat().z, currentCamera->getUp().x, currentCamera->getUp().y, currentCamera->getUp().z);


	//enabling & rendering lights
	lighting->enableLight(0);
	lighting->enableLight(2);
	lighting->enableLight(3);
	lighting->enableLight(4);

	lighting->render();


	// Render geometry/scene here -------------------------------------
	glDisable(GL_LIGHTING); //disable lighting so it doesn't affect the skybox

	//skybox creation
	glPushMatrix();
	glTranslatef(currentCamera->getPosition().x, currentCamera->getPosition().y, currentCamera->getPosition().z);
	glDisable(GL_DEPTH_TEST);
	skybox->render();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glEnable(GL_LIGHTING);


	//adds the mirror for reflection if in free cam mode
	if (currentCamera == camera1)
	{
		glPushMatrix();
		glTranslatef(0, 1.0f, -1.0f);
		create->Model("Knuckles");
		glPopMatrix();

	}
	else if (currentCamera == camera2)
	{
		Reflection();
	}

	//render on scene geometry
	renderGeometry();
	
	
	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::renderGeometry()
{
	//floor verts and shadow matrix used for projecting the shadow onto the ground.
	GLfloat floorVerts[] = {
	-1.f, -1.f, -1.f,  
	-1.f, -1.f, 1.f,  
	1.f, -1.f, 1.f,  
	1.f, -1.f, -1.f };
	float shadowMatrix[16];

	glEnable(GL_STENCIL_TEST);
	
	
	glScalef(1, 1, 1);
	glPushMatrix();
		glScalef(4, 4, 4);
		glTranslatef(1, 0.4, 0);
		glRotatef(-40, 0, 1, 0);
		create->Model("Steve");
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10, 1, 10);
		create->vertexArrayObject(textureLoader->useTexture("Crate")); //use of vertex array
	glPopMatrix();

	glPushMatrix();
		glTranslatef(6, 1, -3);
		create->fSphere(10, 10, 1, textureLoader->useTexture("Stars")); //use of procedral object
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, 1);
		endPortal();

		glPushMatrix();
			glTranslatef(5, 2, 1);
			glScalef(3, 3, 3);
			create->Model("Enderman"); // model loading
		glPopMatrix();
	glPopMatrix();
	
	//rendering obisidan towers around the map
	glPushMatrix();
		glTranslatef(25, 0, 25);
		renderObsidianTower(15);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-25, 0, -27);
		renderObsidianTower(18);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-25, 0, 25);
		renderObsidianTower(19);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25, 0, -22);
		renderObsidianTower(25);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, -35);
		renderObsidianTower(19);
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0, 0, 34);
		renderObsidianTower(23);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(34, 0, 0);
		renderObsidianTower(20);
	glPopMatrix();



	glPushMatrix();
		glTranslatef(-35, 0, 0);
		renderObsidianTower(27);
	glPopMatrix();






	//stencil function to ensure shadow is rendered ontop of the ground object
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glPushMatrix();
		create->hdCube(100, 1, 100, 1, textureLoader->useTexture("EndStone"), true); //procedural cube
	glPopMatrix();
	glStencilMask(0xFF);
	GLfloat pos[] = { 0.0f,50.0f,0.0f }; // main light position
	shadow.generateShadowMatrix(shadowMatrix, pos, floorVerts);

	//shadow rendering
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0f, 0.0f, 0.0f); // Shadow's colour
	glPushMatrix();
		glMultMatrixf((GLfloat*)shadowMatrix);

		glPushMatrix();
			
			glTranslatef(0, 20, 0);
			glRotatef(rot, 0, rotdir, 0);
			glTranslatef(15, 0, 0);
			glScalef(2, 2, 2);
			glEnable(GL_BLEND);
			create->Model("EndDragon"); //shadow object
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();

	//render regular object
	glColor3f(1.0f, 1.0f, 1.0f); 
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_STENCIL_TEST);
	
	glTranslatef(0, 20, 0);
	glPushMatrix();
		glRotatef(rot, 0, rotdir, 0);
		glTranslatef(15, 0, 0);
		glScalef(2, 2, 2);
		glEnable(GL_BLEND);
		create->Model("EndDragon");
		glDisable(GL_BLEND);
	glPopMatrix();
}

void Scene::Reflection()
{
	//Reflection using the stencil buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glTranslatef(-5, 0, 0);
		glPushMatrix();
		//create the mirror plane for the reflection to be visible through
			glBegin(GL_QUADS);
			glVertex3f(0.0f, 5.0f, 4.0f);
			glVertex3f(0.0f, -0.0f, 4.0f);
			glVertex3f(0.0f, -0.0f, -4.0f);
			glVertex3f(0.0f, 5.0f, -4.0f);
			glEnd();
		glPopMatrix();
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//create reflection of the object
	glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glPushMatrix();
			glTranslatef(10, 1.0f, -1.0f);
			create->Model("Knuckles");
		glPopMatrix();
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	//create mirror material for the reflection
		glColor4f(0.8f, 0.8f, 1.0f, 0.4f);
		glTranslatef(-5, 0, 0);
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 5.0f, 4.0f);
		glVertex3f(0.0f, -0.0f, 4.0f);
		glVertex3f(0.0f, -0.0f, -4.0f);
		glVertex3f(0.0f, 5.0f, -4.0f);
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0x00);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	//render the actual object
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0, 1.0f, -1.0f);
			glScalef(1.0, 1.0, 1.0);
			create->Model("Knuckles");
		glPopMatrix();
	glPopMatrix();
}
void Scene::endPortal()
{
	//creating the end portal using blocks
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0, 1, 0);
			create->hdCube(3, 1, 1, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(2, 0, 1);
			create->hdCube(1, 1, 1, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(1, 0, 2);
			create->hdCube(1, 1, 3, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(-1, 0, 2);
			create->hdCube(1, 1, 1, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(-2, 0, 1);
			create->hdCube(3, 1, 1, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(-2, 0, -1);
			create->hdCube(1, 1, 1, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(-1, 0, -2);
			create->hdCube(1, 1, 3, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(1, 0, -2);
			create->hdCube(1, 1, 1, 1, textureLoader->useTexture("Bedrock"), true);
			glTranslatef(2, 1, 2);
			create->hdCube(1, 3, 1, 1, textureLoader->useTexture("Bedrock"), true);
		glPopMatrix();

		//inside the portal
		glTranslatef(0, 0.5f, 3);
		create->Plane(5, 5, 1, textureLoader->useTexture("Stars"), false);
	glPopMatrix();
}
void Scene::renderObsidianTower(int height)
{
	//create an obsidian tower with a custom height
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0, height/2, 0);
			create->hdCube(4, height, 4, 1, textureLoader->useTexture("Obsidian"), true);
		glPopMatrix();
		glTranslatef(-1, height, -1);
		glScalef(0.5f, 0.5f, 0.5f);

		//base of the end crystal
		glPushMatrix();
			glTranslatef(0, -2, 0);
			create->Cube(1, 0.25, 1, 1, textureLoader->useTexture("Bedrock"));
		glPopMatrix();

		createFire();
		glEnable(GL_BLEND);
		//create animated end crystals that rotate
		glPushMatrix();
			glPushMatrix();
				glTranslatef(0, floating, 0);
				glRotatef(rot, 1, 0, 0);
				create->Cube(1, 1, 1, 1, textureLoader->useTexture("Glass"));
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, floating, 0);
				glRotatef(rot + 50, 0, 1, 0);
				create->Cube(1, 1, 1, 1, textureLoader->useTexture("Glass"));
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, floating, 0);
				glRotatef(rot + 30, 0, 0, 1);
				create->Cube(1, 1, 1, 1, textureLoader->useTexture("Glass"));
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();
	
}

void Scene::createFire()
{

	//create fire for the end crystals
	glEnable(GL_BLEND);
	glPushMatrix();


		glTranslatef(1, -1.75, 1);
		glScalef(2, 2, 2);
		glRotatef(90, 1, 0, 0);

		glPushMatrix();
			create->Plane(1, 1, -1, textureLoader->useTexture("Fire"), false); // -1 makes the normal face the opposite direction so fire appears "lit"
		glPopMatrix();

		glPushMatrix();
			glRotatef(90, 0, 0, 1);
			create->Plane(1, 1, 1, textureLoader->useTexture("Fire"), false);
			glTranslatef(0, 1, 0);
			create->Plane(1, 1, -1, textureLoader->useTexture("Fire"), false);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, -1, 0);
			create->Plane(1, 1, 1, textureLoader->useTexture("Fire"), false);
		glPopMatrix();

	glPopMatrix();
	

	glDisable(GL_BLEND);
}
void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.3f,0.5f,0.9f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 300.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
