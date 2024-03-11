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

INCLUDES = -I $(SDK_DIR)/sources/newlib/libc/include -I $(SDK_DIR)/sources/libstdc++-v3/include -I include/C_Layer/INCLUDE -I include

#Flags
CFLAGS = -c -std=c++11 -fpermissive -Wreturn-local-addr

# Папка в которой лежат cpp файлы
SRC_PATH = src

SOURCES = $(SRC_PATH)/filesystem.cpp $(SRC_PATH)/color.cpp $(SRC_PATH)/os.cpp $(SRC_PATH)/fonts.cpp $(SRC_PATH)/thread.cpp
# $(SRC_PATH)/mouse.cpp $(SRC_PATH)/keyboard.cpp $(SRC_PATH)/screen.cpp $(SRC_PATH)/UI.cpp $(SRC_PATH)/windowBase.cpp $(SRC_PATH)/graphic.cpp $(SRC_PATH)/image.cpp  $(SRC_PATH)/form.cpp $(SRC_PATH)/frame.cpp $(SRC_PATH)/childWindow.cpp
OBJECTS =  $(patsubst %.cpp, %.o, $(SOURCES))



all: $(LIB_NAME).a examples done

	

$(LIB_NAME).a: $(OBJECTS)

	@echo " "
	@echo "| -------------------------------------"
	@echo "making static library..."
	$(AR) rc $(LIB_NAME).a $(OBJECTS)



install:
	@echo " "
	@echo "| -------------------------------------"
	@echo "| installing lib"
	@mv $(LIB_NAME).a $(SDK_DIR)/lib/$(LIB_NAME).a

CLAYER:
	@echo "| make C_Layer:" 
	@cd examples
	@make

clean:
	@echo " "
	@echo "| -------------------------------------"
	@echo "| clean"
	@rm $(OBJECTS)

examples:
	@echo " "
	@echo "| -------------------------------------"
	@echo "| make examples"
	$(MAKE) -C examples


%.o : %.cpp Makefile
	@echo " "
	@echo "| -------------------------------------"
	@echo "|  compiling: " $@
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<

done:
	@echo " "
	@echo "| ----------------------------------- |"
	@echo "|                 DONE!               |"
	@echo "| ----------------------------------- |"