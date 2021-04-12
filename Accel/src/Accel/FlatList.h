#pragma once

#include "IObjContainer.h"

namespace accel
{

	template<typename Object>
	class AC_API FlatList : public IObjContainer<Object>
	{
	public:
		FlatList();
		~FlatList()override;

		virtual void Create(std::vector<Object>& org) override;

		virtual std::vector<Object*> FindK_Get(size_t k, Comper comp) override;

		virtual void FindK_Set(size_t k, Comper comp, Action action) override;

		/*virtual std::vector<Object*> FindRange_Get(float range, Comper comp) override;

		virtual void FindRange_Set(float range, Comper comp, Action action) override;*/

		virtual std::vector<Object*> FindIf_Get(Condition condition, Comper comp) override;

		virtual void FindIf_Set(Condition condition, Comper comp, Action action) override;

	private:
		std::vector<Object*> m_Objs;

	};

	template<typename Object>
	inline FlatList<Object>::FlatList()
	{
	}

	template<typename Object>
	inline FlatList<Object>::~FlatList()
	{
	}

	template<typename Object>
	inline void FlatList<Object>::Create(std::vector<Object>& org)
	{
		m_Objs.clear();
		m_Objs.reserve(org.size());
		for (Object& it : org)
		{
			m_Objs.emplace_back(&it);
		}
	}

	template<typename Object>
	inline std::vector<Object*> FlatList<Object>::FindK_Get(size_t k, Comper comp)
	{
		if (k <= 0 || k > m_Objs.size())return std::vector<Object*>();
		std::sort(m_Objs.begin(), m_Objs.end(), comp);
		std::vector<Object*> reObj(m_Objs.begin(), m_Objs.begin() + k - 1);
		return reObj;
	}

	template<typename Object>
	inline void FlatList<Object>::FindK_Set(size_t k, Comper comp, Action action)
	{
		if (k <= 0)return;
		std::sort(m_Objs.begin(), m_Objs.end(), comp);

		for (size_t i = 0; i < m_Objs.size(); i++)
		{
			action(i < k, m_Objs[i]);
		}
	}

	template<typename Object>
	inline std::vector<Object*> FlatList<Object>::FindIf_Get(Condition condition, Comper comp)
	{
		std::sort(m_Objs.begin(), m_Objs.end(), comp);
		
		std::vector<Object*> reObj;
		for (auto& obj : m_Objs)
		{
			if (condition(obj))reObj.push_back(obj);
		}

		return reObj;
	}

	template<typename Object>
	inline void FlatList<Object>::FindIf_Set(Condition condition, Comper comp, Action action)
	{
		std::sort(m_Objs.begin(), m_Objs.end(), comp);
		for (auto& obj : m_Objs)
		{
			action(condition(obj), obj);
		}
	}

}

