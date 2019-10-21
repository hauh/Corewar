/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwMain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/21 18:57:21 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	corewar_t	*pGameObj;

	cwCreateInstanceGame			(&pGameObj);
	/*
	** Init block
	*/
	pGameObj->cwArenaObjInit		(pGameObj);
	pGameObj->cwPlayerObjInit		(pGameObj, argc, argv);
	pGameObj->cwCarriageObjInit		(pGameObj);
	pGameObj->cwCommandObjInit		(pGameObj);
	pGameObj->cwArrangeUnitsOnField	(pGameObj);
	/*
	** Game process
	*/
	pGameObj->cwIntroducePlayers	(pGameObj);
	pGameObj->cwStartGame			(pGameObj);
	pGameObj->cwCongratulations		(pGameObj);
	pGameObj->cwDestructor			(&pGameObj);
	return (CW_SUCCESS);
}
