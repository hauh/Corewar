/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwMain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/25 18:07:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **ppArgv)
{
	corewar_t	*pGameObj;

	cwCreateInstanceGame			(&pGameObj);
	pGameObj->cwArenaObjInit		(pGameObj);
	pGameObj->cwPlayerObjInit		(pGameObj, argc, ppArgv);
	pGameObj->cwCarriageObjInit		(pGameObj);
	pGameObj->cwCommandObjInit		(pGameObj);
	pGameObj->cwArrangeUnitsOnField	(pGameObj);
	pGameObj->cwIntroducePlayers	(pGameObj);
	pGameObj->cwStartGame			(pGameObj);
	pGameObj->cwCongratulations		(pGameObj);
	pGameObj->cwDestructor			(&pGameObj);
	return (CW_SUCCESS);
}
