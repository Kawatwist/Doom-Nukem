/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:35:59 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/08 18:02:11 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void			ft_quit(char *txt, t_my_win *s_win)
{
	printf("%s\n", txt);
	if (s_win->window[J_EDITOR] != NULL)
		SDL_DestroyWindow(s_win->window[J_EDITOR]);
	if (s_win->renderer[J_EDITOR] != NULL)
		SDL_DestroyRenderer(s_win->renderer[J_EDITOR]);
	SDL_Quit();
	exit(1);
}

void		ft_launch_window(t_my_win *s_win)
{
	s_win->window[J_EDITOR] = NULL;
	s_win->renderer[J_EDITOR] = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(s_win->window[J_EDITOR] = SDL_CreateWindow("J map editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							600, 400, SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[J_EDITOR] = SDL_CreateRenderer(s_win->window[J_EDITOR],0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
}


void	ft_draw_grid(void)
{
	printf("ft_draw_grid\n");
}

void	ft_draw_square(void)
{
	printf("ft_draw_square\n");
}

void	ft_write(void)
{
	printf("ft_write\n");
}

void	ft_draw_cross(void)
{
	printf("ft_draw_cross\n");
}

void	ft_draw_wall(void)
{
	printf("ft_draw_wall\n");
}

void	ft_read_map(void)
{
	printf("ft_read_map\n");
}

void	ft_save_map(void)
{
	printf("ft_save_map\n");
}



void	ft_launch_map_editor(t_my_win *s_win)
{
	ft_launch_window(s_win);
	ft_draw_grid();
	ft_draw_square();
	ft_write();
	ft_draw_cross();
	ft_draw_wall();
	ft_read_map();
	ft_save_map();
	SDL_RenderPresent(s_win->renderer[J_EDITOR]);

}


void	ft_jeronemo(t_win *wn)
{
	(void)wn;
	t_my_win	s_win;

	printf("hello chef inca\n");
	ft_launch_map_editor(&s_win);
	while(1)
	{
		SDL_Delay(10);
	}
}


