#ifndef __IMAGEBUTTON_H__
#define __IMAGEBUTTON_H__

#include "button.hpp"
#include <kolibriLib/UI/image.hpp>
#include "baseButton.hpp"

namespace KolibriLib
{
	namespace UI
	{
		namespace buttons
		{
			class ImageButton: public Images::Image, public BaseButton
			{
			public:

				/// @brief Отрисовать изображение
				void Render() const override;

			private:
			
			};
		}
	}
}

#endif // __IMAGEBUTTON_H__