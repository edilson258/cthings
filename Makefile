CC = clang
CFLAGS = -std=c23 -Wall -Werror -pedantic -ggdb
SRCDIR = src
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
LIBS = -lpthread -lm

SRCS := $(shell find $(SRCDIR) -name '*.c')
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: mpsc

mpsc: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILDDIR) mpsc

.PHONY: all clean
