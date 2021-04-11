#include "acpch.h"
#include "Framework.h"

#ifndef CannotResize
#define CannotResize  (sf::Style::Titlebar |  sf::Style::Close)
#endif // !CannotResize

#ifndef KeyPressing
#define KeyPressing sf::Event::KeyPressed
#endif // !KeyPressing

#ifndef KeyReleasing
#define KeyReleasing sf::Event::KeyReleased
#endif // !KeyReleasing

#ifndef KeyEvent
#define KeyEvent(EV) (sf::Keyboard::isKeyPressed(EV))
#endif // !KeyEvent


namespace accel
{

	Framework* Framework::m_Instance = nullptr;

	Framework::Framework()
	{
		m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600),
			"Accel Framework", sf::Style::Close | sf::Style::Titlebar);

		m_Instance = this;
		m_Window->setFramerateLimit(60);
	}

	Framework::~Framework()
	{
	}

	void Framework::Run()
	{
		while (m_Window->isOpen())
		{
			sf::Event ev;
			while (m_Window->pollEvent(ev))
			{
				this->OnEvent(ev);
			}

			m_Window->clear(sf::Color(158, 158, 158, 255));

			for (auto& layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->display();

		}
	}

	void Framework::OnEvent(sf::Event& ev)
	{

		for (auto& layer : m_LayerStack)
		{
			layer->OnEvent(ev);
		}

		if (ev.type == sf::Event::Closed || (KeyPressing && KeyEvent(sf::Keyboard::Key::Escape)))
		{
			this->Close();
			m_Window->close();
		}
	}

	void Framework::PushLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Framework::PushOverLayer(Ref<Layer> overLay)
	{
		m_LayerStack.PushOverLay(overLay);
		overLay->OnAttach();
	}

}