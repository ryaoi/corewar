CORELIB_SRCS =
ASM_SRCS =
COREWAR_SRCS =
INCLUDES = libft/includes/libft.h \
		ft_printf/includes/ft_printf.h \
		includes/adjacency_list.h \
		includes/algorithm.h \
		includes/lem_in.h \
		includes/parser.h \
		includes/visualizer.h
CORELIB_OBJS = $(patsubst %.c,obj/%.o,$(CORELIB_SRCS))
ASM_OBJS = $(patsubst %.c,obj/%.o,$(ASM_SRCS))
COREWAR_OBJS = $(patsubst %.c,obj/%.o,$(COREWAR_SRCS))

TESTS_SRCS =
TESTS = $(patsubst %.c,tests/%.test,$(TESTS_SRCS))
TESTS_DBG_FOLDERS = $(TESTS:.test=.test.dSYM)

CC = gcc
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror -std=c89
endif
INCLUDE_FOLDERS = -Iincludes/ -Ilibft/includes -Ift_printf/includes
LIBRARY_PATHS = -L. -Llibft -Lft_printf
ASM_NAME =
COREWAR_NAME =
CORELIB_NAME =

.PHONY: clean fclean re all

all: $(CORELIB_NAME) $(COREWAR_NAME) $(ASM_NAME) $(TESTS)

LIBFT_PREFIX = ../libft
FTPRINTF_PREFIX = ft_printf
include ft_printf/Makefile.mk
LIBFT_PREFIX = libft
include libft/Makefile.mk

$(CORELIB_NAME): $(CORELIB_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	libtool -dynamic -o $@ $^

$(ASM_NAME): $(CORELIB_NAME) $(ASM_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS)  -lcorelib

$(COREWAR_NAME): $(CORELIB_NAME) $(COREWAR_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS) -lcorelib

obj:
	mkdir -p obj

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

tests/%.test: tests/%.c $(CORELIB_NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATHS) -o $@ $< -lft

clean:
	rm -rf $(TESTS_DBG_FOLDERS)
	rm -f $(TESTS)
	rm -f $(COREWAR_OBJS)
	rm -f $(ASM_OBJS)
	rm -f  $(CORELIB_OBJS)
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
	rm -f $(CORELIB_NAME)
	rm -rf $(ASM_NAME).dSYM/
	rm -f $(ASM_NAME)

re: fclean
	$(MAKE) all
