#include "acpch.h"

#include <Accel.h>
#include "SFML/Graphics.hpp"
using namespace accel;
using namespace std;

int main()
{
	Ray aRay(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(1.0f, -1.0f));
	cout << "dir: " << (aRay.direction - aRay.origin).y << endl;

}
