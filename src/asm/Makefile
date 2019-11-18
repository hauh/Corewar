# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 18:56:46 by smorty            #+#    #+#              #
#    Updated: 2019/11/18 22:59:31 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := asm

OBJ_DIR := obj

LFT_DIR := ../libft

LFT_PRINTF_DIR := ../ft_printf

HEADERS_DIR := ../../include/asm $(LFT_DIR) $(LFT_PRINTF_DIR)/includes

SRC_ASM := asm.c process_argument.c parse_file.c read_input.c\
			parse_title.c parse_label.c parse_opcode.c parse_parameter.c\
			calculate_sizes.c assemble.c disassemble.c\

OBJ_ASM := $(SRC_ASM:.c=.o)

HEADERS := asm.h libft.h ft_printf.h op.h

CC := gcc -Wall -Werror -Wextra -O3

vpath %.o $(OBJ_DIR)
vpath %.h $(HEADERS_DIR)
vpath %.a $(LFT_DIR) $(LFT_PRINTF_DIR)

all: $(NAME)

$(NAME): $(OBJ_ASM)
	@$(CC) $(addprefix $(OBJ_DIR)/, $(OBJ_ASM)) $(INCLUDE) -lft -L $(LFT_DIR) -lftprintf -L $(LFT_PRINTF_DIR) -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"
	@mv $@ ../..

$(OBJ_ASM): %.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $< $(addprefix -I,$(HEADERS_DIR)) -o $(OBJ_DIR)/$@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
