#ifndef __BUF2D_HPP__
#define __BUF2D_HPP__

#include <C_Layer/INCLUDE/kolibri_buf2d.h>
#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <assert.h>

class buf2dLib
{
public:
	buf2dLib();
};

extern buf2dLib buf2dLibv;

namespace buf2d
{
	

	/// @brief Глубина цвета
	enum class BPP : std::uint8_t
	{
		/// @brief  8 битный цвет
		bpp8 = 8,

		/// @brief 24 битный цвет
		RGB = 24,

		/// @brief 24 битный цвет + прозрачность
		RGBA = 32
	};

	/**
	 * @brief Вращение
	 */
	enum class RotateEnum
	{
		/// @brief повернуть на 90 градусов
		rotate_90 = 90,

		/// @brief Повернуть 180 градусов
		rotate_180 = 180,

		/// @brief повернуть на 270 градусов
		rotate_270
	};

	/**
	 * @brief Создать буффер
	 * @param size размеры буфера
	 * @param color цвет
	 * @param bpp бит на пиксель
	 * @return указатель на созданный буффер
	 */
	inline buf2d_struct* Create(const KolibriLib::Size& size, KolibriLib::Colors::Color color, BPP bpp)
	{
		return buf2d_create(0, 0, size.x, size.y, color, static_cast<std::uint8_t>(bpp));
	}

	/**
	 * @brief Создать буффер
	 * @param size размеры буфера
	 * @param color цвет
	 * @param bpp бит на пиксель
	 * @return указатель на созданный буффер
	 */
	inline void Create(buf2d_struct* buff, const KolibriLib::Size& size, KolibriLib::Colors::Color color, BPP bpp)
	{
		buff = Create(size, color, bpp);
	}

	/**
	 * @brief Удалить буффер
	 * @param buff 
	 */
	inline void Delete(buf2d_struct* buff)
	{
		buf2d_delete(buff);
	}

	/**
	 * @brief Очистить буффер цветом
	 * @param buff буффер
	 * @param color цвет
	 */
	inline void Clear(buf2d_struct* buff, KolibriLib::Colors::Color color)
	{
		buf2d_clear(buff, color);
	}

	inline void Draw(buf2d_struct* buff)
	{
		assert(buff->color_bit == static_cast<uint8_t>(BPP::RGB));

		buf2d_draw(buff);
	}

	/**
	 * @brief Изменить пиксель
	 * @param buff 
	 * @param coord координаты пикселя
	 * @param color 
	 */
	inline void SetPixel(buf2d_struct* buff, const KolibriLib::Coord& coord, KolibriLib::Colors::Color color)
	{
		buf2d_set_pixel(buff, coord.y, coord.x, color);
	}

	/**
	 * @brief Получить пиксель
	 * @param buff буффер
	 * @param coord координаты пикселя
	 * @return цвет пикселя
	 */
	inline KolibriLib::Colors::Color GetPixel(buf2d_struct* buff, const KolibriLib::Coord& coord)
	{
		return buf2d_get_pixel(buff, coord.x, coord.y);
	}

	/**
	 * @brief Изменить размер буффера
	 * @param buff буфер
	 * @param NewSize новый размер
	 * @param scale растягивать ли изображение
	 */
	inline void Resize(buf2d_struct* buff, const KolibriLib::Size& NewSize, bool scale = true)
	{
		buf2d_resize(buff, NewSize.y, NewSize.x, 1 + scale);
	}

	/**
	 * @brief Нарисовать прямоугольник (линии)
	 * @param buff буффер в котором рисуктся прямоугольник
	 * @param coord Координаты левого верхнего угла прямоугольника
	 * @param size размер прямоугольника
	 * @param color цвет
	 */
	inline void DrawRect(buf2d_struct* buff, const KolibriLib::Coord& coord, const KolibriLib::Size& size, KolibriLib::Colors::rgb color)
	{
		buf2d_rect_by_size(buff, coord.x, coord.y, size.x, size.y, color);
	}

	/**
	 * @brief Нарисовать прямоугольник (закрашенный)
	 * @param buff буффер в котором рисуктся прямоугольник
	 * @param coord Координаты левого верхнего угла прямоугольника
	 * @param size размер прямоугольника
	 * @param color цвет
	 */
	inline void DrawFilledRect(buf2d_struct* buff, const KolibriLib::Coord& coord, const KolibriLib::Size& size, KolibriLib::Colors::rgb color)
	{
		buf2d_filled_rect_by_size(buff, coord.x, coord.y, size.x, size.y, color);
	}

	/**
	 * @brief Применить прозрачность
	 * @param dst Буфер на котором рисуется (RGB)
	 * @param src буфер с прозрачностью
	 * @param coord
	 */
	inline void ApplyTrasparency(buf2d_struct* dst, const buf2d_struct* src, const KolibriLib::Coord& coord = {0,0})
	{
		assert(src->color_bit == static_cast<uint8_t>(BPP::RGBA) && dst->color_bit == static_cast<uint8_t>(BPP::RGB));

		buf2d_bit_blt_transp(dst, coord.x, coord.y, const_cast<buf2d_struct*>(src));
	}

	/**
	 * @brief Нарисовать круг
	 * @param buff 
	 * @param coord 
	 * @param Radius 
	 * @param color 
	 */
	inline void DrawCircle(buf2d_struct* buff, const KolibriLib::Coord& coord, unsigned Radius, KolibriLib::Colors::Color color)
	{
		buf2d_circle(buff, coord.x, coord.y, Radius, color);
	}

	/**
	 * @brief Обёртка для buf2d_struct
	 * @details Просто обёртка к конструктором и деструктором
	 * Предпочтительнее использовать такой вид объявления:
	 * @code
	 * buffer* buff = new buffer;
	 * @endcode
	 */
	struct buffer : public buf2d_struct
	{
		/**
		 * @brief Конструктор по умолчанию
		 */
		buffer();

		buffer(BPP bpp);

		buffer(const KolibriLib::Size& size, BPP bpp = BPP::RGB);

		buffer(const KolibriLib::Size& size, KolibriLib::Colors::rgb color);

		buffer(const KolibriLib::Size& size, KolibriLib::Colors::Color color);

		/**
		 * @brief Конструктор копирования
		 * @param buff 
		 */
		buffer(const buf2d_struct* buff);

		/**
		 * @brief Деструктор
		 */
		~buffer();
	};
}


#endif // __BUF2D_HPP__