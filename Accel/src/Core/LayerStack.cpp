#include "acpch.h"
#include "LayerStack.h"

namespace accel
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
	}

	void LayerStack::PushLayer(Ref<Layer> layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerStackIndex, layer);
	}

	void LayerStack::PushOverLay(Ref<Layer> overLay)
	{
		m_Layers.emplace_back(overLay);
	}

	void LayerStack::PopLayer(Ref<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerStackIndex--;
		}
	}

	void LayerStack::PopOverLay(Ref<Layer> overLay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overLay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}
