KolibriOS C++ Lib
===

библиотека для (чуть более) удобной работы с KolibriOS, с похренитетом к оптимизации

Как использовать это
---

Подключить заголовочный файл:
```
#include <KolibriLib.hpp>
```
Добавть в ваш Makefile(это есть в src/examples/Makefile):
```
C_LAYER_DIR = $(CONTRIB_DIR)/C_Layer
C_LAYER_OBJ = $(C_LAYER_DIR)/OBJ/loadlibimg.obj

KOLIBRILIB_INCLUDE_PATH = ../include

KOLIBRILIB_INCLUDE = -I $(KOLIBRILIB_INCLUDE_PATH) -I $(C_LAYER_DIR)/INCLUDE

INCLUDES += $(KOLIBRILIB_INCLUDE)

SOURCES += $(KOLIBRILIB_INCLUDE)/kolibriLib/%.cpp

```
KOLIBRILIB_INCLUDE_PATH нужно отредактировать



cmake не тестировался но
Для использования этой библиотеки необходимо добавить в ваш CMakeLists.txt

```
include(PATH_TO_THIS_LIB/include.cmake)
```

Или если вы используете Makefile достаточно добавить в INCLUDES 
```
-I /PATH_TO_THIS_LIB/include
```

подробнее в /Docs

Сборка
---
собрать примеры можно командой:
```
cmake .
```
