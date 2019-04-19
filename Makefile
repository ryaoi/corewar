CORELIB_SRCS = python_bindings/python_bindings.c \
	python_bindings/python_impl.c \
	logging.c \
	vm/vm.c \
	vm/ocp.c \
	vm/optable.c \
	vm/load_store.c \
	vm/instr_init.c \
	vm/control_unit.c \
	vm/champion_load.c \
	vm/byte_order.c \
	vm/clone_process.c \
	vm/process_cycle.c \
	vm/game.c \
	vm/util.c \
	vm/buffer_invert_bits.c \
	vm/buffer_is_zero.c \
	vm/instr_impl/impl_and.c \
	vm/instr_impl/impl_or.c \
	vm/instr_impl/impl_xor.c \
	vm/instr_impl/impl_add.c \
	vm/instr_impl/impl_aff.c \
	vm/instr_impl/impl_ld.c \
	vm/instr_impl/impl_ldi.c \
	vm/instr_impl/impl_live.c \
	vm/instr_impl/impl_st.c \
	vm/instr_impl/impl_sti.c \
	vm/instr_impl/impl_sub.c \
	vm/instr_impl/impl_zjmp.c \
	vm/instr_impl/impl_fork.c \
	vm/instr_impl/impl_lld.c \
	vm/instr_impl/impl_lldi.c \
	vm/instr_impl/impl_lfork.c
ASM_SRCS =
COREWAR_SRCS = 	vm/visualizer/visualizer.c \
	vm/visualizer/memory_dump.c \
	vm/visualizer/info.c \
	vm/visualizer/visualizer_backup.c
INCLUDES = libft/includes/libft.h \
		libft/includes/array.h \
		libft/includes/ft_assert.h \
		ft_printf/includes/ft_printf.h \
		includes/instr.h \
		includes/vm.h \
		includes/visualizer.h \
		includes/python_bindings.h
CORELIB_OBJS = $(patsubst %.c,obj/%.o,$(CORELIB_SRCS))
ASM_OBJS = $(patsubst %.c,obj/%.o,$(ASM_SRCS))
COREWAR_OBJS = $(patsubst %.c,obj/%.o,$(COREWAR_SRCS))

TESTS_SRCS = short_game.c \
	complete_game.c \
	invalid_champ.c
TESTS = $(patsubst %.c,tests/%.test,$(TESTS_SRCS))
TESTS_DBG_FOLDERS = $(TESTS:.test=.test.dSYM)

CC = gcc
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror #-std=c89
export LDFLAGS := $(LDFLAGS)
endif
INCLUDE_FOLDERS = -Iincludes/ -Ilibft/includes -Ift_printf/includes
LIBRARY_PATHS = -L. -Llibft -Lft_printf
ASM_NAME =
COREWAR_NAME = corewar
CORELIB_NAME = libcore.so

.PHONY: clean fclean re all

all: $(CORELIB_NAME) $(COREWAR_NAME) $(ASM_NAME) $(TESTS)

LIBFT_PREFIX = ../libft
FTPRINTF_PREFIX = ft_printf
include ft_printf/Makefile.mk
LIBFT_PREFIX = libft
include libft/Makefile.mk

$(CORELIB_NAME): $(CORELIB_OBJS) $(FTPRINTF_NAME) $(LIBFT_NAME)
	gcc $(LDFLAGS) -shared -o $@ $^ `pkg-config python3 --libs`

$(ASM_NAME): $(CORELIB_NAME) $(ASM_OBJS)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(ASM_OBJS) -o $@ $(LIBRARY_PATHS)  -lcore

$(COREWAR_NAME): $(CORELIB_NAME) $(COREWAR_OBJS)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(COREWAR_OBJS) -o $@ $(LIBRARY_PATHS) -lncurses -lcore

obj:
	mkdir -p obj
	mkdir -p obj/vm
	mkdir -p obj/vm/instr_impl
	mkdir -p obj/vm/visualizer
	mkdir -p obj/python_bindings

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) -fpic $(CFLAGS) $(INCLUDE_FOLDERS) `pkg-config python3 --cflags` -o $@ -c $<

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
