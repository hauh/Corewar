/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwMain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/05 17:56:24 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	corewar_t	*gameObj;

	cwCreateInstanceGame			(&gameObj);
	gameObj->cwConstructorGame		(gameObj);
	gameObj->cwKeyObjectInit		(gameObj, argc, argv);
	gameObj->cwPlayerObjectInit		(gameObj, argc, argv);
	gameObj->cwCarraigeObjectInit	(gameObj);
	gameObj->cwArenaObjectInit		(gameObj);
	gameObj->cwCommandObjectInit	(gameObj);
	gameObj->cwIntroducePlayers		(gameObj);
	gameObj->cwArrangeUnitsOnField	(gameObj);
	gameObj->cwStartGame			(gameObj);
	gameObj->cwDestructorGame		(gameObj);
	return (0);
}
