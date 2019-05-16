/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor_ihc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 09:19:14 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/16 13:58:55 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <map_editor_right_pan.h>

void	ft_display_title(t_mywin *s_win)
{
	t_mycolor		s_color;
	t_mywrite	s_write;

	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(
			100,
			10,
 			s_color,
			24,
			"Doom Map Editor  (en attendant celui de Laetitia)");
	ft_write(s_win, &s_write);
}

void	ft_display_save_button(t_mywin *s_win)
{
	t_mycolor	s_color;
	t_mysquare	s_square;
	t_mywrite	s_write;
	t_mysquare	*s_localisation_save_button;

	s_localisation_save_button = malloc(sizeof(t_mysquare));
	s_color = ft_setcolor(WHITE);

	s_localisation_save_button->x = 50;
	s_localisation_save_button->y = 900;
	s_localisation_save_button->width = 100;
	s_localisation_save_button->height = 50;
	s_square = ft_setsquare(
			s_localisation_save_button->x,
 			s_localisation_save_button->y,
			s_localisation_save_button->width,
			s_localisation_save_button->height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(BLACK);
	s_write = ft_setwrite(50 + 15,
 			910,
			s_color, 20, "SAVE");
	ft_write(s_win, &s_write);
	s_win->s_localisation_save_button = s_localisation_save_button;
}

void	ft_display_quit_button(t_mywin *s_win)
{
	t_mycolor		s_color;
	t_mysquare		s_square;
	t_mywrite		s_write;
	t_mysquare		*s_localisation_quit_button;

	s_localisation_quit_button = malloc(sizeof(t_mysquare));
	s_localisation_quit_button->x = 250;
	s_localisation_quit_button->y = 900;
	s_localisation_quit_button->width = 100;
	s_localisation_quit_button->height = 50;
	s_color = ft_setcolor(WHITE);
	s_square = ft_setsquare(
			s_localisation_quit_button->x,
 			s_localisation_quit_button->y,
			s_localisation_quit_button->width,
			s_localisation_quit_button->height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(BLACK);
	s_write = ft_setwrite(
			265,
 			910,
			s_color,
			20,
			"EXIT");
	ft_write(s_win, &s_write);
	s_win->s_localisation_quit_button = s_localisation_quit_button;
}

void	ft_display_grid(t_mywin *s_win)
{
	t_mygrid	s_grid;
	//t_mygrid	ft_setgrid(int x, int y, int height, int width)
	t_mygrid	*s_grid_location;

	s_grid_location = malloc(sizeof(t_mysquare));
	s_grid_location->x = 50;
	s_grid_location->y = 100;
	s_grid_location->width = 900;
	s_grid_location->height = 700;
	s_grid_location->step = 30;

	s_grid = ft_setgrid(50, 100, 900, 700, 30);
	ft_draw_grid(s_win, &s_grid);
	s_win->s_localisation_grid = s_grid_location;
}

void	ft_draw_map(t_mywin *s_win)
{
	t_mywall *keep;
	t_myputtheline		s_line;

	keep = s_win->lst_wall;
	while (s_win->lst_wall)
	{
		s_line.un.a = (s_win->lst_wall->x_a * s_win->s_localisation_grid->step)
			+ s_win->s_localisation_grid->x;
		s_line.un.b = (s_win->lst_wall->y_a * s_win->s_localisation_grid->step)
			+ s_win->s_localisation_grid->y;
		s_line.deux.a = (s_win->lst_wall->x_b * s_win->s_localisation_grid->step)
			+ s_win->s_localisation_grid->x;
		s_line.deux.b = (s_win->lst_wall->y_b * s_win->s_localisation_grid->step)
			+ s_win->s_localisation_grid->y;


		if (s_win->lst_wall->height == up_to_ceilling)
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], BLUE, 255);
		if (s_win->lst_wall->height == middle)
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], GREEN, 255);
		if (s_win->lst_wall->height == down)
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], RED, 255);
		if (s_win->lst_wall->height == -1)
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], YELLOW, 255);
		if (s_win->lst_wall->current_wall == 1)
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);//blanc
		ft_draw_line(s_win, &s_line);
		s_win->lst_wall = s_win->lst_wall->next;
	}
	s_win->lst_wall = keep;
}

void	ft_display_ihc(t_mywin *s_win)
{
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	ft_display_title(s_win);
	ft_display_save_button(s_win);
	ft_display_quit_button(s_win);
	ft_display_grid(s_win);
	ft_draw_map(s_win);
	ft_display_right_pan(s_win);;
	SDL_RenderPresent(s_win->renderer[J_EDITOR]);
}
