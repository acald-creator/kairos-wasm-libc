KAIROS_CC = clang
KAIROS_CFLAGS = -O2
KAIROS_TARGET_FLAGS = --target=wasm32
SYSROOT = sysroot
THREAD_MODEL = single

AR = llvm-ar
STRIP = llvm-strip
RANLIB = llvm-ranlib
NM = llvm-nm

DIR = src/kairos
INC = $(DIR)/include
LIBC_DIR = $(DIR)/libc
LIBC_SOURCES = $(LIBC_DIR)/string.c
DLMALLOC_DIR = src/dlmalloc
DLMALLOC_SRC_DIR = $(DLMALLOC_DIR)/src
DLMALLOC_SOURCES = $(DLMALLOC_SRC_DIR)/wrapper.c
DLMALLOC_INC = $(DLMALLOC_DIR)/include

ifeq ($(THREADS), single)
KAIROS_CFLAGS += -mthread-model single -DKAIROS_THREAD_MODEL_SINGLE
endif
ifeq ($(THREADS), posix)
KAIROS_CFLAGS += -mthread-model posix -DKAIROS_THREAD_MODEL_POSIX
endif

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

	$(RM) *.o
	"$(KAIROS_CC)" $(KAIROS_CFLAGS) $(KAIROS_TARGET_FLAGS) --sysroot="$(SYSROOT)" -c $(DLMALLOC_SOURCES) -I $(INC) -I $(DLMALLOC_INC)
	mkdir -p "$(SYSROOT)/lib"
	$(AR) crs "$(SYSROOT)/lib/libc-dlmalloc.a" *.o
	$(RM) *.o