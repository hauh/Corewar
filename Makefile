# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 18:33:42 by vrichese          #+#    #+#              #
#    Updated: 2019/09/24 18:25:55 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		corewar

DIR_PRINTF		:=		ft_printf/
DIR_LIBFT		:=		libft/
DIR_SOURCE		:=		source/
DIR_INCLUDE		:=		include/
DIR_BIN			:=		bin/

SOURCE			:=		arena_manager.c \
						cr_vis_buildmap.c \
						cr_vis_printinfo.c \
						memory_manager.c \
						carriage_manager.c \
						cr_vis_control.c \
						cr_vis_updatemap.c \
						player_manager.c \
						command_manager.c \
						cr_vis_init.c \
						error_manager.c \
						support_commands.c \
						corewar.c \
						cr_vis_main.c \
						game_on.c

HEADERS			:=		corewar.h op.h

OBJ				:=		$(SOURCE:.c=.o)
OBJ_WITH_DIR	:=		$(addprefix $(DIR_BIN), $(OBJ))

LIBFT			:=		libft.a
LIBFTPRINTF		:=		libftprintf.a

vpath %.c $(DIR_SOURCE)
vpath %.h $(DIR_INCLUDE)
vpath %.o $(DIR_BIN)
vpath %.a $(DIR_LIBFT) $(DIR_PRINTF)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBFTPRINTF)
	gcc $(OBJ_WITH_DIR) -lncurses -o $@ $(DIR_LIBFT)$(LIBFT) $(DIR_PRINTF)$(LIBFTPRINTF)

$(OBJ):%.o:%.c $(HEADERS) | $(DIR_BIN)
	gcc -g -I $(DIR_LIBFT)includes -I $(DIR_PRINTF)includes -I $(DIR_INCLUDE) -c $< -o $(DIR_BIN)$@

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
.SILENT: all $(NAME) $(OBJ) $(DIR_BIN) $(LIBFT) $(LIBFTPRINTF) clean fclean re