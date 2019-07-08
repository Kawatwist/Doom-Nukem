/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_get_triangles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:58:52 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 22:23:34 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>

t_mytriangle	*ft_get_triangle(void)
{
	t_mytriangle	*triangle_array;
	triangle_array = (t_mytriangle*)malloc(sizeof(t_mytriangle) * 12);
	triangle_array[0].vertice[0].x = 0.0;
	triangle_array[0].vertice[0].y = 0.0;
	triangle_array[0].vertice[0].z = 0.0;

	triangle_array[0].vertice[1].x = 0.0;
	triangle_array[0].vertice[1].y = 1.0;
	triangle_array[0].vertice[1].z = 0.0;

	triangle_array[0].vertice[2].x = 1.0;
	triangle_array[0].vertice[2].y = 1.0;
	triangle_array[0].vertice[2].z = 0.0;



	triangle_array[1].vertice[0].x = 0.0;
	triangle_array[1].vertice[0].y = 0.0;
	triangle_array[1].vertice[0].z = 0.0;

	triangle_array[1].vertice[1].x = 1.0;
	triangle_array[1].vertice[1].y = 1.0;
	triangle_array[1].vertice[1].z = 0.0;

	triangle_array[1].vertice[2].x = 1.0;
	triangle_array[1].vertice[2].y = 0.0;
	triangle_array[1].vertice[2].z = 0.0;




	triangle_array[2].vertice[0].x = 1.0;
	triangle_array[2].vertice[0].y = 0.0;
	triangle_array[2].vertice[0].z = 0.0;

	triangle_array[2].vertice[1].x = 1.0;
	triangle_array[2].vertice[1].y = 1.0;
	triangle_array[2].vertice[1].z = 0.0;

	triangle_array[2].vertice[2].x = 1.0;
	triangle_array[2].vertice[2].y = 1.0;
	triangle_array[2].vertice[2].z = 1.0;



	triangle_array[3].vertice[0].x = 1.0;
	triangle_array[3].vertice[0].y = 0.0;
	triangle_array[3].vertice[0].z = 0.0;

	triangle_array[3].vertice[1].x = 1.0;
	triangle_array[3].vertice[1].y = 1.0;
	triangle_array[3].vertice[1].z = 1.0;

	triangle_array[3].vertice[2].x = 1.0;
	triangle_array[3].vertice[2].y = 0.0;
	triangle_array[3].vertice[2].z = 1.0;



	triangle_array[4].vertice[0].x = 1.0;
	triangle_array[4].vertice[0].y = 0.0;
	triangle_array[4].vertice[0].z = 1.0;

	triangle_array[4].vertice[1].x = 1.0;
	triangle_array[4].vertice[1].y = 1.0;
	triangle_array[4].vertice[1].z = 1.0;

	triangle_array[4].vertice[2].x = 0.0;
	triangle_array[4].vertice[2].y = 1.0;
	triangle_array[4].vertice[2].z = 1.0;



	triangle_array[5].vertice[0].x = 1.0;
	triangle_array[5].vertice[0].y = 0.0;
	triangle_array[5].vertice[0].z = 1.0;

	triangle_array[5].vertice[1].x = 0.0;
	triangle_array[5].vertice[1].y = 1.0;
	triangle_array[5].vertice[1].z = 1.0;

	triangle_array[5].vertice[2].x = 0.0;
	triangle_array[5].vertice[2].y = 0.0;
	triangle_array[5].vertice[2].z = 1.0;



	triangle_array[6].vertice[0].x = 0.0;
	triangle_array[6].vertice[0].y = 0.0;
	triangle_array[6].vertice[0].z = 1.0;

	triangle_array[6].vertice[1].x = 0.0;
	triangle_array[6].vertice[1].y = 1.0;
	triangle_array[6].vertice[1].z = 1.0;

	triangle_array[6].vertice[2].x = 0.0;
	triangle_array[6].vertice[2].y = 1.0;
	triangle_array[6].vertice[2].z = 0.0;


	triangle_array[7].vertice[0].x = 0.0;
	triangle_array[7].vertice[0].y = 0.0;
	triangle_array[7].vertice[0].z = 1.0;

	triangle_array[7].vertice[1].x = 0.0;
	triangle_array[7].vertice[1].y = 1.0;
	triangle_array[7].vertice[1].z = 0.0;

	triangle_array[7].vertice[2].x = 0.0;
	triangle_array[7].vertice[2].y = 0.0;
	triangle_array[7].vertice[2].z = 0.0;


	triangle_array[8].vertice[0].x = 0.0;
	triangle_array[8].vertice[0].y = 1.0;
	triangle_array[8].vertice[0].z = 0.0;

	triangle_array[8].vertice[1].x = 0.0;
	triangle_array[8].vertice[1].y = 1.0;
	triangle_array[8].vertice[1].z = 1.0;

	triangle_array[8].vertice[2].x = 1.0;
	triangle_array[8].vertice[2].y = 1.0;
	triangle_array[8].vertice[2].z = 1.0;


	triangle_array[9].vertice[0].x = 0.0;
	triangle_array[9].vertice[0].y = 1.0;
	triangle_array[9].vertice[0].z = 0.0;

	triangle_array[9].vertice[1].x = 1.0;
	triangle_array[9].vertice[1].y = 1.0;
	triangle_array[9].vertice[1].z = 1.0;

	triangle_array[9].vertice[2].x = 1.0;
	triangle_array[9].vertice[2].y = 1.0;
	triangle_array[9].vertice[2].z = 0.0;


	triangle_array[10].vertice[0].x = 1.0;
	triangle_array[10].vertice[0].y = 0.0;
	triangle_array[10].vertice[0].z = 1.0;

	triangle_array[10].vertice[1].x = 0.0;
	triangle_array[10].vertice[1].y = 0.0;
	triangle_array[10].vertice[1].z = 1.0;

	triangle_array[10].vertice[2].x = 0.0;
	triangle_array[10].vertice[2].y = 0.0;
	triangle_array[10].vertice[2].z = 0.0;


	triangle_array[11].vertice[0].x = 1.0;
	triangle_array[11].vertice[0].y = 0.0;
	triangle_array[11].vertice[0].z = 1.0;

	triangle_array[11].vertice[1].x = 0.0;
	triangle_array[11].vertice[1].y = 0.0;
	triangle_array[11].vertice[1].z = 0.0;

	triangle_array[11].vertice[2].x = 1.0;
	triangle_array[11].vertice[2].y = 0.0;
	triangle_array[11].vertice[2].z = 0.0;

	return (triangle_array);
}


















