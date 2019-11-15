/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/15 14:32:00 by dbrady           ###   ########.fr       */
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

# define V_W cr_vis_box_manager(V_BM_GET_VW) // <- с каретками
// # define V_W 136 + 60
# define V_H cr_vis_box_manager(V_BM_GET_VH)
# define V_SEP cr_vis_box_manager(V_BM_GET_VS)
# define V_SEPSEP cr_vis_box_manager(V_BM_GET_VSS)
# define V_CARVOL cr_vis_box_manager(V_BM_GET_VCARVOL)
# define V_BSYM "\xe2\x96\x88"
# define V_BHALF "\xe2\x96\x93"
# define V_BQUARTER "\xe2\x96\x91"
# define V_STEALTH "\xe2\x96\xa3"


/*
** ---------------------------
*/

/*
** ---------------------------
** Visual typedefs
*/

typedef struct			s_box
{
	int					vh;
	int					vw;
	int					vs;
	int					vss;
	int					vcarvol;
}						t_box;

typedef struct			s_vis
{
	int					flow;
	int					step;
	int					exit;
	int					tick;
	int					fpsdiv;
	int					carinfo;
	int					info;
	long int			time;
	int					car_place;
	int					sound_cur;
	long int			sound_time;
}						t_vis;

enum					e_vis_act
{
	V_INIT,								// initialise the matp
	V_CONTROL,							// update time and check key input
	V_UPDATE,							// update the map (left section)
	V_CLEANUP,							// clean allocated memory and get rid of the visuals
	V_LEFT,
	V_MID,
	V_RIGHT,
	V_SCREEN,
};

enum					e_vis_print
{
	VPN,							// print normal number (also, VPN, lol)
	VPNR,							// print normal number with carriage on it
	VPS,								// print stealth characters insted of numbers
	VPSR,							// stealth with carriage
};

enum					e_vis_boxmanager
{
	V_BM_SET_MINI,
	V_BM_SET_NORMAL,
	V_BM_GET_VH,
	V_BM_GET_VW,
	V_BM_GET_VS,
	V_BM_GET_VSS,
	V_BM_GET_VCARVOL,
	V_BM_CLEAR,
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
int							cr_vis_printattr			(int *xy, char *str, int colour, int reverse);
int							cr_vis_initvis				(t_corewar *cr);
int							cr_vis_initcolour			(void);
int							cr_vis_initterm				(void);
void						cr_vis_putx					(int num, int i, int colour, int rev);
int							cr_vis_printmap				(unsigned char *f, int f_len, t_corewar *cr);
int							cr_vis_timer				(t_corewar *cr);
int							cr_vis_keys					(t_corewar *cr);
int							cr_vis_updatemap			(t_corewar *cr);
int							cr_vis_printinfo			(t_corewar *cr);
void						cr_vis_printcarinfo			(t_corewar *cr);
void						cr_vis_welcome				(t_corewar *cr);
void						cr_vis_winner				(t_corewar *cr);
void						cr_vis_buildbox				(int part);
void						cr_vis_clearbox				(int part);
int							cr_vis_printhealth			(t_corewar *cr);
int							cr_vis_lastlive				(t_corewar *cr, int id);
void						cr_vis_sound				(t_vis *vis, int piece);
void						cr_vis_sound_sellout		(t_corewar *cr);
int							cr_vis_printattr_stealth	(int i, int colour, int flag);
int							cr_vis_box_manager			0(int	action);

/*
** ---------------------------
*/

#endif
