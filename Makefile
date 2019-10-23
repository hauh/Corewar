# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 18:33:42 by vrichese          #+#    #+#              #
#    Updated: 2019/10/23 20:24:13 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		corewar

DIR_PRINTF		:=		ft_printf/
DIR_LIBFT		:=		libft/
DIR_SOURCE		:=		source/
DIR_INCLUDE		:=		include/
DIR_BIN			:=		bin/

SOURCE			:=		cwArenaObject.c \
							cwCallback.c \
							cwCarriageObject.c \
							cwCommandObject.c \
							cwErrorObject.c\
							cwGameObject.c\
							cw_main.c\
							cwPlayerObject.c\
							cwBufferObject.c\

HEADERS			:=		corewar.h cwArenaObject.h cwCarriageObject.h

OBJ				:=		$(SOURCE:.c=.o)
OBJ_WITH_DIR	:=		$(addprefix $(DIR_BIN), $(OBJ) $(VIS_OBJ))

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
