/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/26 20:04:23 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_merge_queue_to_list(corewar_t *p_game_instance)
{
	carriage_t	*pTempCarriage;
	int			iter;

	iter = 0;
	while (iter < p_game_instance->queue_size)
	{
		pTempCarriage = p_game_instance->p_waiting_queue->p_next;
		p_game_instance->cw_add_carriage_to_list(p_game_instance, p_game_instance->p_waiting_queue, 0);
		p_game_instance->carriages_amount += 1;
		p_game_instance->p_waiting_queue = pTempCarriage;
		++iter;
	}
	p_game_instance->p_waiting_queue	= NULL;
	p_game_instance->queue_size		= 0;
}

static void		cwPushToQueue(corewar_t *p_game_instance, carriage_t *pAddingCarriage)
{
	p_game_instance->queue_size += 1;
	if (!p_game_instance->p_waiting_queue)
	{
		p_game_instance->p_waiting_queue	= pAddingCarriage;
		pAddingCarriage->p_next			= pAddingCarriage;
		pAddingCarriage->p_prev			= pAddingCarriage;
	}
	else
	{
		pAddingCarriage->p_next						= p_game_instance->p_waiting_queue;
		pAddingCarriage->p_prev						= p_game_instance->p_waiting_queue->p_prev;
		p_game_instance->p_waiting_queue->p_prev->p_next	= pAddingCarriage;
		p_game_instance->p_waiting_queue->p_prev			= pAddingCarriage;
	}
}

static void		cwDeleteCarriage(corewar_t *p_game_instance, int *pDeletedCount)
{
	carriage_t	*pTemporaryCarriage;
	pTemporaryCarriage = p_game_instance->p_carriage_obj;
	if (p_game_instance->p_carriage_obj->p_next == p_game_instance->p_carriage_obj)
		p_game_instance->p_carriage_obj->cw_destructor(&p_game_instance->p_carriage_obj);
	else
	{		p_game_instance->p_carriage_obj->p_prev->p_next	= p_game_instance->p_carriage_obj->p_next;
		p_game_instance->p_carriage_obj->p_next->p_prev	= p_game_instance->p_carriage_obj->p_prev;
		p_game_instance->p_carriage_obj				= p_game_instance->p_carriage_obj->p_next;
		pTemporaryCarriage->cw_destructor			(&pTemporaryCarriage);
	}
	*pDeletedCount += 1;
}

static void		cw_main_checking(corewar_t *p_game_instance)
{
	carriage_t 	*tmp;
	int			deleted_count;
	int			iter;

	deleted_count = 0;
	iter		 = CW_BEGIN_FROM_ZERO;
	p_game_instance->p_arena_obj->check_amount += 1;
	while (iter < p_game_instance->carriages_amount)
	{
		if ((p_game_instance->p_arena_obj->cycle_amount - p_game_instance->p_carriage_obj->last_speak_cycle) > p_game_instance->p_arena_obj->cycle_to_die || p_game_instance->p_arena_obj->cycle_to_die <= 0)
			p_game_instance->cw_delete_carriage(p_game_instance, &deleted_count);
		p_game_instance->p_carriage_obj ? p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next : CW_FALSE;
		++iter;
	}
	p_game_instance->carriages_amount -= deleted_count;
	if (p_game_instance->p_arena_obj->live_amount >= NBR_LIVE || p_game_instance->p_arena_obj->check_amount > MAX_CHECKS)
	{
		p_game_instance->p_arena_obj->cycle_to_die -= CYCLE_DELTA;
		p_game_instance->p_arena_obj->check_amount = 0;
	}
	p_game_instance->p_arena_obj->live_amount = 0;
}

