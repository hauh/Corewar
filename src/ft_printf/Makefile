# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 15:20:13 by vrichese          #+#    #+#              #
#    Updated: 2019/11/16 13:04:04 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCDIR	= source

LIBDIR	= lib_func

SRC		= $(addprefix $(SRCDIR)/, ft_printf.c char_handlers.c constructor.c chooser_betw_f_e.c \
			addit_func.c decimal_handlers.c double_handlers.c parse_string.c print_char.c \
			print_double.c print_hexadouble.c print_integer.c scientific_record_funcs.c \
			long_arithmetic.c long_arithmetic2.c long_arithmetic3.c)

LIB		= $(addprefix $(LIBDIR)/, ft_atoi.c ft_bzero.c ft_isspace.c ft_memcpy.c ft_strcmp.c ft_strlen.c)

OBJ		= ${SRC:.c=.o} ${LIB:.c=.o}

CC		= gcc

CFLAGS	= -O3 -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $(OBJ)
	@ranlib $@
	@printf "\r\e[J\e[33mlibftprintf.a \e[0mdone!\e[?25h\n"

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I./includes -c -o $@ $<
	@printf "\r\e[?25l\e[JCompiling \e[35m$(notdir $<)\e[0m"

$(LIBDIR)/%.o: $(LIBDIR)/%.c
	@$(CC) $(CFLAGS) -I./includes -c -o $@ $<
	@printf "\r\e[?25l\e[JCompiling \e[35m$(notdir $<)\e[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
