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
C_LAYER_OBJ_DIR = $(CONTRIB_DIR)/C_Layer/OBJ


INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I$(SDK_DIR)/sources/libstdc++-v3/include
LIBPATH = -L $(SDK_DIR)/lib -L $(TOOLCHAIN_DIR)/lib -L $(TOOLCHAIN_DIR)/mingw32/lib

#Flags
CFLAGS = -c -fno-ident -fomit-frame-pointer -fno-ident -O2 -g -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -std=c++11 -Wpointer-arith -fpermissive 
LDFLAGS = -static -S -nostdlib --image-base 0 -T $(SDK_DIR)/sources/newlib/app.lds -start-group  -lgcc -lc.dll  -lstdc++  -lsupc++ -lclayer -lkcppdebug -end-group



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

KOLIBRILIB_INCLUDE = -I $(KOLIBRILIB_INCLUDE_PATH) -I ../include/C_Layer/INCLUDE

INCLUDES += $(KOLIBRILIB_INCLUDE)

############### End of copy text #################################


default: Exapmle



Exapmle: $(OBJECTS) Makefile
	@echo " "
	@echo "| linking:" $(OBJECTS)
	$(LD) -o $(EXECUTABLE) $(LIBPATH) --subsystem native $(OBJECTS) $(LDFLAGS)
	kos32-strip -S $(EXECUTABLE)
	kos32-objcopy $(EXECUTABLE) -O binary
	@rm $(EXECUTABLE).o

%.o : %.cpp Makefile $(SOURCES)
	@echo " "
	@echo "| compile:" $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< 



	
