/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_sound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:19:25 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/11 16:17:19 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cr_vis_sound_swap(t_vis *vis, int piece)
{
	if (piece == 'k')
		system("(pkill afplay) && (afplay ./res/k.mp3&)");
	else if (piece == 'b')
		system("(pkill afplay) && (afplay ./res/b.mp3&)");
	vis->sound_cur = piece;
}

static void		cr_vis_sound_timer(t_vis *vis, int piece)
{
	if (piece == 'k' && (vis->time - vis->sound_time) / CLOCKS_PER_SEC > 180)
		system("(pkill afplay) && (afplay ./res/k.mp3&)");
	else if
	(piece == 'b' && (vis->time - vis->sound_time) / CLOCKS_PER_SEC > 72)
		system("(pkill afplay) && (afplay ./res/b.mp3&)");
}

void			cr_vis_sound_sellout(t_corewar *cr)
{
	if (cr->p_arena_obj->cycle_amount == 7001)
		system("(afplay ./res/dc.mp3)");
	else if (cr->p_arena_obj->cycle_amount == 14001)
		system("(afplay ./res/ctm.mp3)");
	else if (cr->p_arena_obj->cycle_amount == 21001)
		system("(afplay ./res/raid.mp3)");
}

void			cr_vis_sound(t_vis *vis, int piece)
{
	if (piece == 'h')
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
			cr_vis_sound_timer(vis, piece);
		else
			cr_vis_sound_swap(vis, piece);
	}
}
