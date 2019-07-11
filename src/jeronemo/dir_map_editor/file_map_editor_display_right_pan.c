/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor_display_right_pan.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 10:01:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/07 14:08:28 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_display_wall_height_text(t_mywin *s_win, t_mypan *pan)
{
	pan->j = 0;
	pan->s_color = ft_setcolor(WHITE);
	pan->s_write = ft_setwrite(
			1920 - (2 * pan->width) - (4 * pan->marge),
			((pan->j + 1) * pan->height) + (pan->j * pan->marge)  - (pan->height / 2),
			pan->s_color,
			24,
			"Wall Height");
	ft_write(s_win, &(pan->s_write));
}

void	ft_display_wall_texture_text(t_mywin *s_win, t_mypan *pan)
{
	pan->j = 1;
	pan->s_color = ft_setcolor(WHITE);
	pan->s_write = ft_setwrite(
			1920 - (2 * pan->width) - (4 * pan->marge),
 			((pan->j + 1) * pan->height) + (pan->j * pan->marge) - (pan->height / 2) ,
			pan->s_color,
			24,
			"Wall Texture");
	ft_write(s_win, &pan->s_write);
}

void	ft_display_floor_height_text(t_mywin *s_win, t_mypan *pan)
{
	pan->j = 3;
	pan->s_color = ft_setcolor(WHITE);
	pan->s_write = ft_setwrite(
			1920 - (2 * pan->width) - (4 * pan->marge),
 			((pan->j + 1) * pan->height) + (pan->j * pan->marge)  - (pan->height / 2),
			pan->s_color,
			24,
			"Floor Height");
	ft_write(s_win, &pan->s_write);
}

void	ft_display_floor_texture_text(t_mywin *s_win, t_mypan *pan)
{
	pan->j = 4;
	pan->s_color = ft_setcolor(WHITE);
	pan->s_write = ft_setwrite(
			1920 - (2 * pan->width) - (4 * pan->marge),
 			((pan->j + 1) * pan->height) + (pan->j * pan->marge) - (pan->height / 2) ,
			pan->s_color,
			24,
			"Floor Texture");
	ft_write(s_win, &pan->s_write);
}

void	ft_display_show_text(t_mywin *s_win, t_mypan *pan)
{
	pan->j = 5;
	pan->s_color = ft_setcolor(WHITE);
	pan->s_write = ft_setwrite(
			1920 - (2 * pan->width) - (3 * pan->marge) - 280,
			30,
			pan->s_color,
			19,
			"SHOW");
	ft_write(s_win, &pan->s_write);
}

void	ft_display_box(t_mywin *s_win, t_mypan *pan)
{
	t_mylocalisation_box		*s_localisation_box;

	s_localisation_box = malloc(sizeof(t_mylocalisation_box) * 5);

	pan->j = 0;
	pan->i = 4;
	while(pan->j <= 4)
	{
		if (pan->j != 2)
		{
			pan->s_color = ft_setcolor(WHITE);
			s_localisation_box[pan->j].x = 1920 - (pan->marge * pan->i) - (pan->width * pan->i) + (pan->width / 2);
			s_localisation_box[pan->j].y = pan->marge + (pan->j * pan->height) + (pan->j * pan->marge) + (pan->height / 4);
			s_localisation_box[pan->j].width = pan->box_width;
			s_localisation_box[pan->j].height = pan->box_height;
			pan->s_square = ft_setsquare(
					s_localisation_box[pan->j].x,
 					s_localisation_box[pan->j].y,
					s_localisation_box[pan->j].width,
					s_localisation_box[pan->j].height,
					pan->s_color);
			ft_draw_square(s_win, &(pan->s_square));
		}
		pan->j = pan->j + 1;
	}
	s_win->s_localisation_box = s_localisation_box;
}

