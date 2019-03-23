ASM_SRCS = asm/main.c \
			asm/parse_lines.c \
			asm/read_file.c \
			asm/error.c \
			asm/op.c
COREWAR_SRCS =
INCLUDES = libft/includes/libft.h \
		ft_printf/includes/ft_printf.h \
		includes/op.h \
		includes/asm.h \
#		includes/cpu.h \
		includes vm.h
ASM_OBJS = $(patsubst %.c,obj/%.o,$(ASM_SRCS))
COREWAR_OBJS = $(patsubst %.c,obj/%.o,$(COREWAR_SRCS))

TESTS_SRCS =
TESTS = $(patsubst %.c,tests/%.test,$(TESTS_SRCS))
TESTS_DBG_FOLDERS = $(TESTS:.test=.test.dSYM)

CC = gcc
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror #-std=c89
endif
INCLUDE_FOLDERS = -Iincludes/ -Ilibft/includes -Ift_printf/includes
LIBRARY_PATHS = -L. -Llibft -Lft_printf
ASM_NAME = asm
COREWAR_NAME =

.PHONY: clean fclean re all

all: $(ASM_NAME) $(TESTS) $(COREWAR_NAME)

LIBFT_PREFIX = ../libft
FTPRINTF_PREFIX = ft_printf
include ft_printf/Makefile.mk
LIBFT_PREFIX = libft
include libft/Makefile.mk

$(ASM_NAME): $(ASM_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(ASM_OBJS) -o $@ $(LIBRARY_PATHS) -lftprintf -lft

$(COREWAR_NAME): $(COREWAR_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS) -lftprintf -lft

obj:
	mkdir -p obj
	mkdir -p obj/asm
	mkdir -p obj/corewar

tests/%.test: tests/%.c $(NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATHS) -o $@ $< -lft

obj/asm/%.o: src/asm/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -c $< -o $@

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

clean:
	rm -rf $(TESTS_DBG_FOLDERS)
	rm -f $(TESTS)
	rm -f $(COREWAR_OBJS)
	rm -f $(ASM_OBJS)
	rm -rf obj
	rm -f $(LIBFT_OBJS)
	rm -rf libft/obj
	rm -f $(FTPRINTF_OBJS)
	rm -rf ft_printf/obj

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(FTPRINTF_NAME)
	rm -rf $(COREWAR_NAME).dSYM/
	rm -f $(COREWAR_NAME)
	rm -rf $(ASM_NAME).dSYM/
	rm -f $(ASM_NAME)

re: fclean
	$(MAKE) all
