#ifndef __WINDOWATTACHED_H__
#define __WINDOWATTACHED_H__

#include <kolibriLib/window/window.hpp>
#include <kolibriLib/system/thread.hpp>

namespace KolibriLib
{
	namespace window
	{
		/// @brief Окно что запускается в отдельном потоке
		class WindowAttached: public Window
		{
			public:
				WindowAttached(const Window &window);
				/// @brief 
				void Attach();
			private:

		};

		WindowAttached::WindowAttached(const Window &window): Window(window)
		{
			Attach();
		}

		void KolibriLib::window::WindowAttached::Attach()
		{
			
		}
	} // namespace window
	
} // namespace KolibriLib




#endif // __WINDOWATTACHED_H__