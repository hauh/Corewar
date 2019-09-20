/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/20 18:56:09 by vrichese         ###   ########.fr       */
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
#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/ft_printf/includes/ft_printf.h"

typedef enum				byte_blocks_e
{
	BINARY_LABEL			= SIZE_BINARY_LABEL,
	NAME					= BINARY_LABEL + PROG_NAME_LENGTH,
	CODE_SIZE				= NAME + NULL_SEPARATOR + SIZE_VARIABLE,
	COMMENT					= CODE_SIZE + COMMENT_LENGTH,
	CODE					= COMMENT + NULL_SEPARATOR + CHAMP_MAX_SIZE
}							byte_blocks_t;

/*
**	-------------------------
**	Defines for error_catcher
*/

#define MEMORY_ALLOC_ERROR	1
#define NOT_VALID_ARG		2
#define OPEN_FILE_ERROR		3
#define READ_FILE_ERROR		4
#define INCORRECT_BINARY	5
#define TOO_BIG_SIZE		6
#define CHEAT_DETECT		7

#define DESTRUCTOR			"Destructor"
#define GAME				"Game"
#define KEYS				"Keys"
#define PLAYER				"Player"
#define CARRIAGE			"Carriage"
#define ARENA				"Arena"

/*
** ---------------------------
*/

#define TRUE				1
#define FALSE				0
#define CARRIAGE_ID_STEP	10

#define LIVE				0x01
#define LD					0x02
#define ST					0x03
#define ADD					0x04
#define SUB					0x05
#define AND					0x06
#define OR					0x07
#define XOR					0x08
#define ZJMP				0x09
#define LDI					0x0a
#define STI					0x0b
#define FORK				0x0c
#define LLD					0x0d
#define LLDI				0x0e
#define LFORK				0x0f
#define AFF					0x10

#define FIRST_ARG			1
#define SECOND_ARG			2
#define THIRD_ARG			3

typedef struct				player_s
{
	int						id;
	int						code_size;
	int						carriage_id;
	int						binary_label;
	unsigned char			*code;
	unsigned char			*name;
	unsigned char			*source;
	unsigned char			*comment;
	struct player_s			*next;
	struct player_s			*prev;
}							player_t;

typedef struct				command_s
{
	unsigned int			id;
	unsigned int			first_arg;
	unsigned int			second_arg;
	unsigned int			third_arg;
	unsigned char			type_args;
	//void					(*function)(corewar_t *);
}							command_t;

typedef struct				carriage_s
{
	int						id;
	int						player_id;
	int						carry_flag;
	int						waiting_time;
	int						last_live_loop;
	int						next_command_location;
	int						current_location;
	unsigned char			*reg_buf;
	unsigned char			*registers;
	command_t				*current_command;
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

typedef struct				destructor_s
{
	int						keys_detect;
	int						self_detect;
	int						game_detect;
	int						arena_detect;
	int						players_detect;
	int						commands_detect;
	int						carriages_detect;
}							destructor_t;

typedef struct				key_s
{
	unsigned int			custom_id;
	unsigned int			concurance_cpu;
	unsigned int			concurance_gpu;
	unsigned int			visualizator;
	unsigned int			extended_param;
}							key_t;

typedef struct				corewar_s
{
	int						players_amount;
	int						carriages_amount;
	int						commands_amount;
	key_t					*keys;
	arena_t					*arena;
	player_t				*players;
	command_t				*commands;
	carriage_t				*carriages;
	destructor_t			*destructor;
}							corewar_t;

void						validate_player(player_t *player);
void						build_player(player_t *player);
void						check_arguments(int argc, char **argv);
void						print_arena(corewar_t *game);
int							arrange_units(corewar_t *game);
int							get_waiting_time(int command);
void						players_init(corewar_t *game, char **argv);
void						introduce_players(corewar_t *game);
int							here_we_go(corewar_t *game);
void						print_arena(corewar_t *game);
void						write_from_buf_to_reg(carriage_t *carriage, int reg_num);
void						read_from_arena_to_buf(carriage_t *carriage, unsigned char *arena, int data_location, int amount);
void						read_from_reg_to_buf(carriage_t *carriage, int reg_num);
void						write_from_buf_to_arena(carriage_t *carriage, unsigned char *arena, int data_location);
void						conversetion_int_to_bytes(unsigned char *dst, int number);
void						ld_exec(corewar_t *game);
void						st_exec(corewar_t *game);
void						add_exec(corewar_t *game);
void						sub_exec(corewar_t *game);
void						and_exec(corewar_t *game);
void						check_carry(carriage_t *carriage);
int							conversetion_bytes_to_int(unsigned char *data, int amount);
void						error_catcher(int error_code, const char *section);
void						initialization_players(corewar_t *game, char **argv, int argc);
void						initialization_carriages(corewar_t *game);
void						initialization_arena(corewar_t *game);

#endif
// 1	0x01	live	T_DIR					—						—				Нет	Нет		4	10	alive
// 2	0x02	ld		T_DIR / T_IND			T_REG					—				Да	Есть	4	5	load
// 3	0x03	st		T_REG					T_REG / T_IND			—				Нет	Есть	4	5	store
// 4	0x04	add		T_REG					T_REG					T_REG			Да	Есть	4	10	addition
// 5	0x05	sub		T_REG					T_REG					T_REG			Да	Есть	4	10	subtraction
// 6	0x06	and		T_REG / T_DIR / T_IND	T_REG / T_DIR / T_IND	T_REG			Да	Есть	4	6	bitwise AND (&)
// 7	0x07	or		T_REG / T_DIR / T_IND	T_REG / T_DIR / T_IND	T_REG			Да	Есть	4	6	bitwise OR (|)
// 8	0x08	xor		T_REG / T_DIR / T_IND	T_REG / T_DIR / T_IND	T_REG			Да	Есть	4	6	bitwise XOR (^)
// 9	0x09	zjmp	T_DIR					—						—				Нет	Нет		2	20	jump if non-zero
// 10	0x0a	ldi		T_REG / T_DIR / T_IND	T_REG / T_DIR			T_REG			Нет	Есть	2	25	load index
// 11	0x0b	sti		T_REG					T_REG / T_DIR / T_IND	T_REG / T_DIR	Нет	Есть	2	25	store index
// 12	0x0c	fork	T_DIR					—						—				Нет	Нет		2	800	fork
// 13	0x0d	lld		T_DIR / T_IND			T_REG					—				Да	Есть	4	10	long load
// 14	0x0e	lldi	T_REG / T_DIR / T_IND	T_REG / T_DIR			T_REG			Да	Есть	2	50	long load index
// 15	0x0f	lfork	T_DIR					—						—				Нет	Нет		2	1000long fork
// 16	0x10	aff		T_REG					—						—				Нет	Есть	4	2	aff