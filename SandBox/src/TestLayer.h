#pragma once

#include "SFML/Graphics.hpp"
#include <Accel.h>

struct Point : public sf::Drawable
{
	Point(float radius = 1.0f)
		:m_P(radius)
	{
		m_P.setOutlineThickness(radius * 0.8f);
		m_P.setOrigin(radius, radius);
		m_NormalColor = sf::Color::White;
		m_HightlightColor = sf::Color::Red;
	}

	void SetColor(sf::Color color) { m_P.setFillColor(m_NormalColor = color); }
	void SetSelectColor(sf::Color color) { m_P.setOutlineColor(m_HightlightColor = color); }

	void Hightlight(bool isHightlight) { m_P.setOutlineColor(isHightlight ? m_HightlightColor : m_NormalColor); }

	void SetPosition(sf::Vector2f pos) { m_P.setPosition(pos); }
	sf::Vector2f GetPosition()const { return m_P.getPosition(); }

private:
	sf::CircleShape m_P;

	sf::Color m_NormalColor;
	sf::Color m_HightlightColor;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(m_P);
	}
};

struct PointDis
{
	Point* p;
	float dis;
	PointDis(Point* point, float distance) :p(point), dis(distance) {}
};

class TestLayer : public accel::Layer
{
public:
	TestLayer()
	{
		m_Player = Point(5.0f);
		m_Player.SetPosition({ 100.0f, 100.0f });
		m_Player.SetColor(sf::Color::Green);

		m_Enemies.reserve(32);
	}

	~TestLayer() {}

	virtual void OnAttach() {}

	virtual void OnDetch() {}

	virtual void OnUpdate()
	{
		auto& window = accel::Framework::GetInstance()->GetWindow();
		// move player
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_Player.Hightlight(true);
			m_Player.SetPosition((sf::Vector2f)sf::Mouse::getPosition(window));
		}
		else
		{
			m_Player.Hightlight(false);
		}

		
		std::vector<PointDis> pdis;
		pdis.reserve(m_Enemies.size());
		
		for (auto& enmy : m_Enemies)
		{
			pdis.emplace_back(&enmy, DistanceSq(enmy.GetPosition(), m_Player.GetPosition()));
		}

		std::sort(pdis.begin(), pdis.end(), [](const PointDis& a, const PointDis& b)->bool
			{
				return a.dis < b.dis;
			});

		for (size_t i = 0; i < pdis.size(); i++)
		{
			pdis[i].p->Hightlight(i < 10);
		}

		// draw enemies
		for (auto& enmy : m_Enemies)
		{
			window.draw(enmy);
		}

		// draw player
		window.draw(m_Player);
	}

	virtual void OnEvent(sf::Event& e)
	{
		if (e.type == sf::Event::EventType::MouseButtonPressed)
		{
			// add enemy
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				Point newEnmy = Point(3.0f);
				newEnmy.SetPosition((sf::Vector2f)sf::Mouse::getPosition(accel::Framework::GetInstance()->GetWindow()));
				if (m_Enemies.size() < maxEnemyCount)
				{
					m_Enemies.emplace_back(newEnmy);
					std::cout << "Enemies count: " << m_Enemies.size() << "\n";
				}
			}
		}
		if (e.type == sf::Event::EventType::KeyPressed)
		{
			//  Undo
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace))
			{
				if (!m_Enemies.empty())
				{
					std::cout << "Undo.\n";
					m_Enemies.pop_back();
				}
			}
		}
	}

private:
	float DistanceSq(sf::Vector2f const& a, sf::Vector2f const& b)
	{
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	}

	Point m_Player;

	std::vector<Point> m_Enemies;

	const int maxEnemyCount = 100;
};
