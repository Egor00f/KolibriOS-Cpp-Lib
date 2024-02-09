AR	= kos32-ar
AS	= kos32-as
CC	= kos32-gcc
CXX	= kos32-g++
LD	= kos32-ld 

LIB_NAME := libkcpp

#DIRs
CONTRIB_DIR = F:/KolibriOs/contrib
SDK_DIR = $(CONTRIB_DIR)/sdk



INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I $(SDK_DIR)/sources/libstdc++-v3/include -I C_Layer/INCLUDE 
LIBPATH = -L $(SDK_DIR)/lib -L C:/MinGW/msys/1.0/home/autobuild/tools/win32/mingw32/lib

#Flags
CFLAGS = -c -fno-ident -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -std=c++14
LDFLAGS = -static -S -nostdlib -Tapp-dynamic.lds --image-base 0 -O2 -T $(SDK_DIR)/sources/newlib/app.lds

LIB_PATH = src/include/kolibriLib

SOURCES = $(LIB_PATH)/filesystem.cpp $(LIB_PATH)/os.cpp $(LIB_PATH)/color.cpp $(LIB_PATH)/UI.cpp $(LIB_PATH)/graphic.cpp $(LIB_PATH)/image.cpp $(LIB_PATH)/text.cpp $(LIB_PATH)/button.cpp $(LIB_PATH)/form.cpp $(LIB_PATH)/thread.cpp $(LIB_PATH)/frame.cpp $(LIB_PATH)/window.cpp $(LIB_PATH)/childWindow.cpp
OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))



all: setup $(LIB_NAME).a install CLAYER clean EXAMPLES done

setup:
	@@Echo off

CLAYER:
	@echo "# make C_Layer:" 
	$(MAKE) -C C_Layer/ASM

$(LIB_NAME).a: $(OBJECTS)
	$(AR) -rcs $(LIB_NAME).a $(OBJECTS)

%.o : %.cpp $(SOURCES)
	@echo "# compile:" $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

EXAMPLES:
	@echo "# Make examples"
	$(MAKE) -C src/examples

install:
	@echo "# installing lib"
	@mv $(LIB_NAME).a $(SDK_DIR)/lib/$(LIB_NAME).a

clean:
	@echo "# clean"
	@rm $(OBJECTS)
	
done:
	@echo "+-------------------------------------+"
	@echo "|          Compilation Done!          |"
	@echo "+-------------------------------------+"