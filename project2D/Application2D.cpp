#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <time.h>

float moveY = 0;
float moveX = 0;
float rotate = 0;
float bulletX;
float bulletY;
float k = 400;
float l = 400;
int score = 0;


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_shipTexture = new aie::Texture("./textures/ship.png");
	m_rock = new aie::Texture("./textures/rock_large.png");
	m_bullet = new aie::Texture("./textures/bullet.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_shipX = 600;
	m_shipY = 400;
	m_bulletX = 10000;
	m_bulletY = 10000;
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}


void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_cameraX = m_shipX - 600;
	m_cameraY = m_shipY - 400;

	moveY = 0;
	moveX = 0;
	srand (time(nullptr));
	int respawn = rand() % 600 + 1;
	int respawn2 = rand() % 600 + 1;

	// use arrow keys to move the ship
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		moveY += 500.0f;
		rotate = 0;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		moveY  -= 500.0f;
		rotate = 3.14;
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		moveX  -= 500.0f;
		rotate = 1.57;
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		moveX += 500.0f;
		rotate = 4.7;
	}
	if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		rotate = 0.7;
	}
	if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		rotate = 5.3;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN) && input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		rotate = 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN) && input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		rotate = 2.2;
	}
	
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))	//shoot
	{
		bullet();
	}

	if ((m_bulletX < k+30 && m_bulletX > k-30) && (m_bulletY < l+30 && m_bulletY > l-30)) //check hit
	{
		k = respawn;
		l = respawn2;
		m_bulletX = -900;
		m_bulletY = -900;
		score++;
	}

	m_shipX += (moveX * deltaTime);
	m_shipY += (moveY * deltaTime);
	m_bulletX += (bulletX * deltaTime);
	m_bulletY += (bulletY * deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::bullet()
{
	//set position of bullet to ship
	m_bulletX = m_shipX;
	m_bulletY = m_shipY;

	//fire bullet in direction ship is facing
	if (rotate == 0)//up 
	{
		bulletY = 0;
		bulletX = 0;
		bulletY += 2000.0f;
	}
	else if (rotate >3.1 && rotate <3.2)//down
	{
		bulletY = 0;
		bulletX = 0;
		bulletY -= 2000.0f;
	}
	else if (rotate >1.5 && rotate <1.6)//left
	{
		bulletY = 0;
		bulletX = 0;
		bulletX -= 2000.0f;
	}
	else if (rotate <4.4 && rotate >4.9)//right
	{
		bulletY = 0;
		bulletX = 0;
		bulletX += 2000.0f;
	}
	else if (rotate <0.8 && rotate >0.6)
	{
		bulletY += 2000.0f;
		bulletX += 2000.0f;
	}
}

void Application2D::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// ship sprite
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_shipTexture, m_shipX, m_shipY, 0, 0, 0 + rotate, 1);

	// rock
	m_2dRenderer->drawSprite(m_rock, k, l, 50, 50, 0, 1);

	// create bullet
	m_2dRenderer->setRenderColour(2, 0, 0.5, 1);
	m_2dRenderer->drawCircle(m_bulletX, m_bulletY, 10, 10);

	// score
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	char points[32];
	sprintf_s(points, 32, "score: %i", score);
	m_2dRenderer->drawText(m_font, points, m_shipX -550, m_shipY + 280);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, m_shipX -550, m_shipY + 240);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", m_shipX -550, m_shipY + 200);

	// done drawing sprites
	m_2dRenderer->end();
}


