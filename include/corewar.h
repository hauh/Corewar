/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/17 21:27:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/libft/includes/libft.h"

typedef enum				byte_blocks_e
{
	BINARY_LABEL			= SIZE_BINARY_LABEL,
	NAME					= BINARY_LABEL + PROG_NAME_LENGTH,
	CODE_SIZE				= NAME + NULL_SEPARATOR + SIZE_VARIABLE,
	COMMENT					= CODE_SIZE + COMMENT_LENGTH,
	CODE					= COMMENT + NULL_SEPARATOR + CHAMP_MAX_SIZE
}							byte_blocks_t;

#define TRUE				1
#define FALSE				0

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
	int						carry_flag;
	int						last_live_loop;
	int						waiting_time;
	int						step_bytes;
	unsigned int			current_command;
	unsigned int			current_location;
	int						*registers;
	struct carriage_s		*next;
	struct carriage_s		*prev;
}							carriage_t;

typedef struct				arena_s
{
	player_t				*last_survivor;
	unsigned char			*field;
	unsigned long long		loop_amount;
	int						check_amount;
	int						cycle_to_die;
	int						live_amount;
}							arena_t;

typedef struct				memory_status_s
{
	int						arena_detect;
	int						args_detect;
	int						carriage_list_detect;
	int						players_detect;
	int						indicies_detect;
}							memory_status_t;

typedef struct				args_s
{
	int						custom_id;
	int						concurance_cpu;
	int						concurance_gpu;
	int						visualizator;
	int						extended_param;
}							args_t;

typedef struct				corewar_s
{
	arena_t					*arena;
	args_t					*args;
	carriage_t				*carriages;
	player_t				*players[MAX_PLAYERS];
	memory_status_t			memory_status;
	int						*players_indicies;
	int						players_amount;
}							corewar_t;

carriage_t					*new_carriage(int owner, int id, int current_location, int current_command, int waiting_time, int step_bytes);
void						add_carriage(carriage_list_t **list, carriage_t *carriage);
void						validate_player(player_t *player);
player_t					*player_init(int player_id);
void						build_player(player_t *player);
void						check_arguments(int argc, char **argv);
void						print_arena(corewar_t *game);
int							arrange_units(corewar_t *game);
int							get_waiting_time(int command);
void						*game_init(corewar_t **game, char **argv);
void						players_init(corewar_t *game, char **argv);
void						arena_init(corewar_t *game);
void						args_init(corewar_t *game, char **argv, int argc);
void						clean_up(corewar_t *game);

#endif