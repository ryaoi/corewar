FTPRINTF_SRCS = ft_printf.c \
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
FTPRINTF_INCLUDES = includes/ft_printf.h \
     	includes/handler_float.h \
		includes/bigint.h \
		$(LIBFT_PREFIX)/includes/libft.h
FTPRINTF_OBJS := $(patsubst %.c,obj/%.o,$(FTPRINTF_SRCS))
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror
endif
FTPRINTF_INCLUDE_FOLDERS = includes/ $(LIBFT_PREFIX)/includes
FTPRINTF_NAME = libftprintf.a

FTPRINTF_OBJS := $(addprefix $(FTPRINTF_PREFIX)/,$(FTPRINTF_OBJS))
FTPRINTF_NAME := $(addprefix $(FTPRINTF_PREFIX)/, $(FTPRINTF_NAME))
FTPRINTF_INCLUDES := $(addprefix $(FTPRINTF_PREFIX)/, $(FTPRINTF_INCLUDES))
FTPRINTF_INCLUDE_FOLDERS := $(addprefix -I$(FTPRINTF_PREFIX)/, $(FTPRINTF_INCLUDE_FOLDERS))

$(FTPRINTF_NAME): $(FTPRINTF_OBJS)
	ar rcs $@ $^

$(FTPRINTF_PREFIX)/obj:
	mkdir -p $(FTPRINTF_PREFIX)/obj
	mkdir -p $(FTPRINTF_PREFIX)/obj/bigint

$(FTPRINTF_PREFIX)/obj/%.o: $(FTPRINTF_PREFIX)/src/%.c $(FTPRINTF_INCLUDES) | $(FTPRINTF_PREFIX)/obj
	$(CC) $(CFLAGS) $(FTPRINTF_INCLUDE_FOLDERS) -o $@ -c $<
