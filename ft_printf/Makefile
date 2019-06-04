SRCS = ft_printf.c \
		ft_dprintf.c \
		ft_snprintf.c \
		parser.c \
		handler_percent.c \
		handler_s_dec.c \
		handler_u_dec.c \
		handler_u_oct.c \
		handler_u_hex.c \
		handler_u_bin.c \
		handler_u_char.c \
		handler_string.c \
		handler_pointer.c \
		handler_float.c \
		util.c \
		print_util.c \
		integer_util.c \
		float_util.c \
		bigint_math.c \
		bigint/bigint_bitshift.c \
		bigint/bigint_util.c \
		bigint/bigint_sum.c \
		bigint/bigint_mul.c \
		bigint/bigint_div.c
INCLUDES = includes/ft_printf.h \
     	includes/handler_float.h \
		includes/bigint.h \
		$(LIBFT_PREFIX)/includes/libft.h
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))

TESTS_SRCS =
TESTS = $(patsubst %.c,tests/%.test,$(TESTS_SRCS))
TESTS_DBG_FOLDERS = $(TESTS:.test=.test.dSYM)

CC = gcc
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror
endif
INCLUDE_FOLDERS = -Iincludes/ -I$(LIBFT_PREFIX)/includes
LIBRARY_PATHS = -L. -L$(LIBFT_PREFIX)
NAME = libftprintf.a

.PHONY: clean fclean re all

all: $(NAME) $(TESTS)


include Prefix.mk
include $(LIBFT_PREFIX)/Makefile.mk

$(NAME): $(OBJS)
	ar rcs $@ $^

obj:
	mkdir -p obj
	mkdir -p obj/bigint

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

tests/%.test: tests/%.c $(NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATHS) -o $@ $< -lftprintf -lft

clean:
	rm -rf $(TESTS_DBG_FOLDERS)
	rm -f $(TESTS)
	rm -f $(OBJS)
	rm -rf obj
	rm -f $(LIBFT_OBJS)
	rm -rf libft/obj

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(NAME)

re: fclean
	$(MAKE) all
