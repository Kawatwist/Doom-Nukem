/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_get_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:18:24 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/18 16:45:00 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

int				ft_get_nbr_of_triangle(t_mywin *s_win)
{
	int				nbr_indices;
	t_mypolygon		*polygon;
	t_mypolygon		*keep;

	polygon = s_win->polygon_lst;
	keep = polygon;
	nbr_indices = 0;
	while (polygon != NULL)
	{
		nbr_indices += polygon->number_of_indices;
		polygon = polygon->next;
	}
	polygon = keep;
	return (nbr_indices / 3);
}

t_mytriangle	ft_get_vertice_of_the_triangle(t_mypolygon *polygon, int indice)
{
	t_mytriangle	triangle;

	triangle.vertice[0].x = ft_get_the_indice_vertex_x(polygon->indices[indice] ,polygon->vertex_lst);
	triangle.vertice[0].y = ft_get_the_indice_vertex_y(polygon->indices[indice], polygon->vertex_lst);
	triangle.vertice[0].z = ft_get_the_indice_vertex_z(polygon->indices[indice], polygon->vertex_lst);
	triangle.vertice[0].w = 1;
	triangle.vertice[1].x = ft_get_the_indice_vertex_x(polygon->indices[indice + 1], polygon->vertex_lst);
	triangle.vertice[1].y = ft_get_the_indice_vertex_y(polygon->indices[indice + 1], polygon->vertex_lst);
	triangle.vertice[1].z = ft_get_the_indice_vertex_z(polygon->indices[indice + 1], polygon->vertex_lst);
	triangle.vertice[1].w = 1;
	triangle.vertice[2].x = ft_get_the_indice_vertex_x(polygon->indices[indice + 2], polygon->vertex_lst);
	triangle.vertice[2].y = ft_get_the_indice_vertex_y(polygon->indices[indice + 2], polygon->vertex_lst);
	triangle.vertice[2].z = ft_get_the_indice_vertex_z(polygon->indices[indice + 2], polygon->vertex_lst);
	triangle.vertice[2].w = 1;
	return (triangle);
}

t_mytriangle	ft_get_the_next_triangle(t_mywin *s_win, int triangle_nbr)
{
	t_mytriangle	triangle;
	t_mypolygon		*polygon;
	t_mypolygon		*keep;
	int				triangle_indice_absolu;
	int				triangle_indice_relatif;

	polygon = s_win->polygon_lst;
	keep = polygon;
	triangle_indice_absolu = 0;
	while (polygon != NULL)
	{
		triangle_indice_relatif = 0;
		while (triangle_indice_relatif < polygon->number_of_indices)
		{
			if ((triangle_indice_absolu / 3) == triangle_nbr)
			{
				triangle = ft_get_vertice_of_the_triangle(polygon, triangle_indice_relatif);
				polygon = keep;
				return (triangle);
			}
			triangle_indice_relatif++;
			triangle_indice_absolu++;
		}
		polygon = polygon->next;
	}
	polygon = keep;
	printf("error\n");
	triangle.vertice[0].x = 0;
	return (triangle);
}

t_mytriangle	*ft_get_triangles_array(t_mywin *s_win)
{
	t_mytriangle	*triangle_array;
	int				nbr_triangle;
	int				i;

	nbr_triangle = ft_get_nbr_of_triangle(s_win);
	triangle_array = (t_mytriangle*)malloc(sizeof(t_mytriangle) * nbr_triangle);
	i = -1;
	while (++i < nbr_triangle)
	{
		triangle_array[i] = ft_get_the_next_triangle(s_win, i);
	}
	return (triangle_array);
}

void			ft_display_triangle_array(t_mywin *s_win, t_mytriangle *triangle)
{
	int		i;
	int		stop;
	int		j;

	i = 0;
	stop = ft_get_nbr_of_triangle(s_win);
	while (i < stop)
	{
		j = -1;
		while (++j < 3)
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle[i].vertice[j].x, triangle[i].vertice[j].y, triangle[i].vertice[j].z);
		printf("\n");
		i++;
	}
}
