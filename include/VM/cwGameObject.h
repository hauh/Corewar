/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGameObject.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:15:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/26 18:17:16 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_GAME_OBJECT_H
# define CW_GAME_OBJECT_H

#include "cwTypedefObjects.h"

#define	CW_COMMAND_AMOUNT	16 + 1

typedef struct			corewar_s
{
	flag_t				load_dump;
	flag_t				visualizator;

	int					players_amount;
	int					commands_amount;
	int					carriages_amount;
	int					queue_size;

	carriage_t			*p_carriage_obj;
	command_t			*pa_commands[CW_COMMAND_AMOUNT];
	player_t			*p_player_obj;
	arena_t				*p_arena_obj;

	queue_t				*p_execution_queue;
	stackk_t			*p_distribution_stack;
	queue_t				*p_waiting_queue;

	void				(*cw_constructor)			(corewar_t **);
	void				(*cw_carriage_obj_init)		(corewar_t *);
	void				(*cw_command_obj_init)		(corewar_t *);
	void				(*cw_player_obj_init)		(corewar_t *, int, char **);
	void				(*cw_arena_obj_init)		(corewar_t *);
	void				(*cw_add_carriage_to_list)	(corewar_t *, carriage_t *, int);
	void				(*cw_add_player_to_list)	(corewar_t *, player_t *);
	void				(*cw_free_all_carriages)	(corewar_t *);
	void				(*cw_free_all_players)		(corewar_t *);
	void 				(*cw_free_all_command)		(corewar_t *);
	void				(*cw_arrange_units_on_field)(corewar_t *);
	void				(*cw_introduce_players)		(corewar_t *);
	void				(*cw_congratulations)		(corewar_t *);
	void				(*cw_delete_carriage)		(corewar_t *, int *);
	void				(*cw_main_checking)			(corewar_t *);
	void				(*cw_start_game)			(corewar_t *);
	void				(*cw_push_to_queue)			(corewar_t *, carriage_t *);
	void				(*cw_merge_queue_to_list)	(corewar_t *);
	void				(*cw_stack_obj_init)		(corewar_t *);
	void				(*cw_queue_obj_init)		(corewar_t *);
	void				(*cw_destructor)			(corewar_t **);
}						corewar_t;

#endif
