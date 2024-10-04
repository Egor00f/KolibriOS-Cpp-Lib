#include <kolibriLib/UI/ProgressBar.hpp>
#include <kolibriLib/graphic/graphic.hpp>

using namespace KolibriLib;
using namespace UI;

KolibriLib::UI::ProgressBar::ProgressBar(const UDim &coord, const UDim &size, const Colors::Color &BorderColor, const Colors::Color &MainColor, const unsigned &MaxFill, const unsigned &DefaultFill)
	: UIElement(coord, size, MainColor, DefaultMargin),
	  _MaxFill(MaxFill),
	  _Fill(DefaultFill)
{
}

void KolibriLib::UI::ProgressBar::Render() const
{
	const Coord absCoord = GetAbsoluteCoord();
	const Size absSize = GetAbsoluteSize() + absCoord;

	graphic::DrawRectangleLines(absCoord, absSize, _BorderColor);

	graphic::DrawRectangleFill(absCoord, {static_cast<int>(absSize.x * _Fill / _MaxFill), absSize.y}, _MainColor);
}

void KolibriLib::UI::ProgressBar::SetFill(unsigned NewFill)
{
	_Fill = NewFill;
}

unsigned KolibriLib::UI::ProgressBar::GetFill() const
{
	return _Fill;
}

void KolibriLib::UI::ProgressBar::AddFill(unsigned val)
{
	_Fill += val;

	if(_Fill > _MaxFill)
		_Fill = _MaxFill;
}
