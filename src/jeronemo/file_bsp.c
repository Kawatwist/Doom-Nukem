/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:46:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/21 17:53:34 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		ft_launch_window_bsp(t_mywin *s_win)
{
	s_win->window[J_BINARY_TREE] = NULL;
	s_win->renderer[J_BINARY_TREE] = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(s_win->window[J_BINARY_TREE] = SDL_CreateWindow("BSP Tree", 10, 10, (1920 / 2), (1080 / 2), SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[J_BINARY_TREE] = SDL_CreateRenderer(s_win->window[J_BINARY_TREE],0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
}

t_mypoint	ft_get_segment_middle(t_mywall *s_wall, t_mywin *s_win)
{
	t_mypoint	point;
	t_mypoint	point_a;
	t_mypoint	point_b;

	point_a.x  = (s_wall->x_a * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->x;
	point_a.y  = (s_wall->y_a * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->y;
	point_b.x  = (s_wall->x_b * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->x;
	point_b.y  = (s_wall->y_b * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->y;
	point.x = ((point_b.x - point_a.x) / 2) + point_a.x;
	point.y = ((point_b.y - point_a.y) / 2) + point_a.y;
	return (point);
}

t_mypoint	ft_get_vector(t_mywall *s_wall, t_mywin *s_win)
{
	t_mypoint	point;
	t_mypoint	point_a;
	t_mypoint	point_b;

	point_a.x  = (s_wall->x_a * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->x;
	point_a.y  = (s_wall->y_a * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->y;
	point_b.x  = (s_wall->x_b * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->x;
	point_b.y  = (s_wall->y_b * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->y;
	point.x = point_b.x - point_a.x;
	point.y = point_b.y - point_b.y;
	return (point);
}

int		ft_get_norme(t_mywall *s_wall, t_mywin *s_win)
{
	int			norme;
	t_mypoint	vecteur;

	vecteur = ft_get_vector(s_win->lst_wall, s_win);
	norme = sqrt( (vecteur.x * vecteur.x) + (vecteur.y * vecteur.y));
	return (norme);
}

t_mypoint	ft_get_normalise(t_mywall *s_wall, t_mywin *s_win)
{
	t_mypoint	normalise;
	t_mypoint	vector;
	int			norme;

	norme = ft_get_norme(s_win->lst_wall, s_win);
	vector = ft_get_vector(s_win->lst_wall, s_win);
	normalise.x = vector.x / norme;
	normalise.y = vector.y / norme;
	return (normalise);
}

t_mypoint	ft_get_normal(t_mywall *s_wall, t_mywin *s_win)
{
	t_mypoint	normal;
	t_mypoint	normalise;

	normalise = ft_get_normalise(s_win->lst_wall, s_win);
	normal.x = -normalise.y;
	normal.y = normalise.x;
	return (normal);
}

void	ft_display_triangle(t_mywin *s_win)
{
	t_mywall			*keep;
	t_mypoint			middle;
	t_mypoint			vector;
	t_mycross			s_cross;
	t_mycolor			s_color;
	int					norme;
	t_mypoint			normalise;

	keep = s_win->lst_wall;
	while (s_win->lst_wall)
	{
		middle = ft_get_segment_middle(s_win->lst_wall, s_win);
		vector = ft_get_vector(s_win->lst_wall, s_win);
		norme = ft_get_norme(s_win->lst_wall, s_win);
		normalise = ft_get_normalise(s_win->lst_wall, s_win);
		//t_mycross	ft_setcross(int x, int y, int size, int thickness, t_mycolor color)
		s_color = ft_setcolor(RED);
		s_cross = ft_setcross(.x , middle.y , 6, 2, s_color);
		ft_draw_cross(s_win, &s_cross);
		s_win->lst_wall = s_win->lst_wall->next;
	}
	s_win->lst_wall = keep;
}

void	ft_launch_bsp_tree(t_mywin *s_win, t_win *wn)
{
	(void)wn;
	s_win->current_window = J_BINARY_TREE;
	printf("hello bsp tree\n");

	//read du fichier
	//affichage du fichier dans une fenetre
		//-->chaque segment avec une lettre
		//-->et une fleche de direction
	//on clique sur deux points
		//affichage de l'arbre binaire
	ft_launch_window_bsp(s_win);
	s_win->lst_wall = ft_read_map();
	ft_display_grid(s_win);
	ft_draw_map(s_win);
	ft_display_triangle(s_win);
	SDL_RenderPresent(s_win->renderer[J_BINARY_TREE]);
	SDL_Delay(10000);
}

