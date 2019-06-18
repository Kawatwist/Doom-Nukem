/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_get_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:18:24 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/18 13:51:40 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

int				ft_get_nbr_of_triangle(t_mywin *s_win)
{
	int				nbr_indices;
	t_mypolygon		*polygon;
	t_mypolygon		*keep;

	nbr_triangle = 0;
	polygon = s_win->polygon_lst;
	keep = polygon;
	while (polygon != NULL)
	{
		nbr_triangle += polygon->number_of_indices;
		polygon = polygon->next;
	}
	polygon = keep;
	return (number_of_indices / 3);
}

t_mytriangle	ft_get_the_next_triangle(t_mywin *s_win, int triangle_nbr)
{
	t_mytriangle	triangle;
	t_mypolygon		*polygon;
	t_mypolygon		*keep;
	int				j;
	int				triangles_indices;

	triangle_indices = 0;
	polygon = s_win->polygon_lst;
	keep = polygon;
	while (polygon != NULL)
	{
		j = 0;
		while (j < polygon->number_of_indices)
		{
			triangle_indices++;
			if (triangle_indices / 3 == triangle_nbr)
			{
				triangle[0].x = ft_get_the_indice_vertex_x(polygon->indices[triangle_indices] ,polygon->vertex_lst);
				triangle[0].y = ft_get_the_indice_vertex_y(polygon->indices[triangle_indices], polygon->vertex_lst);
				triangle[0].z = ft_get_the_indice_vertex_z(polygon->indices[triangle_indices], polygon->vertex_lst);

				triangle[1].x = ft_get_the_indice_vertex_x(polygon->indices[triangle_indices + 1], polygon->vertex_lst);
				triangle[1].y = ft_get_the_indice_vertex_y(polygon->indices[triangle_indices + 1], polygon->vertex_lst);
				triangle[1].z = ft_get_the_indice_vertex_z(polygon->indices[triangle_indices + 1], polygon->vertex_lst);

				triangle[2].x = ft_get_the_indice_vertex_x(polygon->indices[triangle_indices + 2], polygon->vertex_lst);
				triangle[2].y = ft_get_the_indice_vertex_y(polygon->indices[triangle_indices + 2], polygon->vertex_lst);
				triangle[2].z = ft_get_the_indice_vertex_z(polygon->indices[triangle_indices + 2], polygon->vertex_lst);
				polygon = keep;
				return (triangle);
			}
			j++;
		}
		polygon = polygon->next;
	}
	polygon = keep;
}


t_mytriangle	*ft_get_triangles_array(t_mywin *s_win)
{
	t_mytriangle	*triangle_array;
	int				nbr_triangle;
	int				i;

	nbr_triangle = ft_get_nbr_of_triangle(s_win);
	printf("Le nombre de triangle =%d\n", nbr_triangle);
	triangle_array = (t_mytriangle*)malloc(sizeof(t_mytriangle) * nbr_triangle);
	i = -1;
	while (++i < nbr_triangle)
		triangle_array[i] = ft_get_the_next_triangle(s_win, i);
	return (triangle_array);
}


void	ft_display_triangle_array(t_mywin *s_win)
{

}


/* int		ft_get_number_of_polygon(t_mywin *s_win) */
/* { */
/* 	int				nbr_of_polygon; */
/* 	t_mypolygon		*polygon; */
/* 	t_mypolygon		*keep; */

/* 	nbr_of_polygon = 0; */
/* 	polygon = s_win->polygon_lst; */
/* 	keep = polygon; */
/* 	while (polygon != NULL) */
/* 	{ */
/* 		nbr_of_polygon++; */
/* 		polygon = polygon->next; */
/* 	} */
/* 	polygon = keep; */
/* 	return (nbr_of_polygon); */
/* } */

/* void	ft_get_polynome_lst(t_mywin *s_win) */
/* { */
/* 	int				nbr_of_polygon; */
/* 	int				i; */
/* 	/1* t_mypolygon		*polygon; *1/ */

/* 	nbr_of_polygon = ft_get_number_of_polygon(s_win); */
/* 	printf("Le nombre de polynome =%d", nbr_of_polygon); */


/* 	 polygon = s_win->polygon_lst; */
/* 	 while (i < nbr_of_polygon) */
/* 	 { */

/* 		i++; */
/* 		polygon = polygon->next; */
/* 	 } */
/* 	 polygon = keep->polygon; */
/* } */

