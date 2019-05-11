/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor_display_right_pan.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 10:01:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/11 10:20:25 by jchardin         ###   ########.fr       */
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


	int	marge = 80;
	int	marge_text = 5;
	int	indent_text = 15;
	int	width = 150;
	int	height = 100;
	int	box_width = 70;
	int	box_height = 50;
	int	i;
	int	j;

	t_mycolor		s_color;
	t_mysquare		s_square;
	t_mywrite		s_write;


	//Wall texture
	j = 1;
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(
			1920 - (2 * width) - (4 * marge),
 			((j + 1) * height) + (j * marge) - (height / 2) ,
			s_color,
			24,
			"Wall Texture");
	ft_write(s_win, &s_write);

	//Wall height
	j = 3;
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(
			1920 - (2 * width) - (4 * marge),
 			((j + 1) * height) + (j * marge)  - (height / 2),
			s_color,
			24,
			"Wall Height");
	ft_write(s_win, &s_write);

	//florr height
	j = 4;
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(
			1920 - (2 * width) - (4 * marge),
 			((j + 1) * height) + (j * marge) - (height / 2) ,
			s_color,
			24,
			"Floor Height");
	ft_write(s_win, &s_write);

	//floor texture
	j = 5;
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(
			1920 - (2 * width) - (3 * marge) - 280,
			30,
			s_color,
			19,
			"Floor Texture");
	ft_write(s_win, &s_write);

	//box
	i = 4;
	j = 0;
	s_color = ft_setcolor(WHITE);
	s_square = ft_setsquare(
			1920 - (marge * i) - (width * i) + (width / 2),
 			marge + (j * height) + (j * marge) + (height / 4),
			box_width,
			box_height,
			s_color);
	ft_draw_square(s_win, &s_square);

	//box
	i = 4;
	j = 1;
	s_color = ft_setcolor(WHITE);
	s_square = ft_setsquare(
			1920 - (marge * i) - (width * i) + (width / 2),
 			marge + (j * height) + (j * marge) + (height / 4),
			box_width,
			box_height,
			s_color);
	ft_draw_square(s_win, &s_square);
	//box
	i = 4;
	j = 3;
	s_color = ft_setcolor(WHITE);
	s_square = ft_setsquare(
			1920 - (marge * i) - (width * i) + (width / 2),
 			marge + (j * height) + (j * marge) + (height / 4),
			box_width,
			box_height,
			s_color);
	ft_draw_square(s_win, &s_square);

	//box
	i = 4;
	j = 4;
	s_color = ft_setcolor(WHITE);
	s_square = ft_setsquare(
			1920 - (marge * i) - (width * i) + (width / 2),
 			marge + (j * height) + (j * marge) + (height / 4),
			box_width,
			box_height,
			s_color);
	ft_draw_square(s_win, &s_square);

	i = 1;
	j = 0;
	s_color = ft_setcolor(RED);
	s_square = ft_setsquare(
			1920 - (marge * i) - (width * i),
 			marge + (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(
			1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"Down");
	ft_write(s_win, &s_write);
	i = 2;
	j = 0;
	s_color = ft_setcolor(GREEN);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge + (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(
			1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"Middle");
	ft_write(s_win, &s_write);
	i = 3;
	j = 0;
	s_color = ft_setcolor(BLUE);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge + (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"Up to celling");
	ft_write(s_win, &s_write);
	i = 1;
	j = 1;
	s_color = ft_setcolor(PINK);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge + (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"file needed");
	ft_write(s_win, &s_write);
	i = 2;
	j = 1;
	s_color = ft_setcolor(YELLOW);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge+ (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"file needed");
	ft_write(s_win, &s_write);
	i = 3;
	j = 1;
	s_color = ft_setcolor(ORANGE);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge+ (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"filed needed");
	ft_write(s_win, &s_write);
	i = 1;
	j = 3;
	s_color = ft_setcolor(RED);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge+ (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"Down");
	ft_write(s_win, &s_write);

	i = 2;
	j = 3;
	s_color = ft_setcolor(GREEN);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge + (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"Middle");
	ft_write(s_win, &s_write);
	i = 3;
	j = 3;
	s_color = ft_setcolor(BLUE);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge+ (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"Hight");
	ft_write(s_win, &s_write);
	i = 1;
	j = 4;
	s_color = ft_setcolor(PINK);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge+ (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"filed needed");
	ft_write(s_win, &s_write);
	i = 2;
	j = 4;
	s_color = ft_setcolor(YELLOW);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge+ (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"filed needed");
	ft_write(s_win, &s_write);
	i = 3;
	j = 4;
	s_color = ft_setcolor(ORANGE);
	s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			marge+ (j * height) + (j * marge),
			width,
			height,
			s_color);
	ft_draw_square(s_win, &s_square);
	s_color = ft_setcolor(WHITE);
	s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 			marge + marge_text + ((j + 1) * height) + (j * marge),
			s_color,
			14,
			"filed needed");
	ft_write(s_win, &s_write);


	// CROSS
	t_mycross		s_cross;
	i = 4;
	j = 0;
	s_color = ft_setcolor(PINK);
	s_cross = ft_setcross(1920 - (marge * i) - (width * i) + (width / 2) + (box_width / 2),
			marge + (j * height) + (j * marge) + (height / 4) + (box_height / 2) -5,
			50, 10, s_color);
	ft_draw_cross(s_win, &s_cross);

	// CROSS
	i = 4;
	j = 3;
	s_color = ft_setcolor(PINK);
	s_cross = ft_setcross(1920 - (marge * i) - (width * i) + (width / 2) + (box_width / 2),
			marge + (j * height) + (j * marge) + (height / 4) + (box_height / 2) -5,
			50, 10, s_color);
	ft_draw_cross(s_win, &s_cross);
}

