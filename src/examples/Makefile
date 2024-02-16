#NAME
EXECUTABLE = HelloWorld

AR	= kos32-ar
AS	= kos32-as
CC	= kos32-gcc
CXX	= kos32-g++
LD	= kos32-ld 

#DIRs
CONTRIB_DIR = F:/KolibriOs/contrib
SDK_DIR = $(CONTRIB_DIR)/sdk



INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I $(SDK_DIR)/sources/libstdc++-v3/include 
LIBPATH = -L $(SDK_DIR)/lib -L C:/MinGW/msys/1.0/home/autobuild/tools/win32/mingw32/lib

#Flags
CFLAGS = -c -fno-ident -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -std=c++14
LDFLAGS = -static -S -nostdlib -Tapp-dynamic.lds --image-base 0 -O2 -T $(SDK_DIR)/sources/newlib/app.lds



SOURCES = $(EXECUTABLE).cpp 
OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))


#  Copy this  ||
#            \||/
#             \/
################# KolibriLib ####################

############### C Layer ############
#                    
#       Change it   || 
#                  \||/
#                   \/
C_LAYER_DIR = ../../C_Layer
C_LAYER_OBJ = $(C_LAYER_DIR)/OBJ/loadlibimg.obj
####################################

#                            || 
#                Change it   || 
#                           \||/
#                            \/
KOLIBRILIB_INCLUDE_PATH = ../include

KOLIBRILIB_INCLUDE = -I $(KOLIBRILIB_INCLUDE_PATH) -I $(C_LAYER_DIR)/INCLUDE

INCLUDES += $(KOLIBRILIB_INCLUDE)


################################################


default: Exapmle



Exapmle: $(OBJECTS) Makefile
	@echo "| linking:" $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIBPATH) --subsystem console -o $(EXECUTABLE) $(OBJECTS) $(C_LAYER_OBJ) -lstdc++ -lsupc++  -lgcc -lc.dll -lsound -lkcpp
	kos32-strip -s $(EXECUTABLE) -o $(EXECUTABLE)
	kos32-objcopy $(EXECUTABLE) -O binary
	@rm $(EXECUTABLE).o

%.o : %.cpp Makefile $(SOURCES)
	@echo "| compile:" $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< 



	