# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 19:28:55 by smorty            #+#    #+#              #
#    Updated: 2019/11/18 22:57:13 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		:= libft.a
FTPRINTF	:= libftprintf.a
ASM			:= asm
VM			:= corewar

SRCDIR		:= src
LFTDIR		:= $(SRCDIR)/libft
FTPRINTFDIR	:= $(SRCDIR)/ft_printf
ASMDIR		:= $(SRCDIR)/asm
VMDIR		:= $(SRCDIR)/vm

all: $(LIBFT) $(FTPRINTF) $(ASM) $(VM)

$(LIBFT):
	@$(MAKE) -C $(LFTDIR)

$(FTPRINTF):
	@$(MAKE) -C $(FTPRINTFDIR)

$(ASM):
	@$(MAKE) -C $(ASMDIR)

$(VM):
	@$(MAKE) -C $(VMDIR)
	@printf "\r\e[J\e[33m"
	@printf "     ____   ___   ____   _____ __        __  _     ____ \n"
	@printf "    / ___| / _ \ |  _ \ | ____|\ \      / / / \   |  _ \ \n"
	@printf "   | |    | | | || |_) ||  _|   \ \ /\ / / / _ \  | |_) | \n"
	@printf "   | |___ | |_| ||  _ < | |___   \ V  V / / ___ \ |  _ < \n"
	@printf "    \____| \___/ |_| \_\|_____|   \_/\_/ /_/   \_\|_| \_\ \n\n"
	@printf " ____   _____     _     ____  __   __    _____   ___   ____ \n"
	@printf "|  _ \ | ____|   / \   |  _ \ \ \ / /   |  ___| / _ \ |  _ \ \n"
	@printf "| |_) ||  _|    / _ \  | | | | \ V /    | |_   | | | || |_) | \n"
	@printf "|  _ < | |___  / ___ \ | |_| |  | |     |  _|  | |_| ||  _ < \n"
	@printf "|_| \_\|_____|/_/   \_\|____/   |_|     |_|     \___/ |_| \_\ \n\n"
	@printf "           ____     _   _____  _____  _      _____ \n"
	@printf "          | __ )   / \ |_   _||_   _|| |    | ____| \n"
	@printf "          |  _ \  / _ \  | |    | |  | |    |  _| \n"
	@printf "          | |_) |/ ___ \ | |    | |  | |___ | |___ \n"
	@printf "          |____//_/   \_\|_|    |_|  |_____||_____| \n"
	@printf "\e[0m\e[?25h\n"

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
