/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:46:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 21:53:29 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h>


void	ft_launch_bsp_tree(t_mywin *s_win, t_mypolygon *polygon_lst)
{
	printf("BSP tree launcher\n");

	/* t_mynode	s_node; */

	polygon_lst = ft_read_the_polygon_file();
	ft_display_the_polygon_list(polygon_lst);
	ft_process_polygon(polygon_lst);
	s_win->polygon_lst = polygon_lst;
	//ft_build_bsp_tree((&s_node), s_win->polygon_lst);
	//ft_afficher_le_bsp(&s_node);
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

