#ifndef __BAR_H__
#define __BAR_H__

#include <kolibriLib/UI/UI.hpp>

namespace KolibriLib
{
	namespace UI
	{
		/// @brief Полоска загрузки
		class Bar : public UIElement
		{
		public:

			/// @brief Конструктор
			/// @param coord 
			/// @param size 
			/// @param color 
			/// @param MaxFill Максимальныое кол-во поинтов
			/// @param DefaultFill кол-во поинтов по умолчанию
			Bar(const UDim &coord, const UDim &size, const Colors::Color &color = Globals::SystemColors.work_graph, const unsigned &MaxFill = 100, const unsigned &DefaultFill = 0);

			void Render() const;

		private:
			unsigned _MaxFill;
			unsigned _Fill;
		};
	} // namespace UI
	
} // namespace KolibriLib


#endif // __BAR_H__