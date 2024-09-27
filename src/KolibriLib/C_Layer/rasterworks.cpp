#include <C_Layer/rasterworks.hpp>

rasterwoksLib rasterworksLibv;

rasterwoksLib::rasterwoksLib()
{
	KolibriLib::PrintDebug("Init RasterWorks: ");
	int err = kolibri_rasterworks_init();

	if (err == -1)
	{
		KolibriLib::PrintDebug("Error\n");

		throw err;
	}
	else
	{
		KolibriLib::PrintDebug("OK\n");
	}
}

void drawtext(const KolibriLib::Coord &coord, const KolibriLib::Size &size, const std::string &text, const KolibriLib::Size &CharSize, const KolibriLib::Colors::Color &FontColor, const KolibriLib::Colors::Color &BackgroundColor, const uint8_t &flags, const uint8_t encoding)
{
	const int l = size.x * size.y;
	rgb_t *canvas = new rgb_t[l];

	for (int i = 0; i < l; i++)
	{
		canvas[i] = BackgroundColor.GetRGB();
	}

	void *buff = drawTextToBuff(canvas, {0, 0}, size, text, CharSize, FontColor, flags, encoding);

	delete canvas;

	_ksys_draw_bitmap(buff, coord.x, coord.y, size.x, size.y);

	free(buff);
}