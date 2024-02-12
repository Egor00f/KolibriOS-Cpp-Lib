#	Makefile

AR	= kos32-ar
AS	= kos32-as
CC	= kos32-gcc
CXX	= kos32-g++
LD	= kos32-ld 

LIB_NAME = libkcpp

#DIRs
CONTRIB_DIR = ../contrib
SDK_DIR = $(CONTRIB_DIR)/sdk

INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I C_Layer/INCLUDE -I C:/MinGW/msys/1.0/home/autobuild/tools/win32/lib/gcc/mingw32/5.4.0/include -I C:\MinGW\msys\1.0\home\autobuild\tools\win32\lib\gcc\mingw32\5.4.0\include\c++ C:\MinGW\msys\1.0\home\autobuild\tools\win32\lib\gcc\mingw32\5.4.0\include\c++\mingw32 C:\MinGW\msys\1.0\home\autobuild\tools\win32\lib\gcc\mingw32\5.4.0\include\c++\tr1 -I C:\MinGW\msys\1.0\home\autobuild\tools\win32\lib\gcc\mingw32\5.4.0\include\c++\tr2 -I $(SDK_DIR)/sources/libstdc++-v3/include

#Flags
CFLAGS = -c -fno-ident -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -std=c++14

LIB_PATH = src/include/kolibriLib

SOURCES =  $(LIB_PATH)/types.cpp $(LIB_PATH)/filesystem.cpp $(LIB_PATH)/color.cpp $(LIB_PATH)/mouse.cpp $(LIB_PATH)/keyboard.cpp $(LIB_PATH)/screen.cpp $(LIB_PATH)/os.cpp  $(LIB_PATH)/UI.cpp $(LIB_PATH)/windowBase.cpp $(LIB_PATH)/graphic.cpp $(LIB_PATH)/image.cpp $(LIB_PATH)/text.cpp $(LIB_PATH)/button.cpp $(LIB_PATH)/form.cpp $(LIB_PATH)/thread.cpp $(LIB_PATH)/frame.cpp $(LIB_PATH)/window.cpp $(LIB_PATH)/childWindow.cpp
OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))



all: $(LIB_NAME).a install CLAYER clean

	

$(LIB_NAME).a: $(OBJECTS)
	$(AR) -rcs $(LIB_NAME).a $(OBJECTS)



install:
	@echo "| installing lib"
	@mv $(LIB_NAME).a $(SDK_DIR)/lib/$(LIB_NAME).a

CLAYER:
	@echo "| make C_Layer:" 
	$(MAKE) -C C_Layer/ASM

clean:
	@echo "| clean"
	@rm $(OBJECTS)

%.o : %.cpp Makefile
	@echo "| installing lib" $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< 