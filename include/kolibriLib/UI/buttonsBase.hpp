#ifndef __BUTTONSBASE_H__
#define __BUTTONSBASE_H__

#include <sys/ksys.h>

#include <kolibriLib/UI/UI.hpp>

#include <unordered_map>

namespace KolibriLib
{
	namespace UI
	{
		namespace buttons
		{
			/// @brief Id кнопки
			typedef unsigned int ButtonID;

			// Коды кнопок начинаются с этого числа
			const ButtonID StartButtonId = 100;

			#ifndef __MakeStaticLib__
			/// @brief Список idшников кнопок
			std::unordered_map<ButtonID, bool> ButtonsIdList;
			#endif

			/// \brief Получить свободный номер id кнопки из списка
			/// \paragraph Эта функция может выполнятся очень долго, если вы уже создали довольно много кнопок. Это становится действительно важно когда у вас объявленно более 2000 кнопок
			/// \return номер кнопки из списка @link ButtonsIdList
			ButtonID GetFreeButtonId();

			/// \brief Освободить номер кнопки
			/// \param id номер номер кнопки из списка @link ButtonsIdList
			void FreeButtonId(const ButtonID &id);

			/// \brief Создать кнопку, автоматически присвоить ей id
			/// \param coords координаты
			/// \param size размер
			/// \param color цвет
			/// \return id созданной кнопки
			ButtonID autoDefineButton(const Coord &coords, const Size &size, const Colors::Color &color = OS::GetSystemColors().work_button);

			/// \brief Создать кнопку, вручную
			/// \param coords координаты
			/// \param size размер
			/// \param id idшник кнопки
			/// \param color цвет
			inline void DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = OS::GetSystemColors().work_button);

			/// \brief Удалить кнопу
			/// \param id id удаляемой кнопки
			inline void DeleteButton(unsigned id);

			/// @brief проверить какая кнопка нажата
			/// @return id нажатой кнопки
			inline unsigned GetPressedButton();

			#ifndef __MakeStaticLib__

			ButtonID GetFreeButtonId()
			{
				for (unsigned i = 0; i < ButtonsIdList.size(); i++)
				{
					if (ButtonsIdList.count(i) == 0)
					{
						return i + StartButtonId;
					}
				}
			}

			void FreeButtonId(const ButtonID &id)
			{
				ButtonsIdList.erase(id);
			}

			ButtonID autoDefineButton(const Coord &coords, const Size &size, const Colors::Color &color = OS::GetSystemColors().work_button)
			{
				ButtonID id = GetFreeButtonId(); // Автоматически получаем id для кнопки
				_ksys_define_button(coords.x, coords.y, size.x, size.y, id, color.val);
				return id;
			}

			void DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = OS::GetSystemColors().work_button)
			{
				_ksys_define_button(coord.x, coord.y, size.x, size.y, id, color.val);
			}

			inline void DeleteButton(unsigned id)
			{
				_ksys_delete_button(id);
				FreeButtonId(id); // Кнопка удалена, теперь этот id не использется
			}

			inline unsigned GetPressedButton()
			{
				return _ksys_get_button();
			}

			#endif
		} // namespace buttons
		
	} // namespace UI
	
} // namespace KolibriLib


#endif // __BUTTONSBASE_H__