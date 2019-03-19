CORELIB_SRCS = vm/vm.c \
	vm/ocp.c \
	vm/optable.c \
	vm/load_store.c \
	vm/instr_init.c \
	vm/control_unit.c \
	vm/champion_load.c \
	vm/byte_order.c \
	vm/instr_impl/buffer_invert_bits.c \
	vm/instr_impl/buffer_is_zero.c \
	vm/instr_impl/impl_add.c \
	vm/instr_impl/impl_aff.c \
	vm/instr_impl/impl_ld.c \
	vm/instr_impl/impl_ldi.c \
	vm/instr_impl/impl_live.c \
	vm/instr_impl/impl_st.c \
	vm/instr_impl/impl_sub.c \
	vm/instr_impl/impl_zjmp.c
ASM_SRCS =
COREWAR_SRCS =
INCLUDES = libft/includes/libft.h \
		ft_printf/includes/ft_printf.h \
		includes/instr.h \
		includes/vm.h
CORELIB_OBJS = $(patsubst %.c,obj/%.o,$(CORELIB_SRCS))
ASM_OBJS = $(patsubst %.c,obj/%.o,$(ASM_SRCS))
COREWAR_OBJS = $(patsubst %.c,obj/%.o,$(COREWAR_SRCS))

TESTS_SRCS = champload.c
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
CORELIB_NAME = libcore.so

.PHONY: clean fclean re all

all: $(CORELIB_NAME) $(COREWAR_NAME) $(ASM_NAME) $(TESTS)

LIBFT_PREFIX = ../libft
FTPRINTF_PREFIX = ft_printf
include ft_printf/Makefile.mk
LIBFT_PREFIX = libft
include libft/Makefile.mk

$(CORELIB_NAME): $(CORELIB_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	gcc -shared -o $@ $^

$(ASM_NAME): $(CORELIB_NAME) $(ASM_OBJS)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS)  -lcore

$(COREWAR_NAME): $(CORELIB_NAME) $(COREWAR_OBJS)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS) -lcore

obj:
	mkdir -p obj
	mkdir -p obj/vm
	mkdir -p obj/vm/instr_impl

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) -fpic $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

tests/%.test: tests/%.c $(CORELIB_NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATHS) -o $@ $< -lcore

clean:
	rm -rf $(TESTS_DBG_FOLDERS)
	rm -f $(TESTS)
	rm -f $(COREWAR_OBJS)
	rm -f $(ASM_OBJS)
	rm -f  $(core_OBJS)
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
