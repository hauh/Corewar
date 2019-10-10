/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwMain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/10 19:36:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	corewar_t	*pGameObj;

	cwCreateInstanceGame			(&pGameObj);
	pGameObj->cwKeyObjectInit		(pGameObj, argc, argv);
	int i = 1;
	while (i < argc)
		printf("%s\n", argv[i++]);
	printf("%d %d %d\n", pGameObj->pKeyObject->loadDump, pGameObj->pKeyObject->customId, pGameObj->pKeyObject->graphics);
	exit(1);
	pGameObj->cwPlayerObjectInit	(pGameObj, argc, argv);
	pGameObj->cwCarraigeObjectInit	(pGameObj);
	pGameObj->cwArenaObjectInit		(pGameObj);
	pGameObj->cwCommandObjectInit	(pGameObj);
	pGameObj->cwIntroducePlayers	(pGameObj);
	pGameObj->cwArrangeUnitsOnField	(pGameObj);
	pGameObj->cwStartGame			(pGameObj);
	pGameObj->cwCongratulations		(pGameObj);
	pGameObj->cwDestructorGame		(&pGameObj);
	return (0);
}
