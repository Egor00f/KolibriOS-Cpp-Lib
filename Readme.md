KolibriOS C++ Lib
===

библиотека для (чуть более) удобной работы с KolibriOS, с похренитетом к оптимизации

Как использовать это
---

Подключить заголовочный файл:
```
#include <KolibriLib.hpp>
```
Добавть в ваш Makefile:
```
KOLIBRILIB_INCLUDE_PATH = F:/KolibriOs/KolibriOS-Cpp-Lib/src/include

KOLIBRILIB_INCLUDE = -I $(KOLIBRILIB_INCLUDE_PATH)

INCLUDES += $(KOLIBRILIB_INCLUDE)

```
KOLIBRILIB_INCLUDE_PATH нужно отредактировать

Примеры использования лежат в src/examples/



Описания функций и классов в Docs/html
