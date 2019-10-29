# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 18:33:42 by vrichese          #+#    #+#              #
#    Updated: 2019/10/29 19:58:42 by vrichese         ###   ########.fr        #
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

VM_SOURCE		:=		cw_carriage_object.c	\
						cw_command_object.c		\
						cw_buffer_object.c		\
						cw_player_object.c		\
						cw_arena_object.c		\
						cw_error_object.c		\
						cw_game_object.c		\
						cw_callback.c			\
						cw_queue_object.c		\
						cw_stack_object.c		\
						cw_main.c

VIS_SOURCE		:=		cr_vis_buildmap.c	\
						cr_vis_control.c	\
						cr_vis_init.c		\
						cr_vis_main.c		\
						cr_vis_printinfo.c	\
						cr_vis_updatemap.c	\
						cr_vis_printcar.c	\


VM_HEADERS		:=		cwCarriageObject.h	\
						cwCommandObject.h	\
						cwBufferObject.h	\
						cwPlayerObject.h	\
						cwArenaObject.h		\
						cwGameObject.h		\
						cwTypedefObjects.h	\
						cwQueueObject.h		\
						cwStackObject.h		\
						corewar.h

VIS_HEADER		:=		cr_vis.h

OBJ				:=		$(VM_SOURCE:.c=.o)
VIS_OBJ			:=		$(VIS_SOURCE:.c=.o)
OBJ_WITH_DIR	:=		$(addprefix $(DIR_BIN), $(OBJ) $(VIS_OBJ))

LIBFT			:=		libft.a
LIBFTPRINTF		:=		libftprintf.a

vpath %.c $(VM_DIR_SOURCE) $(VM_DIR_SOURCE)/game_obj		\
							$(VM_DIR_SOURCE)/arena_obj		\
							$(VM_DIR_SOURCE)/buffer_obj		\
							$(VM_DIR_SOURCE)/callbacks		\
							$(VM_DIR_SOURCE)/carriage_obj	\
							$(VM_DIR_SOURCE)/command_obj	\
							$(VM_DIR_SOURCE)/player_obj		\
							$(VM_DIR_SOURCE)/rest
vpath %.c $(VIS_DIR_SOURCE)
vpath %.h $(VM_DIR_INCLUDE)
vpath %.h $(VIS_DIR_INCLUDE)
vpath %.o $(DIR_BIN)
vpath %.a $(DIR_LIBFT) $(DIR_PRINTF)

all: $(NAME)

$(NAME): $(OBJ) $(VIS_OBJ) $(LIBFT) $(LIBFTPRINTF)
	gcc $(OBJ_WITH_DIR) -lncurses -o $@ $(DIR_LIBFT)$(LIBFT) $(DIR_PRINTF)$(LIBFTPRINTF)

$(OBJ):%.o:%.c $(VM_HEADERS) | $(DIR_BIN)
	gcc -g -I $(DIR_LIBFT)includes -I $(DIR_PRINTF)includes -I $(VM_DIR_INCLUDE) -I $(VIS_DIR_INCLUDE) -c $< -o $(DIR_BIN)$@

$(VIS_OBJ):%.o:%.c $(VIS_HEADER)
	gcc -g -I $(DIR_LIBFT)includes -I $(DIR_PRINTF)includes -I $(VM_DIR_INCLUDE) -I $(VIS_DIR_INCLUDE)  -c $< -o $(DIR_BIN)$@

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
