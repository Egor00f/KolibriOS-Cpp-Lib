#ifndef __SCROLLFRAME_HPP__
#define __SCROLLFRAME_HPP__

#include <kolibriLib/UI/UI.hpp>

namespace KolibriLib
{
	namespace UI
	{
		/**
		 * @brief 
		 * @warning Не завершенно
		 */
		class ScrollFrame : public UIElement
		{
		public:
			/**
			 * @brief Режим
			 */
			enum class ScrollMode
			{
				/**
				 * @brief Можно по обоим осям скролить
				 */
				All,

				/**
				 * @brief только по оси X (вправо-влево)
				 */
				OnlyX,

				/**
				 * @brief только по оси Y
				 */
				OnlyY
			};

			void Render() const override;

			ScrollFrame& operator=(const ScrollFrame&) = default;

		private:
			Size _InnerSize;
			Coord _InnerCoord;
			ScrollMode _scrollMode;
		};
	} // namespace UI
} // namespace KolibriLib

#endif // __SCROLLFRAME_HPP__