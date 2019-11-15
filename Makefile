# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 18:33:42 by vrichese          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/11/15 15:08:29 by dbrady           ###   ########.fr        #
=======
#    Updated: 2019/11/15 16:01:13 by vrichese         ###   ########.fr        #
>>>>>>> ad13a51951a1eabb10d05690b150c92ef6e17131
#                                                                              #
# **************************************************************************** #

NAME			:=		corewar

DIR_PRINTF		:=		ft_printf/
DIR_LIBFT		:=		libft/
VM_DIR_SOURCE	:=		source/VM
VIS_DIR_SOURCE	:=		source/VIS
VM_DIR_INCLUDE	:=		include/VM
VIS_DIR_INCLUDE :=		include/VIS
DIR_BIN			:=		bin/

VM_SOURCE		:=		cw_process_obj.c						\
							cw_process_prepare_functions.c		\
							cw_process_movements_functions.c	\
							cw_process_read_write_functions.c	\
							cw_process_registers.c				\
						cw_command_obj.c						\
							cw_command_functions.c				\
						cw_buffer_obj.c							\
							cw_buffer_functions.c				\
						cw_player_obj.c							\
							cw_player_functions.c				\
						cw_arena_obj.c							\
							cw_arena_functions.c				\
						cw_error_manager.c						\
						cw_game_object.c						\
							cw_game_functions.c					\
							cw_game_essence_init.c				\
							cw_game_process.c					\
						cw_and_or_xor_zjmp_ldi.c				\
						cw_live_ld_st_add_sub.c					\
						cw_sti_fork_lld_lldi_lfork.c			\
						cw_aff.c								\
						cw_scheduler_object.c					\
							cw_scheduler_functions.c			\
							cw_scheduler_insertion.c			\
								cw_queue_obj.c					\
								cw_queue_functions.c			\
								cw_queue_avl_tree_functions.c	\
						cw_main.c

VIS_SOURCE		:=		cr_vis_box.c		\
						cr_vis_buildmap.c	\
						cr_vis_control.c	\
						cr_vis_init.c		\
						cr_vis_main.c		\
						cr_vis_printcar.c	\
						cr_vis_printhealth.c\
						cr_vis_printinfo.c	\
						cr_vis_sound.c		\
						cr_vis_updatemap.c	\
						cr_vis_welcomescr.c \


VM_HEADERS		:=		cw_process_obj.h	\
						cw_command_obj.h	\
						cw_buffer_obj.h		\
						cw_player_obj.h		\
						cw_arena_obj.h		\
						cw_game_obj.h		\
						cw_queue_obj.h		\
						cw_obj_container.h	\
						cw_scheduler_obj.h	\
						corewar.h

VIS_HEADER		:=		cr_vis.h

OBJ				:=		$(VM_SOURCE:.c=.o)
VIS_OBJ			:=		$(VIS_SOURCE:.c=.o)
OBJ_WITH_DIR	:=		$(addprefix $(DIR_BIN), $(OBJ) $(VIS_OBJ))

FLAGS			:=		-O3 -Wall -Werror -Wextra -g

LIBFT			:=		libft.a
LIBFTPRINTF		:=		libftprintf.a

vpath %.c $(VM_DIR_SOURCE)	$(VM_DIR_SOURCE)/game_obj						\
							$(VM_DIR_SOURCE)/arena_obj						\
							$(VM_DIR_SOURCE)/buffer_obj						\
							$(VM_DIR_SOURCE)/callbacks						\
							$(VM_DIR_SOURCE)/process_obj					\
							$(VM_DIR_SOURCE)/command_obj					\
							$(VM_DIR_SOURCE)/player_obj						\
							$(VM_DIR_SOURCE)/scheduler_obj					\
								$(VM_DIR_SOURCE)/scheduler_obj/queue_obj	\
							$(VM_DIR_SOURCE)/rest							\
vpath %.c $(VIS_DIR_SOURCE)
vpath %.h $(VM_DIR_INCLUDE)
vpath %.h $(VIS_DIR_INCLUDE)
vpath %.o $(DIR_BIN)
vpath %.a $(DIR_LIBFT) $(DIR_PRINTF)

all: $(NAME)

$(NAME): $(OBJ) $(VIS_OBJ) $(LIBFT) $(LIBFTPRINTF)
	gcc $(FLAGS) $(OBJ_WITH_DIR) -lncurses -o $@ $(DIR_LIBFT)$(LIBFT) $(DIR_PRINTF)$(LIBFTPRINTF)
	clear
	printf "\r\e[J\e[33m"
	bash .output.sh
	printf "\e[0m\e[?25h"

$(OBJ):%.o:%.c $(VM_HEADERS) | $(DIR_BIN)
	gcc $(FLAGS) -I $(DIR_LIBFT)includes -I $(DIR_PRINTF)includes -I $(VM_DIR_INCLUDE) -I $(VIS_DIR_INCLUDE) -c $< -o $(DIR_BIN)$@
	printf "\r\e[?25l\e[JCompiling \e[35m$(notdir $<)\e[0m"

$(VIS_OBJ):%.o:%.c $(VIS_HEADER)
	gcc $(FLAGS) -I $(DIR_LIBFT)includes -I $(DIR_PRINTF)includes -I $(VM_DIR_INCLUDE) -I $(VIS_DIR_INCLUDE)  -c $< -o $(DIR_BIN)$@
	printf "\r\e[?25l\e[JCompiling \e[35m$(notdir $<)\e[0m"

$(DIR_BIN):
	mkdir -p $@

$(LIBFT):
	make -C $(DIR_LIBFT)

$(LIBFTPRINTF):
	make -C $(DIR_PRINTF)

clean:
	rm -rf $(OBJ_WITH_DIR)
	rm -rf $(DIR_BIN)
	make -C $(DIR_LIBFT) clean
	make -C $(DIR_PRINTF) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(DIR_LIBFT) fclean
	make -C $(DIR_PRINTF) fclean

re: fclean all

.PHONY: clean fclean re
.SILENT: all $(NAME) $(OBJ) $(VIS_OBJ) $(DIR_BIN) $(LIBFT) $(LIBFTPRINTF) clean fclean re
