# KolibriOS C++ Lib


библиотека для (чуть более) удобной работы с KolibriOS, с похренитетом к оптимизации. И сразу.

Сия библиотека представляет из себя прослойку абстракций, переименованных функций и прочей фигни, что упростит разработку приложений

Библиотека будет хороша для создания маленьких приложений

АХТУНГ! приложения использующие эту либу будут очень большими и медлеными.

## Зачем оно надо

+ Эта библиотека даёт упращенный доступ к системным функциям
+ чуть более удобно делать UI, чем просто системными API и/или C_Layer(кому как)

## Сборка

По умолчанию предпологается что репозитрий kolibrios лежит в той же папке что и папка этого проекта, но вы можете отредактировать CMakeLists.txt
для сборки библиотеки можно запустить скрипт install.bat
```
install.bat
```
или вручную:
```
mkdir build
cmake ..
make
```


## Как использовать это


1. Скомпилируйте библиотеку
2. (необязятельно)Переместите build/libKolibriLib.a в ваш проект
3. Подключите заголовочный файл(нужно указать папку include в ${includePath}):
```
#include <KolibriLib.hpp>
```
4. Прочитайте doxygen(стем как сгенерить сами думаю справитесь)

Примеры использования лежат в папке `examples`

ВОЗМОЖНО что то полезное есть в wiki на github

Тема на форуме kolibrios: http://board.kolibrios.org/viewtopic.php?t=5621
