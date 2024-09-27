#ifndef __PROGRESS_BAR_HPP__
#define __PROGRESS_BAR_HPP__

#include <kolibriLib/UI/UI.hpp>

namespace KolibriLib
{
	namespace UI
	{
		/// @brief Полоска загрузки
		class ProgressBar : public UIElement
		{
		public:

			/// @brief Конструктор
			/// @param coord 
			/// @param size 
			/// @param color 
			/// @param MaxFill Максимальныое кол-во поинтов
			/// @param DefaultFill кол-во поинтов по умолчанию
			ProgressBar(const UDim &coord, const UDim &size, const Colors::Color &BorderColor = Globals::SystemColors.work_text, const Colors::Color& MainColor = Globals::SystemColors.work_graph, const unsigned &MaxFill = 100, const unsigned &DefaultFill = 0);

			/// @brief Отрисовать
			void Render() const override;

			void SetFill(unsigned NewFill);

		private:
			Colors::Color _BorderColor;
			unsigned _MaxFill;
			unsigned _Fill;
		};
	} // namespace UI
	
} // namespace KolibriLib

#endif // __PROGRESS_BAR_HPP__