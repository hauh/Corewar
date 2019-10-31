/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/31 15:04:55 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CR_VIS_H
# define CR_VIS_H

# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <ncurses.h>
# include <locale.h>
# include <time.h>
# include "cw_game_obj.h"

/*
** ---------------------------
** Visual defines
*/

# define V_W 420 // <- с каретками
// # define V_W 136 + 60
# define V_H 100
# define V_SEP 136
# define V_SEPSEP (V_SEP + 60)
# define V_CARVOL (V_H / 3 - 3)
# define V_BSYM "\xe2\x96\x88"
# define V_BHALF "\xe2\x96\x93"
# define V_BQUARTER "\xe2\x96\x91"


/*
** ---------------------------
*/

/*
** ---------------------------
** Visual typedefs
*/

typedef struct			s_vis
{
	int					flow;
	int					step;
	int					exit;
	int					tick;
	int					fpsdiv;
	int					carinfo;
	int					info;
	int					startfrom;
	unsigned char		*field;
	long int			time;
	int					car_place;
}						t_vis;

enum						e_vis_act
{
	V_INIT,								// initialise the matp
	V_CONTROL,							// update time and check key input
	V_UPDATE,							// update the map (left section)
	V_CLEANUP							// clean allocated memory and get rid of the visuals
};

/*
** ---------------------------
*/

/*
** ---------------------------
** Visual declarations
*/

int							cr_vis_main					(t_corewar *cr, int act);
int							cr_vis_cleanup				(t_corewar *cr);
int							cr_vis_printattr			(int y, int x, char *str, int colour, int reverse);
int							cr_vis_initvis				(t_corewar *cr);
int							cr_vis_initcolour			(void);
int							cr_vis_initterm				(void);
void						cr_vis_putx					(int num, int i, int colour, int rev, t_corewar *cr);
int							cr_vis_drawborder			(void);
int							cr_vis_printmap				(unsigned char *f, int f_len, t_corewar *cr);
int							cr_vis_timer				(t_corewar *cr);
int							cr_vis_keys					(t_corewar *cr);
int							cr_vis_updatemap			(t_corewar *cr);
int							cr_vis_printinfo			(t_corewar *cr);
void						cr_vis_printcarinfo			(t_corewar *cr);
void						cr_vis_welcome				(t_corewar *cr);
void						cr_vis_winner				(t_corewar *cr);

/*
** ---------------------------
*/

#endif
