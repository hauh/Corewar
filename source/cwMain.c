/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwMain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/12 21:02:44 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	corewar_t	*pGameObj;

	cwCreateInstanceGame			(&pGameObj);
	pGameObj->cwKeyObjectInit		(pGameObj, argc, argv);
	pGameObj->cwPlayerObjectInit	(pGameObj, argc, argv);
	pGameObj->cwCarraigeObjectInit	(pGameObj);
	pGameObj->cwArenaObjectInit		(pGameObj);
	pGameObj->cwCommandObjectInit	(pGameObj);
	for (int i = 1; i < 17 ; ++i)
	{
		ft_printf("%d\n", pGameObj->paCommands[i]->id);
		ft_printf("%08b\n", pGameObj->paCommands[i]->firstArg);
		ft_printf("%08b\n", pGameObj->paCommands[i]->secondArg);
		ft_printf("%08b\n", pGameObj->paCommands[i]->thirdArg);
		ft_printf("Time: %d\n", pGameObj->paCommands[i]->waitingTime);
		ft_printf("DirSize: %d\n", pGameObj->paCommands[i]->dirSize);
		ft_printf("Type: %d\n", pGameObj->paCommands[i]->typeByte);
	}
	exit(1);
	pGameObj->cwIntroducePlayers	(pGameObj);
	pGameObj->cwArrangeUnitsOnField	(pGameObj);
	pGameObj->cwStartGame			(pGameObj);
	pGameObj->cwCongratulations		(pGameObj);
	pGameObj->cwDestructorGame		(&pGameObj);
	return (0);
}
