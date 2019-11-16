# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 18:46:34 by smorty            #+#    #+#              #
#    Updated: 2019/08/07 21:18:03 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isupper.c ft_memcpy.c ft_strcapitalize.c ft_strlcat.c ft_strrchr.c\
		ft_itoa.c ft_memdel.c ft_strcat.c ft_strlcpy.c ft_strsplit.c\
		ft_lstadd.c ft_memmove.c ft_strchr.c ft_strlen.c ft_strstr.c\
		ft_atoi.c ft_lstdel.c ft_memset.c ft_strclr.c ft_strmap.c ft_strsub.c\
		ft_bzero.c ft_lstdelone.c ft_putchar.c ft_strcmp.c ft_strmapi.c\
		ft_strtrim.c ft_isalnum.c ft_lstiter.c ft_putchar_fd.c ft_strcpy.c\
		ft_strncat.c ft_tolower.c ft_isalpha.c ft_lstmap.c ft_putendl.c\
		ft_strdel.c ft_strncmp.c ft_toupper.c ft_isascii.c ft_lstnew.c\
		ft_putendl_fd.c ft_strdup.c ft_strncpy.c ft_isblank.c ft_memalloc.c\
		ft_putnbr.c ft_strequ.c ft_strndup.c ft_isdigit.c ft_memccpy.c\
		ft_putnbr_fd.c ft_striter.c ft_strnequ.c ft_islower.c ft_memchr.c\
		ft_putstr.c ft_striteri.c ft_strnew.c ft_isprint.c ft_memcmp.c\
		ft_putstr_fd.c ft_strjoin.c ft_strnstr.c

OBJ = ${SRC:.c=.o}

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@printf "\r\e[Jar \e[32m$@\e[0m"
	@ranlib $(NAME)
	@printf "\r\e[Jranlib \e[32m$@\e[0m"
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

%.o: %.c
	@printf "\r\e[?25l\e[Jcompiling \e[32m$^\e[0m"
	@gcc $(FLAGS) -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
