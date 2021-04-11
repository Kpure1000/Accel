#pragma once

#include <Core/Core.h>
#include <SFML/Graphics.hpp>

namespace accel
{

	class AC_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetch() {}
		virtual void OnUpdate(Ref<sf::RenderWindow> window) {}
		virtual void OnEvent(sf::Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}
