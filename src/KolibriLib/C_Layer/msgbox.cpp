#include <C_Layer/msgbox.hpp>
#include <kolibriLib/debug.hpp>

#include <cstring>
#include <cstdlib>

msgBoxLib _msgBoxLib;

msgBoxLib::msgBoxLib()
{
	KolibriLib::logger << microlog::LogLevel::Debug << "Init msgbox lib: ";
	kolibri_msgbox_init();
	KolibriLib::logger << "OK" << std::endl;
}

msgBox::msgBox(const std::string &title, const std::string& text, const std::vector<std::string> &ButtonsTexts)
{
	_struct = new msgbox;
	_struct->retval = static_cast<std::uint8_t>(ButtonsTexts.size());

	char *pc = _struct->texts;

	std::strcpy(pc, title.c_str());
	pc += strlen(title.c_str()) + 1;

	std::strcpy(pc, text.c_str());
	pc += text.length() + 1;

	for (std::uint8_t i = 0; i < static_cast<std::uint8_t>(ButtonsTexts.size()); i++)
	{
		std::strcpy(pc, ButtonsTexts[i].c_str());
		pc += ButtonsTexts[i].length() + 1;
	}
}

msgBox::~msgBox()
{
	delete _struct;
	if (_funcs != nullptr)
		std::free(_funcs);
}

void msgBox::msg(const std::vector<msgBox::Callback> &funcs)
{
	if(_funcs != nullptr)
		std::free(_funcs);
	_funcs = static_cast<msgBox::Callback*>(std::malloc(funcs.size() + 1));	

	_funcs[funcs.size()] = 0;

	for (std::size_t i = 0; i < funcs.size(); i++)
	{
		_funcs[i] = funcs.at(i);
	}

	msgbox_create(_struct, &_struct->top_stack);
	msgbox_setfunctions(_funcs);
}

void msgBox::reinit()
{
	msgbox_reinit(_struct);
}