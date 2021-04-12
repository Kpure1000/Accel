#pragma once

#include <Core/Core.h>

namespace accel
{

	template <typename Object>
	class AC_API IObjContainer
	{
	public:
		using Comper = typename std::function<bool(const Object* a, const Object* b)>;
		using Action = typename std::function<void(bool isInK, Object* obj)>;
		using Condition = typename std::function<bool(Object* obj)>;

	public:
		virtual ~IObjContainer() {}

		virtual void Create(std::vector<Object>& org) = 0;

		virtual std::vector<Object*> FindK_Get(size_t k, Comper comp) = 0;

		virtual void FindK_Set(size_t k, Comper comp,
			std::function<void(bool isInK, Object* obj)>action) = 0;

		/*virtual std::vector<Object*> FindRange_Get(float range, Comper comp) = 0;

		virtual void FindRange_Set(float range, Comper comp, Action action) = 0;*/

		virtual std::vector<Object*> FindIf_Get(Condition condition, Comper comp) = 0;

		virtual void FindIf_Set(Condition condition, Comper comp, Action action) = 0;

	};

}