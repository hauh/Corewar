/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_sound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:19:25 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/15 17:53:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cr_play_sound(char *filename)
{
	static int	status = 1;
	char		*command;

	if (status == 1)
	{
		command = ft_strjoin("afplay ", filename);
		if (system(command) == -1)
			status = 2;
		free(command);
	}
	if (status == 2)
	{
		command = ft_strjoin("aplay ", filename);
		if (system(command) == -1)
			status = 0;
		free(command);
	}
}

static void		cr_stop_sound(void)
{
	if (system("pkill afplay") != -1)
		return ;
	if (system("pkill aplay") != -1)
		return ;
}

static void		cr_vis_sound_swap_or_timer(t_vis *vis, int piece)
{
	cr_stop_sound();
	if (piece == vis->sound_cur)
	{
		if (piece == 'k')
			cr_play_sound("./res/k.mp3");
		else if (piece == 'b')
			cr_play_sound("./res/b.mp3");
		vis->sound_cur = piece;
	}
	else
	{
		if (piece == 'k' && (vis->time - vis->sound_time) / CLOCKS_PER_SEC > 180)
			cr_play_sound("./res/k.mp3");
		else if
			(piece == 'b' && (vis->time - vis->sound_time) / CLOCKS_PER_SEC > 72)
			cr_play_sound("./res/b.mp3");
	}
}

void			cr_vis_sound_sellout(t_corewar *cr)
{
	if (cr->p_arena_obj->cycle == 6001)
		cr_play_sound("./res/dc.mp3");
	else if (cr->p_arena_obj->cycle == 12001)
		cr_play_sound("./res/ctm.mp3");
	else if (cr->p_arena_obj->cycle == 18001)
		cr_play_sound("./res/raid.mp3");
	else if (cr->p_arena_obj->cycle == 24001)
		cr_play_sound("./res/vavada.mp3");
}

void			cr_vis_sound(t_vis *vis, int piece)
{
	if (piece == 'h')
	{
		cr_stop_sound();
		vis->sound_cur = 0;
	}
	else
	{
		if (!vis->sound_cur)
		{
			if (piece == 'k')
				cr_play_sound("./res/k.mp3");
			else
				cr_play_sound("./res/b.mp3");
			vis->sound_cur = piece;
		}
		cr_vis_sound_swap_or_timer(vis, piece);
	}
}
