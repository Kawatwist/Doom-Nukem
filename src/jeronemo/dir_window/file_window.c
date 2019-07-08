/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:43:32 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 13:13:30 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void		ft_launch_window(t_mywin *s_win, t_win *wn)
{
	s_win->window = malloc(sizeof(SDL_Window *));
	s_win->window[0] = wn->window;
	s_win->renderer = malloc(sizeof(SDL_Renderer *));
	s_win->renderer[0] = wn->rend;/*
	if (!(s_win->window[interface] = SDL_CreateWindow("J map editor", 10, 10, XSCREEN, YSCREEN, SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[interface] = SDL_CreateRenderer(s_win->window[interface],0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
		ft_clear_window(s_win);*/
}

void		ft_clear_window(t_mywin *s_win)
{
	SDL_SetRenderDrawColor(s_win->renderer[0], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[0]);
}
