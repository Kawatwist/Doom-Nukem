/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor_display_right_pan.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 10:01:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/11 13:41:17 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <map_editor_right_pan.h>

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
	pan->j = 0;
	while(pan->j <= 4)
	{
		if (pan->j != 2)
		{
			pan->i = 4;
			pan->s_color = ft_setcolor(WHITE);
			pan->s_square = ft_setsquare(
					1920 - (pan->marge * pan->i) - (pan->width * pan->i) + (pan->width / 2),
 					pan->marge + (pan->j * pan->height) + (pan->j * pan->marge) + (pan->height / 4),
					pan->box_width,
					pan->box_height,
					pan->s_color);
			ft_draw_square(s_win, &(pan->s_square));
		}
		pan->j = pan->j + 1;
	}
}


void	ft_display_color_box(t_mywin *s_win, t_mypan *pan)
{
	char		*txt[10][10];
	t_mycolor	color[10][10];


	int i;
	int j;

	i = 0;
	while (i <= 4)
	{
		j = 0;
		while (j <= 3)
		{
			txt[i][j] = NULL;
			color[i][j] = ft_setcolor(-1, -1, -1);
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


	pan->j = 0;
	pan->i = 1;

	pan->j = 0;
	while (pan->j <= 4)
	{
		pan->i = 0;
		while (pan->i <= 3)
		{
			if (txt[pan->j][pan->i] != NULL)
			{
				pan->s_color = color[pan->j][pan->i];
				pan->s_square = ft_setsquare(
						1920 - (pan->marge * pan->i) - (pan->width * pan->i),
 						pan->marge + (pan->j * pan->height) + (pan->j * pan->marge),
						pan->width,
						pan->height,
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
}



void	ft_display_right_pan(t_mywin *s_win)
{
	t_mypan		pan;

	pan.marge = 80;
	pan.marge_text = 5;
	pan.indent_text = 15;
	pan.width = 150;
	pan.height = 100;
	pan.box_width = 70;
	pan.box_height = 50;
	pan.i = 0;
	pan.j = 0;

	ft_display_wall_height_text(s_win, &pan);
	ft_display_wall_texture_text(s_win, &pan);
	ft_display_floor_height_text(s_win, &pan);
	ft_display_floor_texture_text(s_win, &pan);
	ft_display_show_text(s_win, &pan);
	ft_display_box(s_win, &pan);
	ft_display_color_box(s_win, &pan);


	//	// CROSS
	//	t_mycross		s_cross;
	//	i = 4;
	//	j = 0;
	//	s_color = ft_setcolor(PINK);
	//	s_cross = ft_setcross(1920 - (marge * i) - (width * i) + (width / 2) + (box_width / 2),
	//			marge + (j * height) + (j * marge) + (height / 4) + (box_height / 2) -5,
	//			50, 10, s_color);
	//	ft_draw_cross(s_win, &s_cross);
	//
	//	// CROSS
	//	i = 4;
	//	j = 3;
	//	s_color = ft_setcolor(PINK);
	//	s_cross = ft_setcross(1920 - (marge * i) - (width * i) + (width / 2) + (box_width / 2),
	//			marge + (j * height) + (j * marge) + (height / 4) + (box_height / 2) -5,
	//			50, 10, s_color);
	//	ft_draw_cross(s_win, &s_cross);
}

