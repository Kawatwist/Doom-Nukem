/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:46:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/09 11:04:54 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void 		ft_launch_window_bsp(t_mywin *s_win)
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

t_mypointf	ft_get_vector(t_mywall *s_wall, t_mywin *s_win)
{
	t_mypointf	point;
	t_mypointf	point_a;
	t_mypointf	point_b;

	point_a.x  = (s_wall->x_a * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->x;
	point_a.y  = (s_wall->y_a * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->y;
	point_b.x  = (s_wall->x_b * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->x;
	point_b.y  = (s_wall->y_b * (s_win->s_localisation_grid->step)) + s_win->s_localisation_grid->y;
	point.x = point_b.x - point_a.x;
	point.y = point_b.y - point_a.y;
	return (point);
}

double		ft_get_norme(t_mywall *s_wall, t_mywin *s_win)
{
	double			norme;
	t_mypointf	vecteur;

	vecteur = ft_get_vector(s_wall, s_win);
	norme = sqrt( (vecteur.x * vecteur.x) + (vecteur.y * vecteur.y));
	return (norme);
}

t_mypointf	ft_get_normalise(t_mywall *s_wall, t_mywin *s_win)
{
	t_mypointf	normalise;
	t_mypointf	vector;
	double			norme;

	norme = ft_get_norme(s_wall, s_win);
	vector = ft_get_vector(s_wall, s_win);
	normalise.x = vector.x / norme;
	normalise.y = vector.y / norme;
	return (normalise);
}

t_mypointf	ft_get_normal(t_mywall *s_wall, t_mywin *s_win)
{
	t_mypointf	normal;
	t_mypointf	normalise;

	normalise = ft_get_normalise(s_wall, s_win);
	normal.x = -normalise.y;
	normal.y = normalise.x;
	return (normal);
}

void	ft_display_triangle(t_mywin *s_win)
{
	t_mywall			*keep;
	t_mypoint			middle;
	t_mypointf			vector;
	t_mycolor			s_color;
	int					norme;
	t_mypointf			normalise;
	t_mypointf			normal;
	t_myputtheline		s_line;

	keep = s_win->lst_wall;
	while (s_win->lst_wall)
	{
		printf("\n\n");
		middle = ft_get_segment_middle(s_win->lst_wall, s_win);
		printf("middle %d %d\n", middle.x, middle.y);
		vector = ft_get_vector(s_win->lst_wall, s_win);
		printf("vecteur %f %f\n", vector.x, vector.y);
		norme = ft_get_norme(s_win->lst_wall, s_win);
		printf("norme %d\n", norme);
		normalise = ft_get_normalise(s_win->lst_wall, s_win);
		printf("normalise %f %f\n", normalise.x, normalise.y);
		normal = ft_get_normal(s_win->lst_wall, s_win);
		printf("normal %f %f\n", normal.x, normal.y);
		s_color = ft_setcolor(RED);
		s_line.un.a = middle.x;
		s_line.un.b = middle.y;
		s_line.deux.a = (normal.x * 15) + middle.x;
		s_line.deux.b = (normal.y * 15) + middle.y;
		SDL_SetRenderDrawColor(s_win->renderer[s_win->current_window], 255, 255, 255, 255);
		ft_draw_line(s_win, &s_line);
		s_win->lst_wall = s_win->lst_wall->next;
	}
	s_win->lst_wall = keep;
}

void		ft_affichier_bsp_id(t_mynode *s_node)
{
	printf("%d\n", s_node->splitter->id);
	printf("|\n");

	if (s_node->back->is_leaf != TRUE)
	{
		printf("back:");
		ft_affichier_bsp_id(s_node->back);
	}
	if (s_node->front->is_leaf != TRUE)
	{
		printf("front:");
		ft_affichier_bsp_id(s_node->front);
	}
}

void	ft_launch_bsp_tree(t_mywin *s_win, t_win *wn)
{
	printf("BSP tree launcher\n");
	(void)wn;
	t_mynode	s_node;

	s_win->polygon_lst = ft_read_the_polygon_file();
	ft_display_the_polygon_list(s_win->polygon_lst);
	ft_process_polygon(s_win->polygon_lst);
	ft_build_bsp_tree((&s_node), s_win->polygon_lst);
	ft_afficher_le_bsp(&s_node);
	ft_affichier_bsp_id(&s_node);
	//ft_display_polygon();


	/* (void)wn; */
	/* s_win->current_window = J_BINARY_TREE; */
	/* printf("hello bsp tree\n"); */

	/* //read du fichier */
	/* //affichage du fichier dans une fenetre */
	/* //-->chaque segment avec une lettre */
	/* //-->et une fleche de direction */
	/* //on clique sur deux points */
	/* //affichage de l'arbre binaire */
	/* ft_launch_window_bsp(s_win); */
	/* s_win->lst_wall = ft_read_map(); */
	/* ft_display_grid(s_win); */
	/* ft_draw_map(s_win); */
	/* ft_display_triangle(s_win); */
	/* SDL_RenderPresent(s_win->renderer[J_BINARY_TREE]); */
	/* SDL_Delay(10000); */
}

