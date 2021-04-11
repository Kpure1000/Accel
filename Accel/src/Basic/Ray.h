#pragma once

#include <Core/Core.h>

#include <SFML/System/Vector2.hpp>

namespace accel
{

	template class AC_API sf::Vector2<float>;

	class AC_API Ray
	{
	public:

		Ray(sf::Vector2f origin = { 0.0f,0.0f }, sf::Vector2f dircetion = { 0.0f,0.0f })
			: origin(origin), direction(dircetion)
		{}

		sf::Vector2f origin;
		sf::Vector2f direction;
	};

}