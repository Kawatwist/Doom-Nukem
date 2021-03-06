/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:49 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/21 18:11:15 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Rect	*create_rect(int x, int y, int w, int h)
{
	SDL_Rect	*pos;

	pos = malloc(sizeof(SDL_Rect));
	pos->x = x;
	pos->y = y;
	pos->w = w;
	pos->h = h;
	return (pos);
}

int		hitboxbox(t_myvec vec, t_rectbox box)
{
	if (vec.x >= box.x && vec.x <= (box.x + box.w))
		if (vec.y >= box.y && vec.y <= (box.y + box.h))
			if (vec.z >= box.z && vec.z <= (box.z + box.l))
				return (TRUE);
	return (FALSE);
}

int		hitbox(int	x, int	y, SDL_Rect *pos)
{
	if (x >= pos->x && y >= pos->y && x <= pos->x + pos->w && y <= pos->y + pos->h)
		return (TRUE);
	return (FALSE);
}

Uint32	set_bit(Uint32 var, Uint32 mask)
{
	var = ((var & mask) ? (var & (U_MAX - mask)) : (var | mask));
	return (var);
}

int	mouse_pressed(t_win *wn, Uint32 mask)
{
	if (!(wn->input->oldmouse & SDL_BUTTON(mask)) && (wn->input->mouse & SDL_BUTTON(mask)))
		return (TRUE);
	return (FALSE);
}

int	 key_pressed(t_win *wn, int key_value)
{
	if (wn->state[key_value] && !(wn->old[key_value]))
		return (TRUE);
	return (FALSE);
}