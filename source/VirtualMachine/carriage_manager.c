/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/17 19:17:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

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

int get_waiting_time(int command)
{
	if (command == 0x01 || command == 0x04 || command == 0x05 || command == 0x0d)
		return (10);
	else if (command == 0x02 || command == 0x03)
		return (5);
	else if (command == 0x06 || command == 0x07 || command == 0x08)
		return (6);
	else if (command == 0x09)
		return (20);
	else if (command == 0x0a || command == 0x0b)
		return (25);
	else if (command == 0x0c)
		return (800);
	else if (command == 0x0e)
		return (50);
	else if (command == 0x0f)
		return (1000);
	else if (command == 0x10)
		return (2);
}

carriage_t			*new_carriage(int owner, int id, int current_location, int current_command, int waiting_time, int step_bytes)
{
	carriage_t		*new_carriage;

	new_carriage = (carriage_t *)malloc(sizeof(carriage_t));
	new_carriage->id = id;
	new_carriage->player_id = owner;
	new_carriage->carry_flag = 0;
	new_carriage->last_live_loop = 0;
	new_carriage->waiting_time = waiting_time;
	new_carriage->step_bytes = step_bytes;
	new_carriage->current_command = current_command;
	new_carriage->current_location = current_location;
	new_carriage->registers = (int *)malloc(sizeof(int) * REG_NUMBER);
	memset(new_carriage->registers, 0, REG_SIZE * REG_NUMBER);
	return (new_carriage);
}

void				add_carriage(carriage_list_t **list, carriage_t *carriage)
{
	carriage_list_t	*new_elem;

	new_elem = (carriage_list_t *)malloc(sizeof(carriage_list_t));
	if (!list)
	{
		printf("Some error, i don't know how but you crash my program, go away\n");
		exit(-1);
	}
	if (!*list)
	{
		*list = new_elem;
		(*list)->current_carriage = carriage;
		(*list)->next = NULL;
		(*list)->prev = NULL;
		return ;
	}
	new_elem->current_carriage = carriage;
	new_elem->next = *list;
	new_elem->prev = NULL;
	(*list)->prev = new_elem;
	*list = new_elem;
}