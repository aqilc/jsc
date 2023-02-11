# Reference: https://stackoverflow.com/a/30602701/10013227

CC := gcc
CFLAGS := -o2 -g -m64
BUILDDIR := bin

# https://stackoverflow.com/a/51156408/10013227
define c2o
$(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(1)))
endef

# Defines platform specific stuff for dlls
ifeq ($(OS),Windows_NT)
	DLLENDING := .dll
	DLLFLAGS  := -Wl,--subsystem,windows
else
	DLLENDING := .a
	DLLFLAGS  := 
endif
define c2dll
$(patsubst %.c,%$(DLLENDING),$(notdir $(1)))
endef

# Get the O file names from the C files
SRCS := $(wildcard *.c util/*.c)
OBJS := $(call c2o,$(SRCS))

# A lot of backend specific stuff
BACKDEPS := bin/vec.o
BACKSRCS := $(wildcard backends/*.c)
BACKOBJS := $(call c2o,$(BACKSRCS))
BACKDLLS := $(call c2dll,$(BACKSRCS))

# Require the build folder to be done first, DK if this is the right way but it works for now
all: $(BUILDDIR) | main.exe $(BACKDLLS)
back: $(BUILDDIR) | $(BACKDLLS)

main.exe: $(OBJS)
	$(CC) $^ -o $@

%$(DLLENDING): $(BUILDDIR)/%.o $(BACKDEPS)
	gcc -o $@ $(BACKDEPS) -s -shared $< $(DLLFLAGS)

# Create build dir
$(BUILDDIR):
	mkdir $@

# Build base dir c files
$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

# Build util dir
$(BUILDDIR)/%.o: util/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

# Build backends dir
$(BUILDDIR)/%.o: backends/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rmdir /s /q $(BUILDDIR)
	del main.exe
	del *.dll

.PHONY: all clean
