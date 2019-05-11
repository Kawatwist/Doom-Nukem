/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:39:30 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/11 14:56:08 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	ft_launch_map_editor(t_mywin *s_win, t_win *wn)
{
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	ft_display_ihc(s_win);
	SDL_RenderPresent(s_win->renderer[J_EDITOR]);
	while (TRUE)
	{
		SDL_PollEvent(&(wn->ev));
		wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
		printf("mouse x=%d y=%d\n", wn->input->x, wn->input->y);
		if (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			printf("TU A CLIKKKKKKKKKKKKKKKKKKKKKKKKK\n");
		}
		SDL_Delay(10);
	}
}





	//	SQUARE
	//	s_color = ft_setcolor(255, 255, 255);
	//	t_mysquare		s_square;
	//	s_square = ft_setsquare(10, 10, 100, 100, s_color);
	//	ft_draw_square(s_win, &s_square);
	// CROSS
	//	s_color = ft_setcolor(0, 255, 0);
	//	t_mycross		s_cross;
	//	s_cross = ft_setcross(100, 100, 50, 10, s_color);
	//	ft_draw_cross(s_win, &s_cross);
	//WRITE
	//	s_color = ft_setcolor(0, 0, 255);
	//	t_mywrite	s_write;
	//	s_write = ft_setwrite(10, 10, s_color, 24, "ma phrase");
	//	ft_write(s_win, &s_write);
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

