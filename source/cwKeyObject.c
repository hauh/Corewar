/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwKeyObject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:37:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/14 16:04:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cwValidateArgs(key_t *pKeyInstance, int argc, char **argv)
{
	if (argc < 2)
		cwErrorCatcher(CW_NOT_VALID_KEY, CW_KEYS);
	return ;
}

static void	cwReadKeys(key_t *pKeyInstance, int argc, char **argv)
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
				if (argv[argIter][strIter]	== 'n' && argIter + 1 < argc)
				{
					pKeyInstance->customId	= ft_atoi(argv[argIter + 1]);
					argv[argIter + 1][0]	= CW_CHECK_SEAL;
				}
				else if (argv[argIter][strIter]	== 'd' && argIter + 1 < argc)
				{
					pKeyInstance->loadDump	= ft_atoi(argv[argIter + 1]);
					argv[argIter + 1][0] 	= CW_CHECK_SEAL;
				}
				else if (argv[argIter][strIter]	== 'v')
					pKeyInstance->graphics	= CW_TRUE;
				else
					cwErrorCatcher(CW_NOT_VALID_KEY, CW_KEYS);
				++strIter;
			}
			argv[argIter][0] = CW_CHECK_SEAL;
		}
		++argIter;
	}
}

/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructor(key_t **ppKeyInstance)
{
	(*ppKeyInstance)->loadDump = CW_FALSE;
	(*ppKeyInstance)->customId = CW_FALSE;
	(*ppKeyInstance)->graphics = CW_FALSE;
}

static void	cwDestructor(key_t **ppKeyInstance)
{
	free(*ppKeyInstance);
	*ppKeyInstance = NULL;
}

void		cwCreateInstanceKey(key_t **ppKeyObj)
{
	if (!(*ppKeyObj = (key_t *)malloc(sizeof(key_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_KEYS);
	(*ppKeyObj)->cwConstructor	= (const void *)&cwConstructor;
	(*ppKeyObj)->cwDestructor	= (const void *)&cwDestructor;
	(*ppKeyObj)->cwReadKeys		= (const void *)&cwReadKeys;
	(*ppKeyObj)->cwValidateArgs	= (const void *)&cwValidateArgs;
	(*ppKeyObj)->cwConstructor	(ppKeyObj);
}

/*
**--------------------------------------------------------------------------------------
*/