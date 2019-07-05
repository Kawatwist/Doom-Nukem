/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:39:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/05 15:58:38 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_myvec ft_vector_intersect(t_myvec plane_p, t_myvec plane_n, t_myvec lineStart, t_myvec lineEnd)
	{
		plane_n = ft_normalise(plane_n);
		float plane_d = -ft_dot_product(plane_n, plane_p);
		float ad = ft_dot_product(lineStart, plane_n);
		float bd = ft_dot_product(lineEnd, plane_n);
		float t = (-plane_d - ad) / (bd - ad);
		t_myvec lineStartToEnd = ft_vector_sub(lineEnd, lineStart);
		t_myvec lineToIntersect = ft_vector_multiply(lineStartToEnd, t);
		return (ft_vector_add(lineStart, lineToIntersect));
	}

float	ft_distance(t_myvec plane_n, t_myvec plane_p, t_myvec p)
{
	float	distance;

	distance =  (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - ft_dot_product(plane_n, plane_p));
	printf("la distance =%f\n", distance);
	return (distance);
}

int	ft_triangle_clips_again_plan(t_myvec point, t_myvec plane_norm, t_mytriangle *clipped_triangle, t_mytriangle *triangle, t_mywin *s_win)
{
	t_myvec		points_inside[3];
	t_myvec		points_outside[3];
	int			n_inside_points = 0;
	int			n_outside_points = 0;
	float		distance;
	int			result = 0;
	int			j;

	(void)s_win;
	j = 0;
	plane_norm = ft_normalise(plane_norm);
	point = ft_normalise(point);
	while (j < 3)
	{
		distance = 0;
		distance = ft_distance(plane_norm, point, triangle->vertice[j]);
		if (distance >= 0)
		{
			points_inside[n_inside_points] = triangle->vertice[j];
			n_inside_points++;
		}
		else
		{
			points_outside[n_outside_points] = triangle->vertice[j];
			n_outside_points++;
		}
		j++;
	}
	if (n_inside_points == 0)
	{
		/* printf("reject\n"); */
		result = 0;
	}
	else if (n_inside_points == 1)
	{
		printf("form one triangle ROUGE\n");
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = ft_vector_intersect(plane_norm, point, points_inside[0], points_outside[0]);
		clipped_triangle[0].vertice[2] = ft_vector_intersect(plane_norm, point, points_inside[0], points_outside[1]);
		clipped_triangle[0].ft_color = 'r';
		result = 1;
	}
	else if (n_inside_points == 2)
	{
		printf("==>form a quadra GREEN\n\n");
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = points_inside[1];
		clipped_triangle[0].vertice[2] = ft_vector_intersect(plane_norm, point, points_inside[0], points_outside[0]);
		clipped_triangle[0].ft_color = 'g';


		clipped_triangle[1].vertice[0] = points_inside[1];
		clipped_triangle[1].vertice[1] = clipped_triangle[0].vertice[2];
		clipped_triangle[1].vertice[2] = ft_vector_intersect(plane_norm,  point, points_inside[1], points_outside[0]);
		clipped_triangle[1].ft_color = 'g';
		result = 2;
	}
	else if (n_inside_points == 3)
	{
		/* printf("do nothing BLUE\n"); */
		clipped_triangle[0] = *triangle;
		clipped_triangle[0].ft_color = 'b';
		result = 1;
	}
	return (result);
}