void	ft_display_color_box(t_mywin *s_win, t_mypan *pan)
{
	char		*txt[5][4];
	t_mycolor	color[5][4];
	int i;
	int j;
	t_mysquare		***s_localisation_color_box;
	s_localisation_color_box = NULL;

	s_localisation_color_box = malloc(sizeof(t_mysquare **) * 6);
	i = 0;
	while (i <= 4)
	{
		s_localisation_color_box[i] = malloc(sizeof(t_mysquare *) * 5);
		j = 0;
		while (j <= 3)
		{
			s_localisation_color_box[i][j] = malloc(sizeof(t_mysquare));
			txt[i][j] = NULL;
			color[i][j] = ft_setcolor(-1, -1, -1);
			s_localisation_color_box[i][j]->x = -1;
			j++;
		}
		i++;
	}

	txt[0][1] = ft_strdup("Down");
	color[0][1] = ft_setcolor(RED);
	txt[0][2] = ft_strdup("Middle");
	color[0][2] = ft_setcolor(GREEN);
	txt[0][3] = ft_strdup("Up to ceiling");
	color[0][3] = ft_setcolor(BLUE);
	txt[1][1] = ft_strdup("File needed");
	color[1][1] = ft_setcolor(PINK);
	txt[1][2] = ft_strdup("file needed");
	color[1][2] = ft_setcolor(YELLOW);
	txt[1][3] = ft_strdup("file needed");
	color[1][3] = ft_setcolor(ORANGE);
	txt[3][1] = ft_strdup("Down");
	color[3][1] = ft_setcolor(RED);
	txt[3][2] = ft_strdup("Middle");
	color[3][2] = ft_setcolor(GREEN);
	txt[3][3] = ft_strdup("Hight");
	color[3][3] = ft_setcolor(BLUE);
	txt[4][1] = ft_strdup("file needed");
	color[4][1] = ft_setcolor(PINK);
	txt[4][2] = ft_strdup("file needed");
	color[4][2] = ft_setcolor(YELLOW);
	txt[4][3] = ft_strdup("file needed");
	color[4][3] = ft_setcolor(ORANGE);


	pan->i = 1;
	pan->j = 0;
	while (pan->j <= 4)
	{
		pan->i = 0;
		while (pan->i <= 3)
		{
			if (txt[pan->j][pan->i] != NULL)
			{
				s_localisation_color_box[pan->j][pan->i]->x = 1920 - (pan->marge * pan->i) - (pan->width * pan->i);
				s_localisation_color_box[pan->j][pan->i]->y = pan->marge + (pan->j * pan->height) + (pan->j * pan->marge);
				s_localisation_color_box[pan->j][pan->i]->width = pan->width;
				s_localisation_color_box[pan->j][pan->i]->height = pan->height;
				pan->s_color = color[pan->j][pan->i];
				pan->s_square = ft_setsquare(
						s_localisation_color_box[pan->j][pan->i]->x,
 						s_localisation_color_box[pan->j][pan->i]->y,
						s_localisation_color_box[pan->j][pan->i]->width,
						s_localisation_color_box[pan->j][pan->i]->height,
						pan->s_color);
				ft_draw_square(s_win, &(pan->s_square));
				pan->s_color = ft_setcolor(WHITE);
				pan->s_write = ft_setwrite(
						1920 - (pan->marge * pan->i) - (pan->width * pan->i) + pan->indent_text,
 						pan->marge + pan->marge_text + ((pan->j + 1) * pan->height) + (pan->j * pan->marge),
						pan->s_color,
						14,
						txt[pan->j][pan->i]);
				ft_write(s_win, &(pan->s_write));
			}
			pan->i = pan->i + 1;
		}
		pan->j = pan->j + 1;
	}
	s_win->s_localisation_color_box = s_localisation_color_box;
}

void	ft_display_cross(t_mywin *s_win,t_mypan *pan)
{
	t_mycross		s_cross;

	pan->i = 4;
	pan->j = 0;
	while (pan->j <= 4)
	{
		if (s_win->show_cross[pan->j] == 1)
		{
			pan->s_color = ft_setcolor(PINK);
			s_cross = ft_setcross(1920 - (pan->marge * pan->i) - (pan->width * pan->i) + (pan->width / 2) + (pan->box_width / 2),
					pan->marge + (pan->j * pan->height) + (pan->j * pan->marge) + (pan->height / 4) + (pan->box_height / 2) - 5,
					50, 10, pan->s_color);
			ft_draw_cross(s_win, &s_cross);
		}
		pan->j = pan->j + 1;
	}
}

void	ft_display_right_pan(t_mywin *s_win)
{
	t_mypan		pan;

	pan.marge = 80;
	pan.marge_text = 5;
	pan.indent_text = 15;
	pan.width = 150;
	pan.height = 100;
	pan.box_width = 70; pan.box_height = 50;
	pan.i = 0;
	pan.j = 0;

	ft_display_wall_height_text(s_win, &pan);
	ft_display_wall_texture_text(s_win, &pan);
	ft_display_floor_height_text(s_win, &pan);
	ft_display_floor_texture_text(s_win, &pan);
	ft_display_show_text(s_win, &pan);
	ft_display_box(s_win, &pan);
	ft_display_color_box(s_win, &pan);
	ft_display_cross(s_win, &pan);
}
