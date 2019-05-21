/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:49 by jleblond          #+#    #+#             */
/*   Updated: 2019/05/21 12:58:24 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	set_bit(Uint32 var, Uint32 mask)
{
	var = ((var & mask) ? (var & (U_MAX - mask)) : (var | mask));
	return (var);
}

int	 key_pressed(t_win *wn, int key_value)
{
	if (wn->state[key_value] && !(wn->old[key_value]))
		return (TRUE);
	return (FALSE);
}

