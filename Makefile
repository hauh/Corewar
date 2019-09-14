# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 16:46:19 by smorty            #+#    #+#              #
#    Updated: 2019/09/14 20:32:44 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM := asm

NAME_GAME := corewar

SRC_DIR := src

OBJ_DIR := obj

LFT_DIR := $(SRC_DIR)/libft

HEADERS_DIR := include $(LFT_DIR)

SRC_ASM := asm.c read_input.c parse_file.c parse_arguments.c analyze.c temp.c

SRC_COREWAR :=

OBJ_ASM := $(SRC_ASM:.c=.o)

LFT := libft.a

HEADERS := asm.h libft.h op.h

CC := gcc -Wall -Werror -Wextra -g

vpath %.c $(SRC_DIR) $(SRC_DIR)/asm $(SRC_DIR)/corewar
vpath %.o $(OBJ_DIR)
vpath %.h $(HEADERS_DIR)
vpath %.a $(LFT_DIR)

all: $(NAME_ASM)

$(NAME_ASM): $(LFT) $(OBJ_ASM)
	@$(CC) $(addprefix $(OBJ_DIR)/, $(OBJ_ASM)) $(INCLUDE) -lft -L $(LFT_DIR) -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(OBJ_ASM): %.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $< $(addprefix -I,$(HEADERS_DIR)) -o $(OBJ_DIR)/$@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

$(LFT):
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(LFT_DIR) clean

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LFT_DIR) fclean

fclean: clean
	@rm -f $(NAME_ASM)
	@rm -f $(NAME_COREWAR)

re: fclean all