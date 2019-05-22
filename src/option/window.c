/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:19:56 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/21 10:58:28 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	full_screen(t_win *wn)
{
	if (wn->full_screen == -1)
	{
		SDL_SetWindowFullscreen(wn->window, SDL_WINDOW_FULLSCREEN);
		SDL_GetWindowSize(wn->window, &wn->xscreen, &wn->yscreen);
	}
	else if (wn->full_screen == 1)
	{
		wn->xscreen = XSCREEN;
		wn->yscreen = YSCREEN;
		SDL_SetWindowSize(wn->window, wn->xscreen, wn->yscreen);
		SDL_SetWindowFullscreen(wn->window, 0);
		SDL_RestoreWindow(wn->window);
	}
}
