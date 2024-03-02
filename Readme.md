# KolibriOS C++ Lib


библиотека для (чуть более) удобной работы с KolibriOS, с похренитетом к оптимизации

Сия библиотека представляет из себя прослойку абстракций, переименованных функций и прочей фигни, что упростит разработку приложений

Библиотека будет хороша для создания маленьких приложений

Лучше используйте SDL вместо этого куска кода

## Зачем оно надо

+ Эта библиотека даёт упращенный доступ к системным функциям
+ чуть более удобно делать UI, чем просто системными API и/или C_Layer(кому как)

## Сборка

Для сборки без 100% вероятности ошибки необходимо отредактировать `CONTRIB_DIR` в файле Makefile (`CONTRIB_DIR = Path_to_KolibriOS/contrib`)

И просто собрать:
```
make
```
Ждите...

## Как использовать это


Просто подключить заголовочный файл:
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

ВОЗМОЖНО что то полезное есть в wiki на github

Описания функций и классов в Docs/html

Тема на форуме: http://board.kolibrios.org/viewtopic.php?t=5621