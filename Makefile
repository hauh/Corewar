# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 16:46:19 by smorty            #+#    #+#              #
#    Updated: 2019/09/18 23:13:51 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM := asm

NAME_GAME := corewar

SRC_DIR := src

OBJ_DIR := obj

LFT_DIR := $(SRC_DIR)/libft

LFT_PRINTF_DIR := $(SRC_DIR)/ft_printf

HEADERS_DIR := include $(LFT_DIR) $(LFT_PRINTF_DIR)/includes

SRC_ASM := asm.c read_input.c parse_file.c parse_title.c parse_label.c parse_opcode.c parse_parameter.c analyze_sizes.c assemble.c

SRC_COREWAR :=

OBJ_ASM := $(SRC_ASM:.c=.o)

LFT := libft.a

LFT_PRINTF = libftprintf.a

HEADERS := asm.h libft.h ft_printf.h op.h

CC := gcc -Wall -Werror -Wextra

vpath %.c $(SRC_DIR) $(SRC_DIR)/asm $(SRC_DIR)/corewar
vpath %.o $(OBJ_DIR)
vpath %.h $(HEADERS_DIR)
vpath %.a $(LFT_DIR) $(LFT_PRINTF_DIR)

all: $(NAME_ASM)

$(NAME_ASM): $(LFT) $(LFT_PRINTF) $(OBJ_ASM)
	@$(CC) $(addprefix $(OBJ_DIR)/, $(OBJ_ASM)) $(INCLUDE) -lft -L $(LFT_DIR) -lftprintf -L $(LFT_PRINTF_DIR) -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(OBJ_ASM): %.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $< $(addprefix -I,$(HEADERS_DIR)) -o $(OBJ_DIR)/$@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

$(LFT):
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(LFT_DIR) clean

$(LFT_PRINTF):
	@$(MAKE) -C $(LFT_PRINTF_DIR)
	@$(MAKE) -C $(LFT_PRINTF_DIR) clean

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LFT_DIR) fclean
	@$(MAKE) -C $(LFT_PRINTF_DIR) fclean

fclean: clean
	@rm -f $(NAME_ASM)
	@rm -f $(NAME_COREWAR)

re: fclean all