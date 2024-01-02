#NAME
EXECUTABLE = messagebox


export $PATH = C:/MinGW/msys/1.0/home/autobuild/tools/win32/bin/


AR	= $(COMPILER_PATH)kos32-ar
AS	= $(COMPILER_PATH)kos32-as
CC	= kos32-gcc
CXX	= kos32-g++
LD	= kos32-ld 

#DIRs
SDK_DIR = ../../../contrib/sdk

INCLUDES = -I $(SDK_DIR)/sources/libstdc++-v3/include -I $(SDK_DIR)/sources/newlib/libc/include -I ../include
LIBPATH = -L $(SDK_DIR)/lib -L C:/MinGW/msys/1.0/home/autobuild/tools/win32/mingw32/lib

#Flags
CFLAGS = -c -fno-ident -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -std=gnu++17
LDFLAGS = -static -S -Tapp-dynamic.lds --image-base 0 -O2


SOURCES = messageBox.cpp 
OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))

default: messageBox



messageBox: $(OBJECTS) Makefile

	@echo "linking:" $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIBPATH) --subsystem console -o $(EXECUTABLE) $(OBJECTS) -lstdc++ -lsupc++ -lgcc -lc.dll
	kos32-strip -s $(EXECUTABLE) -o $(EXECUTABLE)
	kos32-objcopy $(EXECUTABLE) -O binary

%.o : %.cpp Makefile $(SOURCES)
	@echo "compile:" $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< 



	