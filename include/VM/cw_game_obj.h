/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_obj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:15:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 17:07:41 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_GAME_OBJECT_H
# define CW_GAME_OBJECT_H

#include "cw_obj_container.h"

#define	CW_COMMAND_AMOUNT	16 + 1

typedef struct			s_corewar
{
	t_flag				load_dump;
	t_flag				visualizator;

	int					players_amount;
	int					commands_amount;
	int					carriages_amount;
	int					queue_size;
	int					last_check_cycle;
	int					numerate_carriage;

	t_carriage			*p_carriage_obj;
	t_command			*pa_commands[CW_COMMAND_AMOUNT];
	t_player			*p_player_obj;
	t_arena				*p_arena_obj;

	t_queue				*p_execution_queue;
	t_stack				*p_distribution_stack;
	t_carriage			*p_waiting_queue;

	t_vis				*vis;

	void				(*cw_constructor)			(t_corewar **);
	void				(*cw_carriage_obj_init)		(t_corewar *);
	void				(*cw_command_obj_init)		(t_corewar *);
	void				(*cw_player_obj_init)		(t_corewar *, int, char **);
	void				(*cw_arena_obj_init)		(t_corewar *);
	void				(*cw_add_carriage_to_list)(t_corewar *, t_carriage *, int);
	void				(*cw_add_player_to_list)	(t_corewar *, t_player *);
	void				(*cw_free_all_carriages)	(t_corewar *);
	void				(*cw_free_all_players)		(t_corewar *);
	void 				(*cw_free_all_commands)		(t_corewar *);
	void				(*cw_arrange_units_on_field)(t_corewar *);
	void				(*cw_introduce_players)		(t_corewar *);
	void				(*cw_congratulations)		(t_corewar *);
	void				(*cw_main_checking)			(t_corewar *);
	void				(*cw_start_game)			(t_corewar *);
	void				(*cw_stack_obj_init)		(t_corewar *);
	void				(*cw_queue_obj_init)		(t_corewar *);
	void				(*cw_push_to_queue)			(t_corewar *, t_carriage *);
	void				(*cw_merge_queue_to_list)	(t_corewar *);
	void				(*cw_delete_carriage)		(t_corewar *, int *);
	void				(*cw_destructor)			(t_corewar **);
}						t_corewar;

void	cw_arena_obj_init(t_corewar *gameInstance);
void	cw_player_obj_init(t_corewar *p_game_instance, int argc, char **argv);
void	cw_stack_obj_init(t_corewar *p_game_instance);
void	cw_queue_obj_init(t_corewar *p_game_instance);
void	cw_carriage_obj_init(t_corewar *p_game_instance);
void	cw_command_obj_init(t_corewar *p_game_instance);
void	cw_add_player_to_list(t_corewar *p_game_instance, t_player *pPlayerAdding);
void	cw_add_t_carriageo_list(t_corewar *p_game_instance, t_carriage *pCarriageAdding, int ascending);
void	cw_free_all_players(t_corewar *p_game_instance);
void	cw_free_all_carriages(t_corewar *p_game_instance);
void	cw_free_all_commands(t_corewar *p_game_instance);
void	cw_introduce_players(t_corewar *gameInstance);
void	cw_congratulations(t_corewar *p_game_instance);
void	cw_arrange_units_on_field(t_corewar *p_game_instance);
void	cw_start_game(t_corewar *p_game_instance);
void	cw_main_checking(t_corewar *p_game_instance);
void	cw_delete_carriage(t_corewar *p_game_instance, int *p_del_car);
void	cw_push_to_queue(t_corewar *p_game_instance, t_carriage *p_adding_carriage);
void	cw_merge_queue_to_list(t_corewar *p_game_instance);

#endif
