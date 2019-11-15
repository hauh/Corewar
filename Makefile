# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 19:28:55 by smorty            #+#    #+#              #
#    Updated: 2019/11/15 21:00:00 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		:= libft.a
FTPRINTF	:= libftprintf.a
ASM			:= asm
VM			:= corewar

SRCDIR		:= src
LFTDIR		:= $(SRCDIR)/libft
FTPRINTFDIR	:= $(SRCDIR)/ft_printf
ASMDIR		:= $(SRCDIR)/ASM
VMDIR		:= $(SRCDIR)/VM

all: $(LIBFT) $(FTPRINTF) $(ASM) $(VM)

$(LIBFT):
	@$(MAKE) -C $(LFTDIR)

$(FTPRINTF):
	@$(MAKE) -C $(FTPRINTFDIR)

$(ASM):
	@$(MAKE) -C $(ASMDIR)

$(VM):
	@$(MAKE) -C $(VMDIR)

clean:
	@$(MAKE) clean -C $(LFTDIR)
	@$(MAKE) clean -C $(FTPRINTFDIR)
	@$(MAKE) clean -C $(ASMDIR)
	@$(MAKE) clean -C $(VMDIR)

fclean:
	@$(MAKE) fclean -C $(LFTDIR)
	@$(MAKE) fclean -C $(FTPRINTFDIR)
	@$(MAKE) fclean -C $(ASMDIR)
	@$(MAKE) fclean -C $(VMDIR)
	@rm -f $(ASM)
	@rm -f $(VM)

re: fclean all
