#pragma once

#include "Application.h"
#include "Renderer2D.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void bullet();
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Texture*		m_rock;
	aie::Texture*		m_bullet;
	aie::Font*			m_font;

	float m_shipX, m_shipY;
	float m_bulletX, m_bulletY;
	float m_cameraX, m_cameraY;
	float m_timer;
};
