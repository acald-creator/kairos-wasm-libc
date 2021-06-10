KAIROS_CC = clang
KAIROS_CFLAGS = -O2
KAIROS_TARGET_FLAGS = --target=wasm32
SYSROOT = sysroot

DIR = src
INC = src/include
LIBC_DIR = $(DIR)/libc
LIBC_SOURCES = $(LIBC_DIR)/string.c

.PHONY: $(SYSROOT)

$(SYSROOT):
	$(RM) -r "$(SYSROOT)"
	mkdir -p "$(SYSROOT)/usr"

	cp -r "$(INC)" "$(SYSROOT)/usr"

	$(RM) *.o

	"$(KAIROS_CC)" $(KAIROS_CFLAGS) $(KAIROS_TARGET_FLAGS) --sysroot="$(SYSROOT)" -c $(LIBC_DIR)/crt*.s
	mkdir -p "$(SYSROOT)/lib"
	mv *.o "$(SYSROOT)/lib"

	$(RM) *.o
	"$(KAIROS_CC)" $(KAIROS_CFLAGS) $(KAIROS_TARGET_FLAGS) --sysroot="$(SYSROOT)" -c $(LIBC_SOURCES) -I $(INC)
	mkdir -p "$(SYSROOT)/lib"
	llvm-ar crs "$(SYSROOT)/lib/libc.a" *.o
	$(RM) *.o