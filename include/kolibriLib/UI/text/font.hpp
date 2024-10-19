#ifndef __FONT_HPP__
#define __FONT_HPP__

#include <string>

#include "freetype.hpp"

namespace KolibriLib
{
	namespace UI
	{
		namespace text
		{
			struct Font
			{
				FreeType::Face _face;
			};

			void DrawText(Coord coord, const std::string &text, Font font);
		} // namespace text
		
	} // namespace UI
	
}

#endif // __FONT_HPP__