void			ft_display_triangle_array(t_mywin *s_win, t_mytriangle *triangle)
{
	int		i;
	int		stop;
	int		j;

	i = 0;
	stop = ft_get_nbr_of_triangle(s_win->polygon_lst);
	while (i < stop)
	{
		j = -1;
		while (++j < 3)
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle[i].vertice[j].x, triangle[i].vertice[j].y, triangle[i].vertice[j].z);
		printf("\n");
		i++;
	}
}

int				ft_get_nbr_of_triangle(t_mypolygon *polygon_lst)
{
	int				nbr_indices;
	t_mypolygon		*keep;

	keep = polygon_lst;
	nbr_indices = 0;
	while (polygon_lst != NULL)
	{
		nbr_indices += polygon_lst->number_of_indices;
		polygon_lst = polygon_lst->next;
	}
	polygon_lst = keep;
	return (nbr_indices / 3);
}

float		ft_get_the_indice_vertex_x(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	x;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	x = vertex_lst->x;
	vertex_lst = keep;
	return (x);
}

float		ft_get_the_indice_vertex_y(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	y;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	y = vertex_lst->y;
	vertex_lst = keep;
	return (y);
}

float		ft_get_the_indice_vertex_z(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	z;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	z = vertex_lst->z;
	vertex_lst = keep;
	return (z);
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

t_mytriangle	ft_get_the_next_triangle(int triangle_nbr, t_mypolygon *polygon_lst)
{
	t_mytriangle	triangle;
	t_mypolygon		*keep;
	int				triangle_indice_absolu;
	int				triangle_indice_relatif;

	keep = polygon_lst;
	triangle_indice_absolu = 0;
	while (polygon_lst != NULL)
	{
		triangle_indice_relatif = 0;
		while (triangle_indice_relatif < polygon_lst->number_of_indices)
		{
			if ((triangle_indice_absolu / 3) == triangle_nbr)
			{
				triangle = ft_get_vertice_of_the_triangle(polygon_lst, triangle_indice_relatif);
				polygon_lst = keep;
				return (triangle);
			}
			triangle_indice_relatif++;
			triangle_indice_absolu++;
		}
		polygon_lst = polygon_lst->next;
	}
	polygon_lst = keep;
	printf("error\n");
	triangle.vertice[0].x = 0;
	return (triangle);
}

t_mytriangle	*ft_get_triangles_array(t_mypolygon *polygon_lst)
{
	t_mytriangle	*triangle_array;
	int				nbr_triangle;
	int				i;

	nbr_triangle = ft_get_nbr_of_triangle(polygon_lst);
	triangle_array = (t_mytriangle*)malloc(sizeof(t_mytriangle) * nbr_triangle);
	i = -1;
	while (++i < nbr_triangle)
	{
		triangle_array[i] = ft_get_the_next_triangle(i, polygon_lst);
	}
	return (triangle_array);
}
