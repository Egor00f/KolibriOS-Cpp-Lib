#include <kolibriLib/UI/text/freetypefuncs.hpp>

using namespace KolibriLib;

void DrawGlyphSlot(const FT_GlyphSlot &slot, const KolibriLib::Coord &coord)
{
	int bpp = 1;
	switch (slot->bitmap.pixel_mode)
	{
	case FT_PIXEL_MODE_BGRA:
		bpp = 32;
		break;
	case FT_PIXEL_MODE_LCD:
		bpp = 24;
		break;
	case FT_PIXEL_MODE_LCD_V:
		bpp = 24;
		break;
	default:
		throw "KolibriLib::DrawGlyph(): glyph BPP nor support\n";
	}

	ksys_draw_bitmap_palette(&slot->bitmap.buffer,
							 coord.x + slot->bitmap_left,
							 coord.y + slot->bitmap_top,
							 slot->bitmap.width,
							 slot->bitmap.rows,
							 bpp,
							 &slot->bitmap.palette,
							 0);
}