/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/10 19:19:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"

# include "cwArenaObject.h"
# include "cwBufferObject.h"
# include "cwCarriageObject.h"
# include "cwCommandObject.h"
# include "cwErrorObject.h"
# include "cwGameObject.h"
# include "cwKeyObject.h"
# include "cwPlayerObject.h"

/*
** Subject's defines
** -----------------------------------
*/

#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define SIZE_BINARY_LABEL		4
#define NULL_SEPARATOR			4
#define SIZE_VARIABLE			4
#define MEM_SIZE				(4 * 1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
**-------------------------------------
*/

typedef enum				byte_blocks_e
{
	BINARY_LABEL			= SIZE_BINARY_LABEL,
	NAME					= BINARY_LABEL + PROG_NAME_LENGTH,
	CODE_SIZE				= NAME + NULL_SEPARATOR + SIZE_VARIABLE,
	COMMENT					= CODE_SIZE + COMMENT_LENGTH,
	CODE					= COMMENT + NULL_SEPARATOR + CHAMP_MAX_SIZE
}							byte_blocks_t;


#define CW_CHAR				1
#define CW_SHORT			2
#define CW_INT				4
#define CW_CHAR_BIAS		3
#define CW_SHORT_BIAS		2
#define CW_INT_BIAS			0

#define DIRECTION_SIZE		4
#define SHORT_DIR_SIZE		2
#define OVERSTEP_NAME		1
#define CW_REGISTER_SIZE	1
#define TO_FIRST_ARG		1


/*
** Error's Defines
** -------------------------------------------
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
** ------------------------------------------
*/

/*
** Common defines;
** -----------------------------
*/

#define CW_BEGIN_FROM_ZERO	0x00
#define CW_BEGIN_FROM_ONE	0x01
#define CW_TRUE				0x01
#define CW_FALSE			0x00

#define CW_REG				0x40
#define CW_REG_CODE			0x01
#define CW_REG_SIZE			0x01
#define CW_REG_AMOUNT		0x04

#define CW_DIR				0x20
#define CW_DIR_CODE			0x02
#define CW_DIR_SIZE			0x04
#define CW_SHORT_DIR_SIZE	0x02

#define CW_IND				0x0c
#define CW_IND_CODE			0x03
#define CW_IND_SIZE			0x02

#define CW_CHECK_SEAL		'*'

/*
** -----------------------------
*/

/*
** Command's defines
** -----------------------------
*/

#define CW_LIVE				0x01
#define CW_LD				0x02
#define CW_ST				0x03
#define CW_ADD				0x04
#define CW_SUB				0x05
#define CW_AND				0x06
#define CW_OR				0x07
#define CW_XOR				0x08
#define CW_ZJMP				0x09
#define CW_LDI				0x0a
#define CW_STI				0x0b
#define CW_FORK				0x0c
#define CW_LLD				0x0d
#define CW_LLDI				0x0e
#define CW_LFORK			0x0f
#define CW_AFF				0x10

/*
**------------------------------
*/

void						liveExec	(corewar_t *game);
void						ldExec		(corewar_t *game);
void						stExec		(corewar_t *game);
void						addExec		(corewar_t *game);
void						subExec		(corewar_t *game);
void						andExec		(corewar_t *game);
void						orExec		(corewar_t *game);
void						xorExec		(corewar_t *game);
void						zjmpExec	(corewar_t *game);
void						ldiExec		(corewar_t *game);
void						stiExec		(corewar_t *game);
void						forkExec	(corewar_t *game);
void						lldExec		(corewar_t *game);
void						lldiExec	(corewar_t *game);
void						lforkExec	(corewar_t *game);
void						affExec		(corewar_t *game);

void						cwCreateInstanceGame		(corewar_t **ppGameObj);
void						cwCreateInstanceKey			(key_t **pKeyObj);
void						cwCreateInstancePlayer		(player_t **ppPlayerObj);
void						cwCreateInstanceCommand		(command_t **ppCommandObj);
void						cwCreateInstanceCarriage	(carriage_t **ppCarriageObj);
void						cwCreateInstanceBuffer		(buffer_t **ppBufferObj);
void						cwCreateInstanceArena		(arena_t **ppArenaObj);
void						cwErrorCatcher				(int error_code, const char *section);

#endif
