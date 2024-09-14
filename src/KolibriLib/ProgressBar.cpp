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
	const Size p2 = GetAbsoluteSize() + absCoord;

	graphic::DrawRectangleLines(absCoord, p2, _BorderColor);

	graphic::DrawRectangleFill(absCoord, {static_cast<int>(p2.x * _Fill / _MaxFill), p2.y}, _MainColor);
}

void KolibriLib::UI::ProgressBar::SetFill(unsigned NewFill)
{
	_Fill = NewFill;
}