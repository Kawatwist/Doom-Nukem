/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:57:49 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/18 12:32:22 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_input(t_win **wn)
{
	if (!((*wn)->input = malloc(sizeof(t_input))))
		stop_exec("malloc inputfailed\n", *wn);
	if (!((*wn)->old = malloc(sizeof(Uint8*) * 284)))
		stop_exec("Malloc old input failed\n", *wn);
	SDL_PumpEvents();
	(*wn)->state = (Uint8*)SDL_GetKeyboardState(NULL);
	(*wn)->input->mouse = SDL_GetMouseState(&(*wn)->input->x, &(*wn)->input->y);
}
