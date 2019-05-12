/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:59:53 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/12 13:04:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setkeyboard(Uint8 *new, Uint8 *current)
{
	int	i;

	i = 0;
	while (i < 284)
	{
		new[i] = current[i];
		i++;
	}
}

void	gameinput(t_win *wn)
{
	(wn->player->rawx += (wn->input->x - (XSCREEN / 2))) > 360
		? wn->player->rawx -= 360 : 0;
	(wn->player->rawy += (wn->input->y - (YSCREEN / 2))) > YSCREEN
		? wn->player->rawy = YSCREEN : 0;
	wn->player->rawx < 0 ? wn->player->rawx += 360 : 0;
	wn->player->rawy < 0 ? wn->player->rawy = 0 : 0;
	!wn->old[SDL_SCANCODE_ESCAPE] && wn->state[SDL_SCANCODE_ESCAPE] && wn->debug == -1 ? wn->interface = MENU : 0;
	wn->state[SDL_SCANCODE_KP_PLUS] ? wn->player->sensi += 0.1 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS] ? wn->player->sensi -= 0.1 : 0;
}