static void	cw_start_game(corewar_t *p_game_instance)
{
	int		iter;

	while (p_game_instance->p_carriage_obj && ++p_game_instance->p_arena_obj->cycle_amount)
	{
		iter = CW_BEGIN_FROM_ZERO;
		if (!--p_game_instance->p_distribution_stack->current_waiting_time)
		{
			p_game_instance->p_distribution_stack->cw_distribute(p_game_instance->p_distribution_stack,
			p_game_instance->p_waiting_queue, p_game_instance->p_execution_queue);
			p_game_instance->p_waiting_queue->cw_sort(p_game_instance->p_waiting_queue);
			p_game_instance->p_waiting_queue->cw_reduce_time(p_game_instance->p_waiting_queue);
			p_game_instance->p_execution_queue->cw_sort(p_game_instance->p_execution_queue);
		}
		p_game_instance->p_execution_queue->cw_exec(p_game_instance->p_execution_queue);
	}
}

static void	cwArrangeUnitsOnField(corewar_t *p_game_instance)
{
	int		iter;
	int		playerLocation;
	int		memoryStep;
	int		codeIter;

	memoryStep	= MEM_SIZE / p_game_instance->players_amount;
	iter		= CW_BEGIN_FROM_ZERO;
	p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_prev;
	while (iter < p_game_instance->carriages_amount)
	{
		codeIter = CW_BEGIN_FROM_ZERO;
		playerLocation = memoryStep * iter;
		p_game_instance->p_carriage_obj->current_location = playerLocation;
		while (playerLocation < memoryStep * iter + CHAMP_MAX_SIZE)
			p_game_instance->p_arena_obj->p_field[playerLocation++] = p_game_instance->p_carriage_obj->p_owner->p_code[codeIter++];
		p_game_instance->p_carriage_obj	= p_game_instance->p_carriage_obj->p_prev;
		++iter;
	}
	p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next;
}

static void	cwCongratulations(corewar_t *p_game_instance)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
	p_game_instance->p_arena_obj->p_last_survivor->id,
	p_game_instance->p_arena_obj->p_last_survivor->p_name);
}

static void	cwIntroducePlayers(corewar_t *gameInstance)
{
	int				iter;

	iter = CW_BEGIN_FROM_ZERO;
	ft_printf("Introducing contestants...\n");
	while (iter < gameInstance->carriages_amount)
	{
		printf("* Player %d, weighing%d bytes, \"%s\" (\"%s\")\n",
		gameInstance->p_carriage_obj->p_owner->id,
		gameInstance->p_carriage_obj->p_owner->code_size,
		gameInstance->p_carriage_obj->p_owner->p_name,
		gameInstance->p_carriage_obj->p_owner->p_comment);
		gameInstance->p_carriage_obj = gameInstance->p_carriage_obj->p_next;
		++iter;
	}
}

static void	cw_free_all_command(corewar_t *p_game_instance)
{
	int		iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		p_game_instance->pa_commands[iter]->cw_destructor(&p_game_instance->pa_commands[iter]);
		++iter;
	}
}

static void	cwFreeAllCarriage(corewar_t *p_game_instance)
{
	;
}

static void	cwFreeAllPlayer(corewar_t *p_game_instance)
{
	;
}

static void	cw_add_carriage_to_list(corewar_t *p_game_instance, carriage_t *pCarriageAdding, int ascending)
{
	if (!p_game_instance->p_carriage_obj)
	{
		p_game_instance->p_carriage_obj	= pCarriageAdding;
		p_game_instance->p_carriage_obj->p_next	= pCarriageAdding;
		p_game_instance->p_carriage_obj->p_prev	= pCarriageAdding;
	}
	else
	{
		pCarriageAdding->p_next							= p_game_instance->p_carriage_obj;
		pCarriageAdding->p_prev							= p_game_instance->p_carriage_obj->p_prev;
		p_game_instance->p_carriage_obj->p_prev->p_next	= pCarriageAdding;
		p_game_instance->p_carriage_obj->p_prev			= pCarriageAdding;
		if (!ascending)
			p_game_instance->p_carriage_obj = pCarriageAdding;
	}
}

static void	cwAddPlayerToList(corewar_t *p_game_instance, player_t *pPlayerAdding)
{
	if (!p_game_instance->p_player_obj)
	{
		p_game_instance->p_player_obj		 = pPlayerAdding;
		p_game_instance->p_player_obj->p_next = pPlayerAdding;
		p_game_instance->p_player_obj->p_prev = pPlayerAdding;
	}
	else
	{
		pPlayerAdding->p_next					= p_game_instance->p_player_obj;
		pPlayerAdding->p_prev					= p_game_instance->p_player_obj->p_prev;
		p_game_instance->p_player_obj->p_prev->p_next	= pPlayerAdding;
		p_game_instance->p_player_obj->p_prev		= pPlayerAdding;
	}
}

