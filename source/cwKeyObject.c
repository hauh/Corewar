/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwKeyObject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:37:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/10 19:30:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cwValidateArgs(key_t *pKeyInstance, int argc, char **argv)
{
	/*
	**	Stub
	*/
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

static void	cwDestructorKey(key_t **ppKeyInstance)
{
	free(*ppKeyInstance);
	*ppKeyInstance = NULL;
}

static void	cwConstructorKey(key_t **ppKeyInstance)
{
	(*ppKeyInstance)->loadDump = CW_FALSE;
	(*ppKeyInstance)->customId = CW_FALSE;
	(*ppKeyInstance)->graphics = CW_FALSE;
}

void		cwCreateInstanceKey(key_t **ppKeyObj)
{
	if (!(*ppKeyObj = (key_t *)malloc(sizeof(key_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_KEYS);
	(*ppKeyObj)->cwConstructorKey	= (const void *)&cwConstructorKey;
	(*ppKeyObj)->cwDestructorKey	= (const void *)&cwDestructorKey;
	(*ppKeyObj)->cwReadKeys			= (const void *)&cwReadKeys;
	(*ppKeyObj)->cwValidateArgs		= (const void *)&cwValidateArgs;
	(*ppKeyObj)->cwConstructorKey	(ppKeyObj);
}

/*
**--------------------------------------------------------------------------------------
*/