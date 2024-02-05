KolibriOS C++ Lib
===

библиотека для (чуть более) удобной работы с KolibriOS, с похренитетом к оптимизации

Зачем оно надо
---

+ Эта библиотека даёт ОЧЕНЬ упращенный доступ к системным функциям
+ Удобно делать UI(внатуре на это и делался в коде)

Как использовать это
---

Подключить заголовочный файл:
```
#include <KolibriLib.hpp>
```
Добавть в ваш Makefile:
```
C_LAYER_DIR = ../../C_Layer
C_LAYER_OBJ = $(C_LAYER_DIR)/OBJ/loadlibimg.obj

KOLIBRILIB_INCLUDE_PATH = F:/KolibriOs/KolibriOS-Cpp-Lib/src/include

KOLIBRILIB_INCLUDE = -I $(KOLIBRILIB_INCLUDE_PATH)

INCLUDES += $(KOLIBRILIB_INCLUDE)
```
KOLIBRILIB_INCLUDE_PATH и C_LAYER_DIR нужно отредактировать для вашего проекта

это все можно также найти в src/examples/Makefile

Примеры использования лежат в src/examples/



Описания функций и классов в Docs/html
