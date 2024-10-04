#ifndef __PROGRESS_BAR_HPP__
#define __PROGRESS_BAR_HPP__

#include <kolibriLib/UI/UI.hpp>

namespace KolibriLib
{
	namespace UI
	{
		/// @brief Полоска загрузки
		/// @details Рабоает так: заполнен на p2.x * _Fill / _MaxFill
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

			/**
			 * @brief 
			 * @param NewFill 
			 */
			void SetFill(unsigned NewFill);

			/**
			 * @brief получить то на сколько заполнен
			 * @return 
			 */
			unsigned GetFill() const;

			/**
			 * @brief Добавить заполненость
			 * @param val 
			 */
			void AddFill(unsigned val);

			/**
			 * @brief Получить максимальную
			 * @return 
			 */
			unsigned GetMaxFill() const;

			ProgressBar& operator=(const ProgressBar&) = default;

			/**
			 * @brief 
			 * @param val то с чем сравнивать
			 * @return 
			 */
			bool operator==(const ProgressBar& val) const;

			/**
			 * @brief 
			 * @param val то с чем сравнивать
			 * @return 
			 */
			bool operator != (const ProgressBar& val) const;

		private:

			/**
			 * @brief Цвет рамки
			 */
			Colors::Color _BorderColor;

			/**
			 * @brief 
			 */
			unsigned _MaxFill;

			/**
			 * @brief 
			 */
			unsigned _Fill;
		};
		/** @example ProgressBar.cpp
         * пример использования ProgressBar
         */

	} // namespace UI
	
} // namespace KolibriLib

#endif // __PROGRESS_BAR_HPP__