static void	cwCommandObjectInit(corewar_t *p_game_instance)
{
	command_t		*pCommandObj;
	int				iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		cw_create_instance_command			(&pCommandObj);
		pCommandObj->cw_recognize	(pCommandObj, iter);
		p_game_instance->pa_commands[iter]	= pCommandObj;
		++iter;
	}
}

static void		cwCarriageObjectInit(corewar_t *p_game_instance)
{
	carriage_t	*p_carriage_obj;
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < p_game_instance->players_amount)
	{
		cw_create_instance_carriage(&p_carriage_obj);
		p_carriage_obj->id = ++p_game_instance->carriages_amount;
		p_carriage_obj->pp_command_container = p_game_instance->pa_commands;
		p_carriage_obj->cw_set_owner(p_carriage_obj, p_game_instance->p_player_obj, p_game_instance->players_amount);
		p_carriage_obj->cw_write_owner_id_to_reg(p_carriage_obj);
		p_game_instance->p_distribution_stack->cw_push(p_game_instance->p_distribution_stack, p_carriage_obj);
		++iter;
	}
	p_game_instance->p_distribution_stack->cw_peek(p_game_instance->p_distribution_stack, p_carriage_obj);
	p_game_instance->p_arena_obj->cw_set_last_survivor(p_game_instance->p_arena_obj, p_carriage_obj->p_owner);
}

static void		cw_queue_obj_init(corewar_t *p_game_instance)
{
	;
}

static void		cw_stack_obj_init(corewar_t *p_game_instance)
{
	stackk_t 	*stack;

	cw_create_instance_stack(&stack);
	p_game_instance->p_distribution_stack = stack;
}

static void		cwPlayerObjectInit(corewar_t *p_game_instance, int argc, char **argv)
{
	player_t	*p_player_obj;
	int			standartId;
	int			customId;
	int			iter;
	int			busyByte;

	standartId	= 0;
	customId	= 0;
	busyByte	= CW_ALL_FREE;
	iter		= CW_BEGIN_FROM_ONE;
	while (iter < argc)
	{
		if (*(argv[iter]) == CW_KEY)
		{
			while (*++(argv[iter]))
				if (*(argv[iter]) == 'n' && iter + 1 < argc)
					(customId = ft_atoi(argv[iter + 1])) < CW_MIN_PLAYERS
						|| (customId = ft_atoi(argv[iter + 1])) > CW_MAX_PLAYERS ?
							cwErrorCatcher(CW_NOT_VALID_KEY, "Not valid number near -n") :
								CW_FALSE;
				else if (*(argv[iter]) == 'd' && iter + 1 < argc)
					(p_game_instance->load_dump = ft_atoi(argv[iter + 1])) < CW_MIN_DUMP_CYCLE ?
						cwErrorCatcher(CW_NOT_VALID_KEY, "Not valid nubmer near -d") :
							CW_FALSE;
				else if (*(argv[iter]) == 'v')
					p_game_instance->visualizator = CW_TRUE;
				else
					cwErrorCatcher(CW_NOT_VALID_KEY, "Not that place");
			p_game_instance->load_dump || customId ? ++iter : CW_FALSE;
		}
		else if (++p_game_instance->players_amount)
		{
			cw_create_instance_player		(&p_player_obj);
			p_player_obj->cw_read_file		(p_player_obj, argv[iter]);
			p_player_obj->cw_self_build		(p_player_obj);
			p_player_obj->cw_self_validate	(p_player_obj);
			if (customId)
				p_player_obj->cw_set_id		(p_player_obj, &busyByte, customId, CW_TRUE);
			p_game_instance->cw_add_player_to_list(p_game_instance, p_player_obj);
			customId = 0;
		}
		++iter;
	}
	if (p_game_instance->players_amount < 1 || p_game_instance->players_amount > 4)
		cwErrorCatcher(CW_INVALID_PLAYERS, CW_PLAYER);
	iter = 0;
	while (iter < p_game_instance->players_amount)
	{
		if (p_game_instance->p_player_obj->id == 0)
			p_game_instance->p_player_obj->cw_set_id(p_game_instance->p_player_obj, &busyByte, 1, CW_FALSE);
		p_game_instance->p_player_obj = p_game_instance->p_player_obj->p_next;
		++iter;
	}
	p_game_instance->p_arena_obj->cw_set_last_survivor(p_game_instance->p_arena_obj, p_game_instance->p_player_obj->p_prev);
}

