# Reference: https://stackoverflow.com/a/30602701/10013227

BUILDDIR := bin

# https://stackoverflow.com/a/51156408/10013227
define c2o
$(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(1)))
endef

SRCS := $(wildcard *.c util/*.c)
OBJS := $(call c2o,$(SRCS))


all: $(BUILDDIR) | main.exe

main.exe: $(OBJS)
	gcc $^ -o $@

$(BUILDDIR):
	mkdir $@

$(BUILDDIR)/%.o: %.c
	gcc -O2 -c $^ -o $@

$(BUILDDIR)/%.o: util/%.c
	gcc -O2 -c $^ -o $@

.PHONY: all
