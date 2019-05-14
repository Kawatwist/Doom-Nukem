/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:39:30 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/14 15:11:43 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>


int		ft_clik_wall_height(t_mywin *s_win, t_win *wn)
{
	printf("hello1\n");
	if (wn->input->y > s_win->s_localisation_color_box[0][1]->y && wn->input->y < s_win->s_localisation_color_box[0][1]->y + s_win->s_localisation_color_box[0][1]->height)
	{
		printf("hello2\n");
		//y = 0 <=> wall height
		//s_win->s_localisation_color_box[0][1]->y

		//1 down
		if (wn->input->x > s_win->s_localisation_color_box[0][1]->x &&
				wn->input->x < s_win->s_localisation_color_box[0][1]->x + s_win->s_localisation_color_box[0][1]->width)
		{
			printf("wall height => down\n");
			return(1);
		}
		//2 middle
		if (wn->input->x > s_win->s_localisation_color_box[0][2]->x &&
				wn->input->x < s_win->s_localisation_color_box[0][2]->x + s_win->s_localisation_color_box[0][2]->width)
		{
			printf("wall height => middle\n");
			return(1);
		}
		//3 uptoceilling
		if (wn->input->x > s_win->s_localisation_color_box[0][3]->x &&
				wn->input->x < s_win->s_localisation_color_box[0][3]->x + s_win->s_localisation_color_box[0][3]->width)
		{
			printf("wall height => up to ceilling\n");
			return(1);
		}
	}


	return (0);
}

int		ft_clik_wall_texture(t_mywin *s_win, t_win *wn)
{
	(void)s_win;
	(void)wn;
	if (wn->input->y > s_win->s_localisation_color_box[1][1]->y &&
			wn->input->y < s_win->s_localisation_color_box[1][1]->y + s_win->s_localisation_color_box[1][1]->height)
	{
		//y = 1 <=> wall texture
		//s_win->s_localisation_color_box[1][1]->y


		//1 first texture
		if (wn->input->x > s_win->s_localisation_color_box[1][1]->x &&
				wn->input->x < s_win->s_localisation_color_box[1][1]->x + s_win->s_localisation_color_box[1][1]->width)
		{
			printf("wall texture => first\n");
			return(1);
		}
		//2 secondetexture
		if (wn->input->x > s_win->s_localisation_color_box[1][2]->x &&
				wn->input->x < s_win->s_localisation_color_box[1][2]->x + s_win->s_localisation_color_box[1][2]->width)
		{
			printf("wall texture => seconde\n");
			return(1);
		}
		//3 third texture
		if (wn->input->x > s_win->s_localisation_color_box[1][3]->x &&
				wn->input->x < s_win->s_localisation_color_box[1][3]->x + s_win->s_localisation_color_box[1][3]->width)
		{
			printf("wall texture => third\n");
			return(1);
		}
	}
	return (0);
}


int		ft_click_floor_height(t_mywin *s_win, t_win *wn)
{
	(void)s_win;
	(void)wn;
	if (wn->input->y > s_win->s_localisation_color_box[3][1]->y &&
			wn->input->y < s_win->s_localisation_color_box[3][1]->y + s_win->s_localisation_color_box[3][1]->height)
	{
		//y = 3 <=> floor height
		//s_win->s_localisation_color_box[3][1]->y

		//1 down
		if (wn->input->x > s_win->s_localisation_color_box[3][1]->x &&
				wn->input->x < s_win->s_localisation_color_box[3][1]->x + s_win->s_localisation_color_box[3][1]->width)
		{
			printf("floor height => down\n");
			return(1);
		}
		//2 middle
		if (wn->input->x > s_win->s_localisation_color_box[3][2]->x &&
				wn->input->x < s_win->s_localisation_color_box[3][2]->x + s_win->s_localisation_color_box[3][2]->width)
		{
			printf("floor height => middle\n");
			return(1);
		}
		//3 hight
		if (wn->input->x > s_win->s_localisation_color_box[3][3]->x &&
				wn->input->x < s_win->s_localisation_color_box[3][3]->x + s_win->s_localisation_color_box[3][3]->width)
		{
			printf("floor height => hight\n");
			return(1);
		}
	}
	return (0);
}


int		ft_click_floor_texture(t_mywin *s_win, t_win *wn)
{
	(void)s_win;
	(void)wn;
	if (wn->input->y > s_win->s_localisation_color_box[4][1]->y &&
			wn->input->y < s_win->s_localisation_color_box[4][1]->y + s_win->s_localisation_color_box[4][1]->height)
	{
		//y = 4 <=> floor texture

		//1 first texture
		if (wn->input->x > s_win->s_localisation_color_box[4][1]->x &&
				wn->input->x < s_win->s_localisation_color_box[4][1]->x + s_win->s_localisation_color_box[4][1]->width)
		{
			printf("floor texture => first\n");
			return(1);
		}
		//2 secondetexture
		if (wn->input->x > s_win->s_localisation_color_box[4][2]->x &&
				wn->input->x < s_win->s_localisation_color_box[4][2]->x + s_win->s_localisation_color_box[4][2]->width)
		{
			printf("floor texture => second\n");
			return(1);
		}
		//3 third texture
		if (wn->input->x > s_win->s_localisation_color_box[4][3]->x &&
				wn->input->x < s_win->s_localisation_color_box[4][3]->x + s_win->s_localisation_color_box[4][3]->width)
		{
			printf("floor texture => third\n");
			return(1);
		}
	}
	return (0);
}

int		ft_click_save(t_mywin *s_win, t_win *wn)
{
	if (wn->input->y > s_win->s_localisation_save_button->y &&
			wn->input->y < s_win->s_localisation_save_button->y + s_win->s_localisation_save_button->height)
	{
		if (wn->input->x > s_win->s_localisation_save_button->x &&
				wn->input->x < s_win->s_localisation_save_button->x + s_win->s_localisation_save_button->width)
		{
			return(1);
		}
	}
	return (0);
}

int		ft_click_quit(t_mywin *s_win, t_win *wn)
{
	if (wn->input->y > s_win->s_localisation_quit_button->y &&
			wn->input->y < s_win->s_localisation_quit_button->y + s_win->s_localisation_quit_button->height)
	{
		if (wn->input->x > s_win->s_localisation_quit_button->x &&
				wn->input->x < s_win->s_localisation_quit_button->x + s_win->s_localisation_quit_button->width)
		{
			return(1);
		}
	}
	return (0);
}

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
			if (ft_clik_wall_height(s_win, wn))
				printf("CLIK wall height\n");
			//if(ft_clik_wall_texture(s_win, wn))
			//printf("CLIK wall texture\n");
			//if(ft_click_floor_height(s_win, wn))
			//printf("CLIK floor height\n");
			//if(ft_click_floor_texture(s_win, wn))
			//printf("CLIK floor texture\n");
			if(ft_click_save(s_win, wn))
				printf("CLIK save\n");
			if(ft_click_quit(s_win, wn))
				printf("CLIK quit\n");
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

