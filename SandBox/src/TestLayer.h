#pragma once

#include "SFML/Graphics.hpp"
#include <Accel.h>

class TestLayer : public accel::Layer
{
public:
	TestLayer() 
	{
		m_Circle = sf::CircleShape(30.0f);
		m_Circle.setPosition(100.0f, 100.0f);
		m_Circle.setOrigin(30.0f, 30.0f);
	}

	~TestLayer() {}

	virtual void OnAttach() {}

	virtual void OnDetch() {}
	
	virtual void OnUpdate(accel::Ref<sf::RenderWindow> window)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_Circle.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
		}

		window->draw(m_Circle);
	}
	
	virtual void OnEvent(sf::Event& e) 
	{
		
	}

private:
	sf::CircleShape m_Circle;
};
