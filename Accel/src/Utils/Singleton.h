#pragma once
#include <Core/Core.h>
#include <memory>
namespace accel
{
	template<typename T>
	class AC_API Singleton {
	public:
		static T* GetInstance();

	private:
		Singleton() = delete;
		static std::unique_ptr<T> m_instance_;
	};


}