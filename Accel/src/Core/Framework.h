#pragma once
#include "LayerStack.h"

#include <SFML/Graphics.hpp>

namespace accel
{
	class AC_API Framework
	{
	public:
		Framework();
		virtual ~Framework();

		void Run();

		void OnEvent(sf::Event& ev);

		void PushLayer(Ref<Layer> layer);

		void PushOverLayer(Ref<Layer> overLay);

		inline void Close() { m_Window->close(); }

		inline sf::Vector2u GetSize() { return m_Window->getSize(); }

	private:
		Ref<sf::RenderWindow>m_Window;

		std::vector<Ref<sf::Drawable>> m_Drawables;

		LayerStack m_LayerStack;
		
	};

	Ref<Framework> CreateFramework();

}

