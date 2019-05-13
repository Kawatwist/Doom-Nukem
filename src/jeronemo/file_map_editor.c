/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:39:30 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/13 16:47:42 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>



void	ft_launch_map_editor(t_mywin *s_win, t_win *wn)
{
	int		quit;


	ft_init_show_cross(s_win);
	ft_launch_window(s_win);
	ft_display_ihc(s_win);
	quit = FALSE;
	while (!quit)
	{
		SDL_PollEvent(&(wn->ev));
		wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
		//printf("mouse x=%d y=%d\n", wn->input->x, wn->input->y);
		if (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			ft_update_show_cross(s_win, wn);
			ft_display_ihc(s_win);
		}
		if (wn->state[SDL_SCANCODE_ESCAPE])
			quit = TRUE;
		SDL_Delay(10);
	}
}


//READMAP
//t_mywall	*s_wall;
//s_wall = ft_read_map();
//DRAW GRID
//t_mygrid	s_grid;
//s_grid = ft_setgrid(10, 10, 300, 500);
//ft_draw_grid(s_win, &s_grid);
//DRAW WALL
//	t_mypoint	s_point_a;
//	t_mypoint	s_point_b;
//	s_point_a = ft_setpoint(20, 40);
//	s_point_b = ft_setpoint(50, 100);
//	t_mywall	s_wall;
//	s_wall = ft_setwall(s_point_a, s_point_b, 2, 4);
//	ft_draw_wall(s_win, &s_wall);

