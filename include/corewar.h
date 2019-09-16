/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/16 21:11:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum				byte_blocks_e
{
	BINARY_LABEL	= SIZE_BINARY_LABEL,
	NAME			= BINARY_LABEL + PROG_NAME_LENGTH,
	CODE_SIZE		= NAME + NULL_SEPARATOR + SIZE_VARIABLE,
	COMMENT			= CODE_SIZE + COMMENT_LENGTH,
	CODE			= COMMENT + NULL_SEPARATOR + CHAMP_MAX_SIZE
}							byte_blocks_t;

typedef struct				player_s
{
	int						id;
	int						carriage_id;
	int						reading_carriage;
	int						binary_label;
	unsigned int			code_size;
	unsigned char			*name;
	unsigned char			*comment;
	unsigned char			*code;
	unsigned char			*player_source;
}							player_t;

typedef struct				carriage_s
{
	int						id;
	int						player_id;
	int						waiting_time;
	unsigned int			current_command;
	unsigned int			current_location;
	unsigned int			register_size;
	int						*registers;
}							carriage_t;

typedef struct				game_setting_s
{
	unsigned long long		loop_amount;
	int						last_survivor;
	int						check_live_amount;
	int						cycle_to_die;
	int						live_amount;
}							game_setting_t;

typedef struct				carriage_list_s
{
	carriage_t				current_carriage;
	struct carriage_list_s	*next;
	struct carriage_list_s	*prev;
}							carriage_list_t;

typedef struct				corewar_s
{
	player_t				*players[MAX_PLAYERS];
	game_setting_t			*setting;
	carriage_list_t			*carriage_list;
	int						players_amount;
	unsigned char			*arena;
}							corewar_t;

#endif