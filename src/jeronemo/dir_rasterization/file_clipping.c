/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:39:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/25 13:38:08 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_distance(void)
{
	//distance from point to a plane

}

void	ft_vector_intersect(void)
{
	//return a point if the line cross the plane
	//line intersect with plane

}



int	ft_triangle_clips_again_plan(t_myvec point, t_myvec plan, t_mytriangle *clipped_triangle, t_mytriangle *triangle)
{

	//we want the distance between the plane and the point

	t_myvec		points_inside[2];
	t_myvec		points_outside[2];
	int			n_inside_points = 0;
	int			n_outside_points = 0;
	int			distance;
	int			result;


	int	j;
	j = -1;
	while (++j < 3)
	{
		distance = 0;
		distance = ft_distance(triangle->vertice[j]);

		if (distance >= 0)
		{
			points_inside[n_inside_points] = triangle->vertice[j];
			n_inside_points++;
		}
		else
		{
			points_inside[n_outside_points] = triangle->vertice[j];
			n_outside_points++;
		}
	}

	if (n_inside_points == 3)
	{
		//do nothing
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = points_inside[1];
		clipped_triangle[0].vertice[2] = points_inside[2];
		result = 1;
	}
	else if (n_inside_points == 0)
	{
		//reject
		result = 0;
	}
	else if (n_inside_points == 2)
	{
		//form a quadra
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = points_inside[];
		clipped_triangle[0].vertice[2] = ft_vector_intersect(points_inside[0], point_outside[1], plane);


		clipped_triangle[1].vertice[0] = points_inside[0];
		clipped_triangle[1].vertice[1] = points_inside[];
		clipped_triangle[1].vertice[2] = ft_vector_intersect(points_inside[0], point_outside[1], plane);

		result = 2;
	}
	else if (n_inside_points == 1)
	{
		//form one triangle
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = ft_vector_intersect(points_inside[0], point_outside[0], plane);
		clipped_triangle[0].vertice[2] = ft_vector_intersect(points_inside[0], point_outside[1], plane);
		result = 1;
	}
}
