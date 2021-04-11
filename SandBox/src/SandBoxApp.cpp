#include "acpch.h"

#ifndef CLIENT_ENTRY
#define CLIENT_ENTRY
#endif

#include <Accel.h>

#include "TestLayer.h"
#include "SFML/Graphics.hpp"

class SandBox : public accel::Framework
{
public:
	SandBox()
	{
		this->PushOverLayer(std::make_shared<TestLayer>());
	}
	~SandBox()
	{

	}
};

accel::Ref<accel::Framework> accel::CreateFramework()
{
	return std::make_shared<SandBox>();
}
