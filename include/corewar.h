/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/20 14:52:57 by vrichese         ###   ########.fr       */
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
	unsigned char			reg_buf[REG_SIZE];
	unsigned char			*registers;
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
	int						command_detect;
}							memory_status_t;

typedef struct				commands_s
{
	unsigned int			id;
	unsigned int			first_arg;
	unsigned int			second_arg;
	unsigned int			third_arg;
	unsigned char			type_args;
	void					(*function)(corewar_t *);
}							commands_t;

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
	commands_t				*available_command;
	int						*players_indicies;
	int						players_amount;
}							corewar_t;

carriage_t					*new_carriage(int owner, int id, int current_location, int current_command, int waiting_time, int step_bytes);
void						init_carriage(corewar_t *game);
void						validate_player(player_t *player);
player_t					*player_init(int player_id);
void						build_player(player_t *player);
void						check_arguments(int argc, char **argv);
void						print_arena(corewar_t *game);
int							arrange_units(corewar_t *game);
int							get_waiting_time(int command);
void						players_init(corewar_t *game, char **argv);
void						arena_init(corewar_t *game);
void						args_init(corewar_t *game, char **argv, int argc);
void						clean_up(corewar_t *game);
void						carriages_init(corewar_t *game);
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