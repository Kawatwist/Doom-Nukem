/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:39:30 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/10 16:11:16 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	ft_launch_map_editor(t_mywin *s_win)
{
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	t_mycolor		s_color;
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




		t_mysquare		s_square;
		t_mywrite	s_write;

		int marge = 80;
		int marge_text = 5;
		int indent_text = 15;
		int width = 150;
		int height = 100;

		int box_width = 70;
		int box_height = 50;
		int i;
		int j;

		//TITRE
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(	100,
								10,
 			   	s_color, 24, "Doom Map Editor  (en attendant celui de Laetitia)");
		ft_write(s_win, &s_write);


	//DRAW GRID
	t_mygrid	s_grid;
	s_grid = ft_setgrid(50, 100, 700, 900);
	ft_draw_grid(s_win, &s_grid);


		//Wall height
		j = 0;
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(	1920 - (2 * width) - (4 * marge),
 			   					((j + 1) * height) + (j * marge)  - (height / 2),
								s_color, 24, "Wall Height");
		ft_write(s_win, &s_write);


		//Wall texture
		j = 1;
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(	1920 - (2 * width) - (4 * marge),
 			   					((j + 1) * height) + (j * marge) - (height / 2) ,
								s_color, 24, "Wall Texture");
		ft_write(s_win, &s_write);


		//Wall height
		j = 3;
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(	1920 - (2 * width) - (4 * marge),
 			   					((j + 1) * height) + (j * marge)  - (height / 2),
								s_color, 24, "Wall Height");
		ft_write(s_win, &s_write);


		//florr height
		j = 4;
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(	1920 - (2 * width) - (4 * marge),
 			   					((j + 1) * height) + (j * marge) - (height / 2) ,
								s_color, 24, "Floor Height");
		ft_write(s_win, &s_write);


		//floor texture
		j = 5;
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(1920 - (2 * width) - (3 * marge) - 280, 30, s_color, 19, "Floor Texture");
		ft_write(s_win, &s_write);




		//box
		i = 4;
		j = 0;
		s_color = ft_setcolor(WHITE);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i) + (width / 2),
 			   					marge + (j * height) + (j * marge) + (height / 4),
								box_width,
								box_height,
								s_color);
		ft_draw_square(s_win, &s_square);


		//box
		i = 4;
		j = 1;
		s_color = ft_setcolor(WHITE);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i) + (width / 2),
 			   					marge + (j * height) + (j * marge) + (height / 4),
								box_width,
								box_height,
								s_color);
		ft_draw_square(s_win, &s_square);


		//box
		i = 4;
		j = 3;
		s_color = ft_setcolor(WHITE);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i) + (width / 2),
 			   					marge + (j * height) + (j * marge) + (height / 4),
								box_width,
								box_height,
								s_color);
		ft_draw_square(s_win, &s_square);


		//box
		i = 4;
		j = 4;
		s_color = ft_setcolor(WHITE);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i) + (width / 2),
 			   					marge + (j * height) + (j * marge) + (height / 4),
								box_width,
								box_height,
								s_color);
		ft_draw_square(s_win, &s_square);



		i = 1;
		j = 0;
		s_color = ft_setcolor(RED);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			   					marge + (j * height) + (j * marge),
								width,
								height,
								s_color);
		ft_draw_square(s_win, &s_square);
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "Down");
		ft_write(s_win, &s_write);
		i = 2;
		j = 0;
		s_color = ft_setcolor(GREEN);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			   					marge+ (j * height) + (j * marge),
								width,
								height,
								s_color);
		ft_draw_square(s_win, &s_square);
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "Middle");
		ft_write(s_win, &s_write);
		i = 3;
		j = 0;
		s_color = ft_setcolor(BLUE);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			   					marge+ (j * height) + (j * marge),
								width,
								height,
								s_color);
		ft_draw_square(s_win, &s_square);
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "Up to celling");
		ft_write(s_win, &s_write);
		i = 1;
		j = 1;
		s_color = ft_setcolor(PINK);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			   					marge+ (j * height) + (j * marge),
								width,
								height,
								s_color);
		ft_draw_square(s_win, &s_square);
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "file needed");
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
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "file needed");
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
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "filed needed");
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
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "Down");
		ft_write(s_win, &s_write);


		i = 2;
		j = 3;
		s_color = ft_setcolor(GREEN);
		s_square = ft_setsquare(1920 - (marge * i) - (width * i),
 			   					marge+ (j * height) + (j * marge),
								width,
								height,
								s_color);
		ft_draw_square(s_win, &s_square);
		s_color = ft_setcolor(WHITE);
		s_write = ft_setwrite(1920 - (marge * i) - (width * i) + indent_text,
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "Middle");
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
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "Hight");
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
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "filed needed");
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
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "filed needed");
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
 	marge + marge_text + ((j + 1) * height) + (j * marge) ,
				s_color, 14, "filed needed");
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







	SDL_RenderPresent(s_win->renderer[J_EDITOR]);
}
