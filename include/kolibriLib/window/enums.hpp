#ifndef __WINDOW_ENUMS_HPP__
#define __WINDOW_ENUMS_HPP__

#include <cstdint>

namespace KolibriLib
{
	namespace window
	{
		/// @brief Список стилей для окна
		enum class WindowStyle
		{
			/// @brief только определить область окна, ничего не рисовать
			/// @details вид окна полность определяется приложением
			NoDraw = 1,

			/// @brief Окно со скином
			withSkin = 3,

			/// @brief Окно со скином фиксированных размеров
			FixSizewithSkin = 4,
		};

		/// @brief Настройки для окна. битовые флаги
		enum WindowSettings
		{
			/// @brief у окна есть заголовок
			WindowHaveTitle = 1,

			/// @brief Координаты крафических приметивов относительно окна
			RelativeCoord = 2,

			/// @brief Не закрашивать рабочую область при отрисовке окна
			NoDrawWorkspace = 4,

			/// @brief Градиентная заливка рабочей области
			/// @details по умолчанию нормальная заливка
			GradientDraw = 8,

			/// @brief неперемещаемое окно
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

			/// @brief обчное
			Normal = 0,

			/// @brief Всегда поверх остальных окон
			AlwaysTop = 1
		};
	} // namespace window
	
}

#endif // __WINDOW_ENUMS_HPP__
