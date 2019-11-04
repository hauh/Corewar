/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_sound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:19:25 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/04 17:30:54 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cr_vis_sound(t_vis *vis, int act, int piece)
{
	if (act == V_MSTOP)
	{
		system("(pkill afplay)");
		vis->sound_cur = 0;
	}
	else
	{
		if (!vis->sound_cur)
		{
			if (piece == 'k')
				system("(afplay ./res/k.mp3&)");
			else
				system("(afplay ./res/b.mp3&)");
			vis->sound_cur = piece;
		}
		if (piece == vis->sound_cur)
		{
			if (piece == 'k' && (vis->time - vis->sound_time)/CLOCKS_PER_SEC > 180)
				system("(pkill afplay) && (afplay ./res/k.mp3&)");
			else if (piece == 'b' && (vis->time - vis->sound_time)/CLOCKS_PER_SEC > 72)
				system("(pkill afplay) && (afplay ./res/b.mp3&)");
		}
		else
		{
			if (piece == 'k')
				system("(pkill afplay) && (afplay ./res/k.mp3&)");
			else if (piece == 'b')
				system("(pkill afplay) && (afplay ./res/b.mp3&)");
			vis->sound_cur = piece;	
		}
	}
}