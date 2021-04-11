#pragma once
#include "LayerStack.h"

#include <SFML/Graphics.hpp>

namespace accel
{
	class AC_API Framework
	{
	public:
		inline static Framework* GetInstance() { return m_Instance; }

		void Run();

		void OnEvent(sf::Event& ev);

		void PushLayer(Ref<Layer> layer);

		void PushOverLayer(Ref<Layer> overLay);

		inline void Close() { m_Window->close(); }

		inline sf::Vector2u GetSize() { return m_Window->getSize(); }

		inline sf::RenderWindow& GetWindow() { return *m_Window; }

	protected:
		Framework();
		virtual ~Framework();

	private:
		Ref<sf::RenderWindow>m_Window;

		std::vector<Ref<sf::Drawable>> m_Drawables;

		LayerStack m_LayerStack;
		
		static Framework* m_Instance;
	};

	Ref<Framework> CreateFramework();

}

