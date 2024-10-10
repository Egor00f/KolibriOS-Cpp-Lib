#include <C_Layer/buf2d.hpp>
#include <kolibriLib/debug.hpp>

buf2dLib buf2dLibv;

buf2dLib::buf2dLib()
{
	KolibriLib::PrintDebug("Init buf2d: ");

	int err = kolibri_buf2d_init();

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

buf2d::buffer::buffer()
{
	Create(this, {32, 32}, 0xFFFFFF, BPP::RGB);
}

buf2d::buffer::buffer(BPP bpp)
{
	Create(this, {32, 32}, 0xFFFFFF, bpp);
}

buf2d::buffer::buffer(const KolibriLib::Size& size, BPP bpp)
{
	Create(this, size, 0xFFFFFF, bpp);
}

buf2d::buffer::buffer(const KolibriLib::Size& size, KolibriLib::Colors::rgb color)
{
	Create(this, size, color, BPP::RGB);
}

buf2d::buffer::buffer(const KolibriLib::Size& size, KolibriLib::Colors::Color color)
{
	Create(this, size, color, BPP::RGBA);
}

buf2d::buffer::buffer(const buf2d_struct* buff)
{
	buf2d_copy(buff, this);
}

buf2d::buffer::~buffer()
{
	Delete(this);
}
