/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:43:32 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/04 17:49:36 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		ft_launch_window(t_mywin *s_win)
{
	s_win->window[J_EDITOR] = NULL;
	s_win->renderer[J_EDITOR] = NULL;
	if (!(s_win->window[J_EDITOR] = SDL_CreateWindow("J map editor", 10, 10, 1920, 1080, SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[J_EDITOR] = SDL_CreateRenderer(s_win->window[J_EDITOR],0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
}
