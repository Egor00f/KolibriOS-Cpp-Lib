
FASM = fasm

all: $(patsubst   %.asm,%.obj,$(wildcard   *.asm))
	@echo "installing C_Layer"
	@mv $^ ../OBJ
%.obj: %.asm
	@echo "# compiling:"  $@
	$(FASM) $< $%
