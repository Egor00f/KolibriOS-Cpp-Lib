#NAME
EXECUTABLE = test

AR	= kos32-ar
AS	= kos32-as
CC	= kos32-gcc
CXX	= kos32-g++
LD	= kos32-ld 

#DIRs
KolibriOS_repo_dir = ../../kolibrios
CONTRIB_DIR = $(KolibriOS_repo_dir)/contrib
SDK_DIR = $(CONTRIB_DIR)/sdk
TOOLCHAIN_DIR = C:/MinGW/msys/1.0/home/autobuild/tools/win32



INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I$(SDK_DIR)/sources/libstdc++-v3/include
LIBPATH = -L $(SDK_DIR)/lib -L $(TOOLCHAIN_DIR)/lib -L $(TOOLCHAIN_DIR)/mingw32/lib

#Flags
CFLAGS = -c -fno-ident -fomit-frame-pointer -fno-ident -O2 -g -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -std=c++11 -Wpointer-arith -fpermissive 
LDFLAGS = -static -S -nostdlib -T app-dynamic.lds --image-base 0 -T $(SDK_DIR)/sources/newlib/app.lds -lstdc++ -lsupc++ -lgcc -lc.dll -lkcpp



SOURCES = $(EXECUTABLE).cpp 
OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))


#  Copy this  ||
#            \||/
#             \/
################# KolibriLib ####################
#                            || 
#                Change it   || 
#                           \||/
#                            \/
KOLIBRILIB_INCLUDE_PATH = ../include

############### C Layer ############

C_LAYER_DIR = $(KOLIBRILIB_INCLUDE_PATH)/C_Layer
C_LAYER_OBJ = $(C_LAYER_DIR)/OBJ/loadlibimg.obj $(C_LAYER_DIR)/OBJ/loadrasterworks.obj $(C_LAYER_DIR)/OBJ/loadlibini.obj $(C_LAYER_DIR)/OBJ/loadbuf2d.obj $(C_LAYER_DIR)/OBJ/loadboxlib.obj
####################################

KOLIBRILIB_INCLUDE = -I $(KOLIBRILIB_INCLUDE_PATH) -I $(C_LAYER_DIR)/INCLUDE

INCLUDES += $(KOLIBRILIB_INCLUDE)

############### End of copy text #################################


default: Exapmle



Exapmle: $(OBJECTS) Makefile
	@echo " "
	@echo "| linking:" $(OBJECTS)
	$(LD) $(LIBPATH) --subsystem native -o $(EXECUTABLE) $(OBJECTS) $(C_LAYER_OBJ) $(LDFLAGS)
	kos32-strip -S $(EXECUTABLE)
	kos32-objcopy $(EXECUTABLE) -O binary
	@rm $(EXECUTABLE).o

%.o : %.cpp Makefile $(SOURCES)
	@echo " "
	@echo "| compile:" $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< 



	
