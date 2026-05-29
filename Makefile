ifneq ($(OS),Windows_NT)
    PLAT := $(shell uname -s | tr '[:upper:]' '[:lower:]')
else
    PLAT := win32
endif

SRCDIR ?= src
OBJDIR ?= obj
OUTDIR ?= .

SYSROOT ?= /usr
SYSBIN ?= $(SYSROOT)/bin

ifneq ($(DEBUG),y)
    OBJDIR := $(OBJDIR)/release
else
    OBJDIR := $(OBJDIR)/debug
    ifeq ($(ASAN),y)
        OBJDIR := $(OBJDIR)_asan
    endif
endif

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

BIN := $(OUTDIR)/fabricate
ifeq ($(PLAT),win32)
    BIN := $(BIN).exe
endif

CC ?= gcc
LD := $(CC)
_CC := $(TOOLCHAIN)$(CC)
_LD := $(TOOLCHAIN)$(LD)

_CFLAGS := $(CFLAGS) -std=c99 -Wall -Wextra -Wuninitialized -Wundef
_CPPFLAGS := $(CPPFLAGS)
_LDFLAGS := $(LDFLAGS)
_LDLIBS := $(LDLIBS)

ifneq ($(DEBUG),y)
    _CPPFLAGS += -DNDEBUG
else
    _CFLAGS += -g -Wdouble-promotion
    O ?= g
    ifeq ($(ASAN),y)
        _CFLAGS += -fsanitize=address -fno-omit-frame-pointer
        _LDFLAGS += -fsanitize=address
    endif
endif
_CFLAGS += -O$(O)

.SECONDEXPANSION:

define mkdir
if [ ! -d '$(1)' ]; then echo 'Creating $(1)/...'; mkdir -p '$(1)'; fi; true
endef
define rm
if [ -f '$(1)' ]; then echo 'Removing $(1)...'; rm -f '$(1)'; fi; true
endef
define rmdir
if [ -d '$(1)' ]; then echo 'Removing $(1)/...'; rm -rf '$(1)'; fi; true
endef

deps.filter := %.c %.h
deps.option := -MM
define deps
$$(filter $$(deps.filter),,$$(shell $(_CC) $(CFLAGS) $(CPPFLAGS) -E $(deps.option) $(1)))
endef

build: $(BIN)
	@:

$(OUTDIR) $(OBJDIR):
	@$(call mkdir,$@)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(call deps,$(SRCDIR)/%.c) | $(OBJDIR)
	@echo Compiling $<...
	@$(_CC) -c $(_CFLAGS) $(_CPPFLAGS) $< -o $@
	@echo Compiled $<

$(BIN): $(OBJECTS) | $(OUTDIR)
	@echo Linking $@...
	@$(_LD) $(_LDFLAGS) $^ $(_LDLIBS) -o $@
	-@cd -- $(OUTDIR); [ -e fab ] || ln -s -- fabricate fab
	@echo Linked $@

clean:
	@$(call rmdir,$(OBJDIR))

distclean: clean
	@$(call rm,$(BIN))

.PHONY: build clean distclean
