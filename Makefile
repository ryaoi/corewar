CORELIB_SRCS = logging.c \
	logging_save.c \
	optable.c \
	vm/vm.c \
	vm/vm_memory.c \
	vm/ocp.c \
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
ASM_SRCS = optable.c \
	asm/main.c \
	asm/files_utils.c \
	asm/file_parse.c \
	asm/file_parse_utils.c \
	asm/file_parse_check.c \
	asm/file_parse_tokenizer.c \
	asm/file_parse_header.c \
	asm/bytecode_length.c \
	asm/file_read.c \
	asm/file_read_utils.c \
	asm/file_conversion.c \
	asm/file_conversion_traslate_bc.c \
	asm/print_errors.c \
	asm/write_cor_file.c \
	asm/free_asm.c
COREWAR_SRCS = 	vm/visualizer/visualizer.c \
	vm/visualizer/memory_dump.c \
	vm/visualizer/info.c \
	vm/main.c \
	vm/visualizer/colors.c \
	vm/visualizer/key_inputs.c \
	vm/visualizer/visualizer_utils.c \
	vm/prepare_game/parse_cmd.c \
	vm/prepare_game/syntax_check_flags.c \
	vm/prepare_game/syntax_check_inputs.c \
	vm/prepare_game/get_infos.c \
	vm/prepare_game/parse_cmd_utils.c \
	vm/prepare_game/flags_utils.c \
	vm/stdout_messages.c
INCLUDES = libft/includes/libft.h \
		libft/includes/array.h \
		libft/includes/ft_assert.h \
		ft_printf/includes/ft_printf.h \
		includes/instr.h \
		includes/vm.h \
		includes/visualizer.h \
		includes/cmd_line.h \
		includes/asm.h
CORELIB_OBJS = $(patsubst %.c,obj/%.o,$(CORELIB_SRCS))
ASM_OBJS = $(patsubst %.c,obj/%.o,$(ASM_SRCS))
COREWAR_OBJS = $(patsubst %.c,obj/%.o,$(COREWAR_SRCS))

CC = gcc
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror -std=c89
export LDFLAGS := $(LDFLAGS)
endif
INCLUDE_FOLDERS = -Iincludes/ -Ilibft/includes -Ift_printf/includes
LIBRARY_PATHS = -L. -Llibft -Lft_printf
ASM_NAME = asm
COREWAR_NAME = corewar
CORELIB_NAME = libcore.so

.PHONY: clean fclean re all

all: $(CORELIB_NAME) $(COREWAR_NAME) $(ASM_NAME)

LIBFT_PREFIX = ../libft
FTPRINTF_PREFIX = ft_printf
include ft_printf/Makefile.mk
LIBFT_PREFIX = libft
include libft/Makefile.mk

$(CORELIB_NAME): $(CORELIB_OBJS) $(FTPRINTF_NAME) $(LIBFT_NAME)
	gcc $(LDFLAGS) -shared -o $@ $^

$(ASM_NAME): $(ASM_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(ASM_OBJS) -o $@ $(LIBRARY_PATHS) -lftprintf -lft -lcore

$(COREWAR_NAME): $(CORELIB_NAME) $(COREWAR_OBJS)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(COREWAR_OBJS) -o $@ $(LIBRARY_PATHS) -lncurses -lcore -lft

obj:
	mkdir -p obj
	mkdir -p obj/vm
	mkdir -p obj/asm
	mkdir -p obj/vm/instr_impl
	mkdir -p obj/vm/visualizer
	mkdir -p obj/vm/prepare_game

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) -fpic $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

clean:
	rm -f $(COREWAR_OBJS)
	rm -f $(ASM_OBJS)
	rm -f $(core_OBJS)
	rm -rf obj
	rm -f $(LIBFT_OBJS)
	rm -rf libft/obj
	rm -f $(FTPRINTF_OBJS)
	rm -rf ft_printf/obj

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(FTPRINTF_NAME)
	rm -f $(COREWAR_NAME)
	rm -f $(CORELIB_NAME)
	rm -f $(ASM_NAME)
	rm -f $(VISUALIZER_NAME)
	rm -rf $(VISUALIZER_NAME).dSYM/

re: fclean
	$(MAKE) all
