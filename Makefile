# Reference: https://stackoverflow.com/a/30602701/10013227

CC := gcc
CFLAGS := -o2 -g
BUILDDIR := bin

# https://stackoverflow.com/a/51156408/10013227
define c2o
$(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(1)))
endef

# Get the O file names from the C files
SRCS := $(wildcard *.c util/*.c)
OBJS := $(call c2o,$(SRCS))


# Require the build folder to be done first, DK if this is the right way but it works for now
all: $(BUILDDIR) | main.exe

main.exe: $(OBJS)
	$(CC) $^ -o $@

# Create build dir
$(BUILDDIR):
	mkdir $@

# Build base dir c files
$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

# Build util dir
$(BUILDDIR)/%.o: util/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rmdir /s /q $(BUILDDIR)
	del main.exe

.PHONY: all clean
