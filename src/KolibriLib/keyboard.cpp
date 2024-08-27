#include <kolibriLib/input/keyboard.hpp>
#include <algorithm>

using namespace KolibriLib;
using namespace keyboard;

Scancode keyboard::GetScancodeByASCII(char ascii, KeyboardLayoutMode mode)
{
	KeyboardLayout layout = GetKeyboardLayout(mode);

	for(uint8_t i = 0; i < sizeof(KeyboardLayout); i++)
	{
		if(layout[i] == ascii)
		{
			return i;
		}
	}

	return Scancode::ANY;
}

Scancode keyboard::GetScancodeByASCII(char ascii)
{
	uint8_t a = GetScancodeByASCII(ascii, KeyboardLayoutModes::Normal);

	if(a == Scancode::ANY)
	{
		a = GetScancodeByASCII(ascii, KeyboardLayoutModes::Shift);

		if(a == Scancode::ANY) // Вероятность того что до этого дойдёт довольно низка
		{
			a = GetScancodeByASCII(ascii, KeyboardLayoutModes::Alt);
		}
	}

	return a;
}

Scancode::Scancode(char c)
{
	
	val = GetScancodeByASCII(c);
}

Scancode::operator char() const
{
	return GetKeyboardLayout()[val];
}

Scancode::operator uint8_t() const
{
	return val;
}

char & KeyboardLayout::operator[](uint8_t i)
{
	return table[i];
}

char KeyboardLayout::operator[](uint8_t i) const
{
	return table[i];
}

Input::operator char() const
{
	if(GetInputMode() == InputModes::ASCII)
	{
		return this->ASCII;
	}
	else
	{
		return (char)scancode;
	}
}

Input::operator Scancode() const
{
	if(GetInputMode() == InputModes::ASCII)
	{
		return GetScancodeByASCII(ASCII);
	}
	else
	{
		return scancode;
	}
}

void KolibriLib::PrintDebug(Scancode out)
{
	PrintDebug((unsigned)((char)out));
}

void KolibriLib::PrintDebug(Input out)
{
	if(GetInputMode() == InputModes::ASCII)
	{
		PrintDebug(out.ASCII);
	}
	else
	{
		PrintDebug(out.scancode);
	}
}
