/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor_ihc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 09:19:14 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/11 10:03:00 by jchardin         ###   ########.fr       */
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

	s_color = ft_setcolor(WHITE);
	s_square = ft_setsquare(50,
 			900,
			100,
			50,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(BLACK);
	s_write = ft_setwrite(50 + 15,
 			910,
			s_color, 20, "SAVE");
	ft_write(s_win, &s_write);
}

void	ft_display_quit_button(t_mywin *s_win)
{
	t_mycolor		s_color;
	t_mysquare		s_square;
	t_mywrite		s_write;

	s_color = ft_setcolor(WHITE);
	s_square = ft_setsquare(
			250,
 			900,
			100,
			50,
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
}

void	ft_display_grid(t_mywin *s_win)
{
	t_mygrid	s_grid;
	s_grid = ft_setgrid(50, 100, 700, 900);
	ft_draw_grid(s_win, &s_grid);
}


void	ft_display_ihc(t_mywin *s_win)
{
	ft_display_title(s_win);
	ft_display_save_button(s_win);
	ft_display_quit_button(s_win);
	ft_display_grid(s_win);
	ft_display_right_pan(s_win);;
}


