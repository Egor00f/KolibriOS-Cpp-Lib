#ifndef __BUTTONSBASE_HPP__
#define __BUTTONSBASE_HPP__

#include <include_ksys.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/os.hpp>
#include <kolibriLib/debug.hpp>
#include <kolibriLib/globals.hpp>

#include <vector>

namespace KolibriLib
{
	namespace UI
	{
		namespace buttons
		{
			/// @brief ID кнопки
			struct ButtonID
			{
				uint32_t value;

				ButtonID(unsigned val);

				/// @brief является ли этот ID пригодным
				/// @details ID кнопок могут быть только от 0 до 0x8000 (исключая сами числа)
				bool CheckIsValid() const;

				ButtonID operator=(const unsigned &val);

				/// @brief
				operator uint32_t() const;
			};

			const ButtonID ButtonIDNotSet = 0;

			/// @brief Самый большой ID. Дальше низя
			const ButtonID ButtonIDEnd = 0x8000;

			/// @brief Id кнопки закрытия окна
			const ButtonID CloseButton = 1;

			/// @brief Id кнопки минимизации окна
			const ButtonID MinimizeButton = 0xffff;

			/// \brief Получить свободный номер id кнопки из списка
			/// \paragraph Эта функция может выполнятся очень долго, если вы уже создали довольно много кнопок. Это становится действительно важно когда у вас объявленно более 2000 кнопок
			/// \return номер кнопки из списка ButtonsIdList
			ButtonID GetFreeButtonId(std::vector<ButtonID> *ButtonsIdList, uint32_t startID = 2);

			/// \brief Освободить номер кнопки
			/// \param id номер номер кнопки из списка ButtonsIdList
			bool FreeButtonId(const ButtonID &id, std::vector<ButtonID> *ButtonsIdList);

			/// \brief Создать кнопку, автоматически присвоить ей id
			/// \param coords координаты
			/// \param size размер
			/// \param color цвет
			/// \return id созданной кнопки
			ButtonID autoDefineButton(std::vector<ButtonID> *ButtonsIdList, const Coord &coords, const Size &size, const Colors::Color &color = Globals::SystemColors.work_button);

			/// \brief Создать кнопку, вручную
			/// \param coords координаты
			/// \param size размер
			/// \param id idшник кнопки
			/// \param color цвет
			inline void DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = Globals::SystemColors.work_button)
			{
				_ksys_define_button(
					static_cast<std::uint32_t>(coord.x),
					static_cast<std::uint32_t>(coord.y),
					static_cast<std::uint32_t>(size.x),
					static_cast<std::uint32_t>(size.y),
					static_cast<std::uint32_t>(id),
					color.operator ksys_color_t());
			}

			/// \brief Создать кнопку, вручную
			/// \param coords координаты
			/// \param size размер
			/// \param id idшник кнопки
			/// \param color цвет
			inline void DefineButton(std::vector<ButtonID> *ButtonsIdList, const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = Globals::SystemColors.work_button)
			{
				ButtonsIdList->push_back(id);
				DefineButton(coord, size, id, color);
			}

			/// \brief Удалить кнопу
			/// \param id id удаляемой кнопки
			inline void DeleteButton(ButtonID id)
			{
				_ksys_delete_button(static_cast<std::uint32_t>(id));
			}

			/// \brief Удалить кнопу
			/// \param id id удаляемой кнопки
			inline void DeleteButton(std::vector<ButtonID> *ButtonsIdList, ButtonID id)
			{
				_ksys_delete_button(id);
				FreeButtonId(id, ButtonsIdList); // Кнопка удалена, теперь этот id не использется
			}

			/// @brief проверить какая кнопка нажата
			/// @return id нажатой кнопки
			inline ButtonID GetPressedButton()
			{
				return ButtonID(_ksys_get_button());
			}

			typedef enum ButtonStyle
			{
				/// @brief Плоские кнопки
				flat = 0,

				/// @brief Объёмные кнокпи
				volumetric = 1
			} buttonStyle;

			inline void SetButtonStyle(buttonStyle style)
			{
				asm_inline(
					"int $0x40" ::"a"(48), "b"(1), "c"(style));
			}

			/// @brief Автоматическое присвоение ID для кнопок
			/// @note Этот класс работает только с ID кнопок и ничего больше
			class ButtonsIDController
			{
			public:
				/// @brief Получить свободный ID кнопки из списка
				/// @return ID кнопки, который не занят
				ButtonID GetFreeButtonID();

				/// @brief Освободить ID
				/// @param id ID который нужно освободить
				void FreeButtonID(const ButtonID &id);

				std::vector<ButtonID> *GetButtonsIDList();

				const std::vector<ButtonID> *GetButtonsIDList() const;

			private:
				/// @brief Список использованных id кнопок
				std::vector<ButtonID> ButtonsIdList{/*CloseButton,*/ MinimizeButton};

				uint32_t _top = 2;
			};

		} // namespace buttons

	} // namespace UI

	void PrintDebug(UI::buttons::ButtonID out);

	namespace Globals
	{
		extern UI::buttons::ButtonsIDController *DefaultButtonsIDController;
	}
} // namespace KolibriLib

#endif // __BUTTONSBASE_HPP__