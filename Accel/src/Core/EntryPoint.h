#pragma once

#ifdef AC_PLATFORM_WINDOWS

	extern accel::Ref<accel::Framework> accel::CreateFramework();

	int main()
	{
		auto App = accel::CreateFramework();

		App->Run();
	}

#endif // AC_PLATFORM_WINDOWS
