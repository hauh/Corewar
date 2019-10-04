/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/04 20:01:45 by vrichese         ###   ########.fr       */
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
#include "libft.h"
//# include "ft_printf.h"
# include <ncurses.h>
# include <locale.h>
# include <time.h>

#define CW_WAITING_TIME			game->carriages->waiting_time
#define CW_DYNAMIC_SIZE_DIR		4 - game->carriages->current_command->dir_size
#define CW_CARRIAGE_SAVE_POINT	game->carriages->save_point
#define CW_AVAILABILITY_TYPES	game->carriages->current_command->availability_types
#define CW_REQUESTING_REGISTER	game->carriages->current_register
#define CW_CARRIAGE_LOCATION	game->carriages->current_location
#define CW_GAME_ARENA			game->arena->field
#define CW_CURRENT_COMMAND		game->carriages->current_command
#define CW_FIRST_ARG			game->carriages->current_command->first_arg
#define CW_SECOND_ARG			game->carriages->current_command->second_arg
#define CW_THIRD_ARG			game->carriages->current_command->third_arg
#define CW_CARRIAGE_REGISTERS	game->carriages->registers
#define CW_BUFFER_SET			game->arena->buffer_set

typedef enum				byte_blocks_e
{
	BINARY_LABEL			= SIZE_BINARY_LABEL,
	NAME					= BINARY_LABEL + PROG_NAME_LENGTH,
	CODE_SIZE				= NAME + NULL_SEPARATOR + SIZE_VARIABLE,
	COMMENT					= CODE_SIZE + COMMENT_LENGTH,
	CODE					= COMMENT + NULL_SEPARATOR + CHAMP_MAX_SIZE
}							byte_blocks_t;

#define CW_REG_CODE			1
#define CW_DIR_CODE			2
#define CW_IND_CODE			3

#define CW_ACROSS_NAME		carriageInstance->current_command->availability_types
#define CW_ACROSS_TYPE		1

#define CW_CHAR				1
#define CW_SHORT			2
#define CW_INT				4
#define CW_CHAR_BIAS		3
#define CW_SHORT_BIAS		2
#define CW_INT_BIAS			0

#define	R1					1
#define	R2					2
#define	R3					3
#define	R4					4
#define	R5					5
#define	R6					6
#define	R7					7
#define	R8					8
#define	R9					9
#define	R10					10
#define	R11					11
#define	R12					12
#define	R13					13
#define	R14					14
#define	R15					15
#define	R16					16

#define	COMMAND_AMOUNT		16 + 1
#define DIRECTION_SIZE		4
#define SHORT_DIR_SIZE		2
#define OVERSTEP_NAME		1
#define CW_REGISTER_SIZE	1
#define CW_IND_SIZE			2
#define TO_FIRST_ARG		1
#define ERROR				-335

#define PUT_WAITING_TIME(x)	(x << 48)
#define PUT_DIR_SIZE(x)		(x << 40)
#define PUT_ID(x)			(x << 32)
#define PUT_FIRST_ARG(x)	(x << 31)
#define PUT_SECOND_ARG(x)	(x << 30)
#define PUT_THIRD_ARG(x)	(x << 29)
#define PUT_CHANGE_CARRY(x)	(x << 28)
#define PUT_AVAI_TYPES(x)	(x << 27)

#define GET_WAITING_TIME(x) (x >> 48)
#define GET_DIR_SIZE(x)		(x << 16) >> 56
#define GET_ID(x)			(x << 24) >> 56
#define GET_FIRST_ARG(x)	(x << 32) >> 63
#define GET_SECOND_ARG(x)	(x << 33) >> 63
#define GET_THIRD_ARG(x)	(x << 34) >> 63
#define GET_CHANGE_CARRY(x)	(x << 35) >> 63
#define GET_AVAI_TYPES(x)	(x << 36) >> 63

/*
**	-------------------------
**	Defines for error_catcher
*/

#define CW_NOT_ALLOCATED	1
#define CW_NOT_VALID_KEY	2
#define CW_OPEN_FILE_ERROR	3
#define CW_READ_FILE_ERROR	4
#define CW_INCORRECT_BINARY	5
#define CW_TOO_BIG_SIZE		6
#define CW_CHEAT_DETECT		7
#define CW_ARGS_AMOUN_ERROR	8
#define CW_INVALID_PLAYERS	9
#define CW_KERNEL_ERROR		10

#define CW_DESTRUCTOR		"Destructor"
#define CW_GAME				"Game"
#define CW_KEYS				"Keys"
#define CW_PLAYER			"Player"
#define CW_CARRIAGE			"Carriage"
#define CW_ARENA			"Arena"
#define CW_COMMAND			"Command"
#define CW_INIT				"Initialization"
#define CW_EXEC_ERROR		"In Exec error"

/*
** ---------------------------
*/

#define CW_BEGIN_FROM_ZERO	0
#define CW_BEGIN_FROM_ONE	1
#define CW_TRUE				1
#define CW_FALSE			0
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

typedef struct	corewar_s corewar_t;
typedef char flag_t;

typedef enum				set_buffer_e
{
	CW_VALUE_BUF_1,
	CW_VALUE_BUF_2,
	CW_VALUE_BUF_3,
	CW_SYSTEM_BUF,
	CW_SPARE_BUF,
	CW_BUFFER_AMOUNT
}							set_buffer_t;

typedef struct 				buffer_s
{
	int						int_value;
	char					char_value;
	short					short_value;
	unsigned char			*data;
}							buffer_t;

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

	const void				(*cwConstructorPlayer)	(player_t *);
	const void				(*cwBuildPlayer)		(player_t *);
	const void				(*cwValidatePlayer)		(player_t *);
	const void				(*cwReadFile)			(player_t *, const char *);
	const void				(*cwDestructorPlayer)	(player_t *);
}							player_t;

