#ifndef __BUTTONSBASE_H__
#define __BUTTONSBASE_H__

#include <sys/ksys.h>

#include <kolibriLib/types.hpp>
#include <kolibriLib/color.hpp>
#include <kolibriLib/system/os.hpp>

#include <vector>

namespace KolibriLib
{
	namespace UI
	{
		namespace buttons
		{
			/// @brief Id кнопки
			typedef uint32_t ButtonID;

			const ButtonID ButtonIDNotSet = 0;

			const ButtonID ButtonIDEnd = 0x8000;

			/// @brief Id кнопки закрытия окна
			const ButtonID CloseButton = 1;

			/// @brief Id кнопки минимизации окна
			const ButtonID MinimizeButton = 0xffff;

			/// \brief Получить свободный номер id кнопки из списка
			/// \paragraph Эта функция может выполнятся очень долго, если вы уже создали довольно много кнопок. Это становится действительно важно когда у вас объявленно более 2000 кнопок
			/// \return номер кнопки из списка ButtonsIdList
			ButtonID GetFreeButtonId(std::vector<ButtonID>*ButtonsIdList);

			/// \brief Освободить номер кнопки
			/// \param id номер номер кнопки из списка ButtonsIdList
			void FreeButtonId(const ButtonID &id, std::vector<ButtonID> *ButtonsIdList);

			/// \brief Создать кнопку, автоматически присвоить ей id
			/// \param coords координаты
			/// \param size размер
			/// \param color цвет
			/// \return id созданной кнопки
			ButtonID autoDefineButton(std::vector<ButtonID>*ButtonsIdList, const Coord &coords, const Size &size, const Colors::Color &color = OS::GetSystemColors().work_button);

			/// \brief Создать кнопку, вручную
			/// \param coords координаты
			/// \param size размер
			/// \param id idшник кнопки
			/// \param color цвет
			inline void DefineButton(const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = OS::GetSystemColors().work_button)
			{
				_ksys_define_button(coord.x, coord.y, size.x, size.y, 0x00FFFFFF&id, color);
			}

			/// \brief Создать кнопку, вручную
			/// \param coords координаты
			/// \param size размер
			/// \param id idшник кнопки
			/// \param color цвет
			inline void DefineButton(std::vector<ButtonID>*ButtonsIdList, const Coord &coord, const Size &size, const ButtonID &id, Colors::Color color = OS::GetSystemColors().work_button)
			{
				ButtonsIdList->push_back(id);
				_ksys_define_button(coord.x, coord.y, size.x, size.y, 0x00FFFFFF&id, color);
			}

			/// \brief Удалить кнопу
			/// \param id id удаляемой кнопки
			inline void DeleteButton( unsigned id)
			{
				_ksys_delete_button(id);
			}

			/// \brief Удалить кнопу
			/// \param id id удаляемой кнопки
			inline void DeleteButton(std::vector<ButtonID> *ButtonsIdList, unsigned id)
			{
				_ksys_delete_button(id);
				FreeButtonId(id, ButtonsIdList); // Кнопка удалена, теперь этот id не использется
			}

			/// @brief проверить какая кнопка нажата
			/// @return id нажатой кнопки
			inline ButtonID GetPressedButton()
			{
				return (ButtonID)_ksys_get_button();
			}

			typedef enum ButtonStyle{
				flat = 0,
 				volumetric = 1
			} buttonStyle;

			inline void SetButtonStyle(buttonStyle style)
			{
				asm_inline(
					"int $0x40"
					::"a"(48), "b"(1), "c"(style)
				);
			}

			/// @brief Автоматическое присвоение ID для кнопок
			class ButtonsIDController
			{
				public:
					/// @brief  Получить свободный id кнопки из списка
					/// @return
					ButtonID GetFreeButtonID();

					/// @brief 
					/// @param id 
					void FreeButtonID(const ButtonID &id);

					std::vector<ButtonID> *GetButtonsIDList();

					const std::vector<ButtonID> *GetButtonsIDList() const;
					
				private:
					/// @brief Список использованных id кнопок
					std::vector<ButtonID> ButtonsIdList {/*CloseButton,*/ MinimizeButton};

			};

		} // namespace buttons
		
	} // namespace UI
	
} // namespace KolibriLib


#endif // __BUTTONSBASE_H__