/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_obj.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:27:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 19:24:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_SCHEDULER_OBJECT_H
# define CW_SCHEDULER_OBJECT_H

//# include "cw_obj_container.h"

typedef struct		s_scheduler
{
	t_mark			nearest_cycle;

	void			(*cw_constructor)	(struct s_scheduler **);
	int				(*cw_action_phase)	(struct s_scheduler *);
	void			(*cw_destructor)	(struct s_scheduler **);
}					t_scheduler;

void				cw_create_instance_scheduler(t_scheduler **pp_scheduler_obj);

#endif
