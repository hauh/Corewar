/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwKeyObject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:37:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 19:56:57 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwValidateArgs(corewar_t *game, char **argv, int argc)
{
	/*
	**	Stub
	*/
	return ;
}

void	cwReadKeys(key_t *keyInstance, int argc, char **argv)
{
	int	argIter;
	int	strIter;

	argIter = CW_BEGIN_FROM_ONE;
	while (argIter < argc)
	{
		if (argv[argIter][0] == '-')
		{
			strIter = CW_BEGIN_FROM_ONE;
			while (argv[argIter][strIter])
			{
				if (argv[argIter][strIter]	== 'n')
				{
					keyInstance->customId	= CW_TRUE;
					keyInstance->userId		= ft_atoi(argv[argIter + 1]);
					argv[argIter + 1][0]	= '*';
				}
				else if (argv[argIter][strIter]	== 'd')
				{
					keyInstance->loadDump	= CW_TRUE;
					keyInstance->userDump	= ft_atoi(argv[argIter + 1]);
					argv[argIter + 1][0] 	= '*';
				}
				else if (argv[argIter][strIter]	== 'v')
					keyInstance->graphics	= CW_TRUE;
				else
					cwErrorCatcher(CW_NOT_VALID_KEY, CW_KEYS);
				++strIter;
			}
			argv[argIter][0] = '*';
		}
		++argIter;
	}
}

void	cwDestructorKey(key_t **keyInstance)
{
	free(*keyInstance);
	*keyInstance = NULL;
}

void	cwConstructorKey(key_t **keyInstance)
{
	(*keyInstance)->loadDump		= CW_FALSE;
	(*keyInstance)->customId		= CW_FALSE;
	(*keyInstance)->graphics		= CW_FALSE;
	(*keyInstance)->cwReadKeys		= &cwReadKeys;
	(*keyInstance)->cwValidateArgs	= &cwValidateArgs;
}

void	cwCreateInstanceKey(key_t **keyObj)
{
	if (!(*keyObj = (key_t *)malloc(sizeof(key_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_KEYS);
	(*keyObj)->cwConstructorKey	= &cwConstructorKey;
	(*keyObj)->cwDestructorKey	= &CW_DESTRUCTOR;
}