typedef struct				command_s
{
	unsigned int			id;
	unsigned int			first_arg;
	unsigned int			second_arg;
	unsigned int			third_arg;
	unsigned int			dir_size;
	unsigned int			change_carry;
	unsigned int			waiting_time;
	unsigned int			availability_types;
	void					(*call)(corewar_t *);
}							command_t;

/*
** Carriage object;
*/

typedef struct				carriage_s
{
	int						id;
	int						jump;
	int						carry;
	int						savePoint;
	int						waitingTime;
	int						lastSpeakCycle;
	int						currentLocation;
	int						currentRegister;

	unsigned char			*registers;

	struct carriage_s		*next;
	struct carriage_s		*prev;

	command_t				*currentCommand;
	player_t				*ownerCarriage;

	const void				(*cwConstructorCarriage)(carriage_t *);
	const void				(*cwReduceWaitingTime)	(carriage_t *);
	const void				(*cwExecCommand)		(carriage_t *);
	const void				(*cwSetCommand)			(carriage_t *);
	const void				(*cwSavePos)			(carriage_t *);
	const void				(*cwMoveTo)				(carriage_t *, int);
	const void				(*cwComputeJump)		(carriage_t *);
	const void				(*cwParseTypes)			(carriage_t *);
	const void				(*cwReadOperation)		(carriage_t *);
	const void				(*cwWriteOperation)		(carriage_t *);
	const void				(*cwValidateCommand)	(carriage_t *);
	const void				(*cwValidateTypes)		(carriage_t *);
	const void				(*cwDestructorCarriage) (carriage_t *);
}							carriage_t;

/*
**-------------------------------------
*/

typedef struct				arena_s
{
	int						live_amount;
	int						check_amount;
	int						cycle_to_die;
	unsigned long			cycle_amount;
	unsigned char			*field;
	carriage_t				*last_carriage;
	player_t				*last_survivor;
	buffer_t				*buffer_set[CW_BUFFER_AMOUNT];
}							arena_t;

typedef struct				key_s
{
	unsigned int			load_dump;
	unsigned int			custom_id;
	unsigned int			visualizator;

	const void				(*cwConstructorKey)		(key_t *);
	const void				(*cwValidateArgs)		(key_t *, int, char **);
	const void				(*cwReadKeys)			(key_t *, int, char **);
	const void				(*cwDestructorKey)		(key_t *);
}							key_t;

typedef struct				corewar_s
{
	int						playersAmount;
	int						commandsAmount;
	int						carriagesAmount;

	carriage_t				*pCarriageObject;
	command_t				*commands[COMMAND_AMOUNT];
	player_t				*pPlayerObject;
	arena_t					*pArenaObject;
	key_t					*pKeyObject;

	const void				(*cwConstructorGame)	(corewar_t *);
	const void				(*cwKeyObjectInit)		(corewar_t *, int, char **);
	const void				(*cwPlayerObjectInit)	(corewar_t *, int, char **);
	const void				(*cwCarraigeObjectInit)	(corewar_t *);
	const void				(*cwArenaObjectInit)	(corewar_t *);
	const void				(*cwCommandObjectInit)	(corewar_t *);
	const void				(*cwIntroducePlayers)	(corewar_t *);
	const void				(*cwStartGame)			(corewar_t *);
	const void				(*cwAddPlayerToList)	(corewar_t *, player_t *);
	const void				(*cwAddCarriageToList)	(corewar_t *, carriage_t *);
	const void				(*cwDestructorGame)		(corewar_t *);
}							corewar_t;


void						cwIntroducePlayers			(corewar_t *game);
void						cwHereWeGo					(corewar_t *game);
void						cwPrintArena				(corewar_t *game);
void						cwConversionIntToBytes		(unsigned char *buffer, int *from, int bias);
void						cwConversionBytesToInt		(unsigned char *buffer, void *dest, int bias, int type);
void						cwReadFromRegToBuf			(unsigned char *buffer, unsigned char *registers, int reg_num, int bias);
void						cwReadFromArenaToBuf		(unsigned char *buffer, unsigned char *field, int data_location, int bias);
void						cwWriteFromBufToReg			(unsigned char *buffer, unsigned char *registers, int reg_num, int bias);
void						cwWriteFromBufToArena		(unsigned char *buffer, unsigned char *field, int data_location, int bias);
void						live_exec					(corewar_t *game);
void						ld_exec						(corewar_t *game);
void						st_exec						(corewar_t *game);
void						add_exec					(corewar_t *game);
void						sub_exec					(corewar_t *game);
void						and_exec					(corewar_t *game);
void						or_exec						(corewar_t *game);
void						xor_exec					(corewar_t *game);
void						zjmp_exec					(corewar_t *game);
void						ldi_exec					(corewar_t *game);
void						sti_exec					(corewar_t *game);
void						fork_exec					(corewar_t *game);
void						lld_exec					(corewar_t *game);
void						lldi_exec					(corewar_t *game);
void						lfork_exec					(corewar_t *game);
void						aff_exec					(corewar_t *game);
void						cwErrorCatcher				(int error_code, const char *section);
void						cwInitializationPlayers		(corewar_t *game, char **argv, int argc);
void						cwInitializationCarriages	(corewar_t *game);
void						cwInitializationArena		(corewar_t *game);
void						cwInitializationCommands	(corewar_t *game);
void						cwInitializationDestructor	(corewar_t *game);
void						cwInitializationKeys		(corewar_t *game, char **argv, int argc);
void						cwCheckCarry				(unsigned char *registers, int *carry, int reg_num);
void						cwCopyReg					(unsigned char *from, unsigned char *to, int size);
void						logging(corewar_t *game, flag_t flag);

#endif