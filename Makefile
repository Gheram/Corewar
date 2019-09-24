# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/18 16:12:18 by ghtouman          #+#    #+#              #
#    Updated: 2019/09/18 15:19:25 by ghtouman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAG = -Wall -Werror -Wextra
IDIR = ./includes/
NAME_ASM = asm
NAME_VM = corewar
SRC_PATH = ./srcs/
LIB_PATH = ./libft/
LIB = libft/libft.a
NCURSES = -lncurses

FILES_ASM = 	main_asm.c				\
				open_file.c				\
				errors.c				\
				ft_utile.c				\
				print_error.c			\
				read_header.c			\
				check_header.c			\
				read_body.c				\
				parse_cmd.c				\
				check_cmd.c				\
				check_arg.c				\
				create_corfile.c		\
				corfile_utils_head.c	\
				corfile_utils_body.c	\
				corfile_utils_label.c	\
				clean.c					\
				clean2.c
				
FILES_VM = 		main.c					\
				init_mem.c				\
				init_champ.c			\
				get_champs.c			\
				get_champ_info.c		\
				get_options.c			\
				ft_error.c				\
				swap_int_bit.c			\
				print_mem.c				\
				error_utils.c			\
				error_utils2.c			\
				clean.c					\
				init_processus.c		\
				start.c					\
				update_die_time.c		\
				live.c					\
				ld.c					\
				st.c					\
				add.c					\
				sub.c					\
				and.c					\
				or.c					\
				xor.c					\
				zjmp.c					\
				ldi.c					\
				sti.c					\
				forc.c					\
				lld.c					\
				lldi.c					\
				lfork.c					\
				aff.c					\
				format_args.c			\
				read_in_ram.c			\
				write_in_ram.c			\
				utils.c					\
				print_result.c			\
				print_instr.c			\
				print_movement.c		\
				ncurses/get_x_y.c		\
				ncurses/init_ncurses.c	\
				ncurses/loop_ncurses.c	\
				ncurses/norme_ncurses.c	\
				ncurses/new_write.c		\
				ncurses/fill_win.c

SRCS_FILES_ASM = $(addprefix srcs_asm/, $(FILES_ASM))
SRCS_FILES_VM = $(addprefix srcs_vm/, $(FILES_VM))

OBJ_ASM = $(SRCS_FILES_ASM:.c=.o)
OBJ_VM = $(SRCS_FILES_VM:.c=.o)

all: $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): $(LIB) $(OBJ_ASM)
	$(CC) $(OBJ_ASM) $(LIB) -I $(LIB_PATH) -o $(NAME_ASM) #-fsanitize=address

$(NAME_VM): $(LIB) $(OBJ_VM)
	$(CC) $(OBJ_VM) $(LIB) -I $(LIB_PATH) $(NCURSES) -o $(NAME_VM)

%.o: %.c
	$(CC) -c $(FLAG) $< -o $@ -I$(IDIR)

$(OBJ_ASM) : $(IDIR)asm.h $(IDIR)op.h
$(OBJ_VM) : $(IDIR)vm.h $(IDIR)processus.h $(IDIR)op.h

clean_asm:
	$(RM) $(OBJ_ASM)
fclean_asm: clean_asm
	$(RM) $(NAME_ASM)

clean_vm:
	$(RM) $(OBJ_VM)
fclean_vm: clean_vm
	$(RM) $(NAME_VM)

clean_lib:
	$(MAKE) clean -C $(LIB_PATH)
fclean_lib: clean_lib
	$(RM) $(LIB)

clean: clean_asm clean_vm clean_lib
fclean: fclean_lib fclean_asm fclean_vm

re_asm: fclean_asm asm
re_vm: fclean_vm vm

re: fclean all

libft/libft.a: FORCE
	$(MAKE) -C libft -j

FORCE:

.PHONY: all clean fclean re
