UI.hpp
===

обращатся как к KolibriLib::UI

Классы
---
* KolibriLib::UI::UIElement  
  бесполезный класс, просто шаблон для остальных
* KolibriLib::UI::Form  
  Форма для ввода текста
  Методы:
  - ```render()```
  - ```Handler()```
  - ```GetInput()```
* KolibriLib::UI::buttons::Button  
  Кнопка

Работа с текстом
---
Ко всем функциям обращатся как к KolibriLib::UI::text::

* ```DrawText(text, (KolibriLib::point)coord, (optional) size, color)``` - Выводит текст  
  Функция перегружена 
  - text может быть как const char* так и std::string
  - size можно не указывать, по умолчанию 9px
  - color можно не указывать, по умолчанию использется системный
*