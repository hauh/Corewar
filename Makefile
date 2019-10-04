# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 18:33:42 by vrichese          #+#    #+#              #
#    Updated: 2019/10/03 18:14:55 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		corewar

DIR_PRINTF		:=		ft_printf/
DIR_LIBFT		:=		libft/
DIR_SOURCE		:=		source/
DIR_VIS			:=		visualizationSource/
DIR_INCLUDE		:=		include/
DIR_BIN			:=		bin/

SOURCE			:=		cwArena.c \
							cwCallback.c \
							cwCarriage.c \
							cwCommand.c \
							cwDestructor.c \
							cwError.c\
							cwGame.c\
							cwKey.c\
							cwMain.c\
							cwMemory.c\
							cwPlayer.c\
							cwLogs.c
VIS_SOURCE		:=		cr_vis_buildmap.c \
							cr_vis_printinfo.c \
							cr_vis_control.c \
							cr_vis_updatemap.c \
							cr_vis_init.c \
							cr_vis_main.c

HEADERS			:=		corewar.h op.h

OBJ				:=		$(SOURCE:.c=.o)
VIS_OBJ			:=		$(VIS_SOURCE:.c=.o)
OBJ_WITH_DIR	:=		$(addprefix $(DIR_BIN), $(OBJ) $(VIS_OBJ))

LIBFT			:=		libft.a
LIBFTPRINTF		:=		libftprintf.a

vpath %.c $(DIR_SOURCE) $(DIR_VIS)
vpath %.h $(DIR_INCLUDE)
vpath %.o $(DIR_BIN)
vpath %.a $(DIR_LIBFT) $(DIR_PRINTF)

all: $(NAME)

$(NAME): $(OBJ) $(VIS_OBJ) $(LIBFT) $(LIBFTPRINTF)
	gcc $(OBJ_WITH_DIR) -lncurses -o $@ $(DIR_LIBFT)$(LIBFT) $(DIR_PRINTF)$(LIBFTPRINTF)

$(OBJ):%.o:%.c $(HEADERS) | $(DIR_BIN)
	gcc -g -I $(DIR_LIBFT)includes -I $(DIR_PRINTF)includes -I $(DIR_INCLUDE) -c $< -o $(DIR_BIN)$@

$(VIS_OBJ):%.o:%.c $(HEADERS)
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
.SILENT: all $(NAME) $(OBJ) $(VIS_OBJ) $(DIR_BIN) $(LIBFT) $(LIBFTPRINTF) clean fclean re