static void		cw_arena_obj_init(corewar_t *gameInstance)
{
	arena_t		*p_arena_obj;

	cw_create_instance_arena(&p_arena_obj);
	p_arena_obj->cw_buffer_init(p_arena_obj);
	gameInstance->p_arena_obj = p_arena_obj;
}

static void		cw_constructor(corewar_t **pp_game_instance)
{
	(*pp_game_instance)->players_amount = 0;
	(*pp_game_instance)->commands_amount = 0;
	(*pp_game_instance)->carriages_amount = 0;
	(*pp_game_instance)->queue_size = 0;
	(*pp_game_instance)->visualizator = CW_FALSE;
	(*pp_game_instance)->load_dump = CW_FALSE;
	(*pp_game_instance)->p_carriage_obj = NULL;
	(*pp_game_instance)->p_player_obj = NULL;
	(*pp_game_instance)->p_arena_obj = NULL;
	(*pp_game_instance)->p_waiting_queue = NULL;
}

static void		cw_destructor(corewar_t **pp_game_instance)
{
	(*pp_game_instance)->p_arena_obj->cw_destructor(&(*pp_game_instance)->p_arena_obj);
	(*pp_game_instance)->cw_free_all_carriages(*pp_game_instance);
	(*pp_game_instance)->cw_free_all_players(*pp_game_instance);
	(*pp_game_instance)->cw_free_all_command(*pp_game_instance);
	free(*pp_game_instance);
	*pp_game_instance = NULL;
}

extern void		cw_create_instance_game(corewar_t **pp_game_obj)
{
	if (!(*pp_game_obj = (corewar_t *)malloc(sizeof(corewar_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_GAME);
	(*pp_game_obj)->cw_constructor = cw_constructor;
	(*pp_game_obj)->cw_destructor = cw_destructor;
	(*pp_game_obj)->cw_carriage_obj_init = cwCarriageObjectInit;
	(*pp_game_obj)->cw_command_obj_init = cwCommandObjectInit;
	(*pp_game_obj)->cw_player_obj_init = cwPlayerObjectInit;
	(*pp_game_obj)->cw_arena_obj_init = cw_arena_obj_init;
	(*pp_game_obj)->cw_add_carriage_to_list = cw_add_carriage_to_list;
	(*pp_game_obj)->cw_add_player_to_list = cwAddPlayerToList;
	(*pp_game_obj)->cw_free_all_carriages = cwFreeAllCarriage;
	(*pp_game_obj)->cw_free_all_players = cwFreeAllPlayer;
	(*pp_game_obj)->cw_free_all_command = cw_free_all_command;
	(*pp_game_obj)->cw_delete_carriage = cwDeleteCarriage;
	(*pp_game_obj)->cw_main_checking = cw_main_checking;
	(*pp_game_obj)->cw_start_game = cwStartGame;
	(*pp_game_obj)->cw_arrange_units_on_field = cwArrangeUnitsOnField;
	(*pp_game_obj)->cw_introduce_players = cwIntroducePlayers;
	(*pp_game_obj)->cw_congratulations = cwCongratulations;
	(*pp_game_obj)->cw_push_to_queue = cwPushToQueue;
	(*pp_game_obj)->cw_merge_queue_to_list	= cw_merge_queue_to_list;
	(*pp_game_obj)->cw_queue_obj_init = cw_queue_obj_init;
	(*pp_game_obj)->cw_stack_obj_init = cw_stack_obj_init;
	(*pp_game_obj)->cw_constructor(pp_game_obj);
}
