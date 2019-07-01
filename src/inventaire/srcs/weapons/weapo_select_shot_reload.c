/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_shot_reoad.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:07:27 by naali             #+#    #+#             */
/*   Updated: 2019/06/28 14:14:30 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventaire.h"

void		select_shot_reload(t_weapons *weap, int type)
{
	if (type == CAC)
	{
		weap->shoot = &cac_shot;
		weap->reload = &cac_reload;
	}
	else if (type == RANGE)
	{
		weap->shoot = &range_shot;
		weap->reload = &range_reload;
	}
	else if (type == ZONE)
	{
		weap->shoot = &area_shot;
		weap->reload = &area_reload;
	}
}
