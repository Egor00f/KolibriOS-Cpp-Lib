#	Makefile

AR	= kos32-ar
AS	= kos32-as
CC	= kos32-gcc
CXX	= kos32-g++
LD	= kos32-ld 

#Имя библиотеки
LIB_NAME = libkcpp

#папка до репозитория kolibrios
KolibriOS_repo_dir = ../kolibrios
CONTRIB_DIR = $(KolibriOS_repo_dir)/contrib
SDK_DIR = $(CONTRIB_DIR)/sdk
C_LAYER_DIR = $(CONTRIB_DIR)/C_Layer

INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I $(SDK_DIR)/sources/libstdc++-v3/include -I include/C_Layer/INCLUDE -I include -L $(SDK_DIR)/lib

#Флаги компилятора
CFLAGS = -c -std=c++11 -fpermissive -Wpointer-arith -Wreturn-local-addr -O2 -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -Wparentheses -D __MakeStaticLib__ -L $(SDK_DIR)/lib -lgcc

# Папка в которой лежат cpp файлы
SRC_PATH = src

SOURCES = $(SRC_PATH)/filesystem.cpp $(SRC_PATH)/color.cpp $(SRC_PATH)/os.cpp $(SRC_PATH)/graphic.cpp $(SRC_PATH)/fonts.cpp \
$(SRC_PATH)/thread.cpp $(SRC_PATH)/types.cpp $(SRC_PATH)/textBase.cpp $(SRC_PATH)/img.cpp $(SRC_PATH)/UI.cpp $(SRC_PATH)/image.cpp \
$(SRC_PATH)/char.cpp $(SRC_PATH)/text.cpp

OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))



all: $(LIB_NAME).a INSTALL CLAYER EXAMPLES CLEAN DONE

ma:
	$(CXX) $(SOURCES) $(INCLUDES) $(CFLAGS)
mb:
	$(AR) rcs $(LIB_NAME).a $(OBJECTS)

$(LIB_NAME).a: $(OBJECTS)

	@echo " "
	@echo "| -------------------------------------"
	@echo "making static library..."
	$(AR) rcs $(LIB_NAME).a $(OBJECTS)

%.o : %.cpp Makefile
	@echo " "
	@echo "| -------------------------------------"
	@echo "|  compiling: " $@
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<


INSTALL:
	@echo " "
	@echo "| -------------------------------------"
	@echo "| installing lib"
	@mv -f $(LIB_NAME).a $(SDK_DIR)/lib/$(LIB_NAME).a

CLAYER:
	@echo " "
	@echo "| -------------------------------------"
	@echo "| Make C_Layer"
	$(MAKE) -C $(C_LAYER_DIR)

CLEAN:
	@echo " "
	@echo "| -------------------------------------"
	@echo "| clean"
	@rm $(OBJECTS)

EXAMPLES:
	@echo " "
	@echo "| -------------------------------------"
	@echo "| make examples"
	$(MAKE) -C examples



DONE:
	@echo " "
	@echo "| ----------------------------------- |"
	@echo "|                 DONE!               |"
	@echo "| ----------------------------------- |"