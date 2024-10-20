#ifndef __WINDOW_ENUMS_HPP__

/*
	Файл с перечислениями в пространстве имен window
*/
#define __WINDOW_ENUMS_HPP__

#include <cstdint>
#include <kolibriLib/enumBitfield.hpp>

namespace KolibriLib
{
	namespace window
	{
		/// @brief Список стилей для окна
		enum class WindowStyle
		{
			/// @brief только определить область окна, ничего не рисовать
			/// @details вид окна полностью определяется приложением
			NoDraw = 1,

			/// @brief Окно со скином
			withSkin = 3,

			/// @brief Окно со скином фиксированных размеров
			FixSizeWithSkin = 4,
		};

		/// @brief Настройки для окна. битовые флаги
		enum WindowSettings : std::uint16_t
		{
			/// @brief у окна есть заголовок
			WindowHaveTitle = 1,

			/// @brief Координаты графических примитивов относительно окна
			RelativeCoord = 2,

			/// @brief Не закрашивать рабочую область при отрисовке окна
			NoDrawWorkspace = 4,

			/// @brief Градиентная заливка рабочей области
			/// @details по умолчанию нормальная заливка
			GradientDraw = 8,

			/// @brief Не перемещаемое окно
			/// @details работает для всех стилей окон
			NotMoveable = (1 << 8),

			TitleGradient = (8 << (8 + 4))
		};

		/// @brief Список констант положения окна относительно других окон:
		enum class Pos : std::int16_t
		{
			/// @brief На фоне
			BackGround = -2,

			/// @brief всегда за другими окнами
			AlwaysBack = -1,

			/// @brief обычное
			Normal = 0,

			/// @brief Всегда поверх остальных окон
			AlwaysTop = 1
		};
	} // namespace window	
} // namespace KolibriLib

template<> struct is_flag<KolibriLib::window::WindowSettings> : std::true_type {};

#endif // __WINDOW_ENUMS_HPP__
