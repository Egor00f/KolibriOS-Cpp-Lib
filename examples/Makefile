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
LIBPATH = -L C:/MinGW/msys/1.0/home/autobuild/tools/win32/mingw32/lib -L $(SDK_DIR)/lib

#Flags
CFLAGS = -Wpointer-arith -fpermissive -c -fno-ident -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -std=c++11 
LDFLAGS = -static -S -nostdlib -T app-dynamic.lds --image-base 0 -T $(SDK_DIR)/sources/newlib/app.lds  -lstdc++ -lsupc++ -lgcc -lc.dll -lkcpp



SOURCES = $(EXECUTABLE).cpp 
OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))


#  Copy this  ||
#            \||/
#             \/
################# KolibriLib ####################

############### C Layer ############
#                    
#      Change it     || 
#   (for u project) \||/
#                    \/
C_LAYER_DIR = ../include/C_Layer
C_LAYER_OBJ = $(C_LAYER_DIR)/OBJ/loadlibimg.obj $(C_LAYER_DIR)/OBJ/loadrasterworks.obj $(C_LAYER_DIR)/OBJ/loadlibini.obj $(C_LAYER_DIR)/OBJ/loadbuf2d.obj
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
	@echo " "
	@echo "| linking:" $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIBPATH) --subsystem console -o $(EXECUTABLE) $(OBJECTS) $(C_LAYER_OBJ)
	kos32-strip -s $(EXECUTABLE) -o $(EXECUTABLE)
	kos32-objcopy $(EXECUTABLE) -O binary
	@rm $(EXECUTABLE).o

%.o : %.cpp Makefile $(SOURCES)
	@echo " "
	@echo "| compile:" $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< 



	