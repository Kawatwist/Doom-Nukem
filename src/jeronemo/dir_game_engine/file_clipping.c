/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:39:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/05 09:53:35 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

float	ft_distance(t_myvec plane_N, t_myvec point_plane_Q, t_myvec point_P)
{
	float	distance;
	//distance from point to a plane
	float	A = plane_N.x;
	float	B = plane_N.y;
	float	C = plane_N.z;
	float	x0 = point_plane_Q.x;
	float	y0 = point_plane_Q.y;
	float	z0 = point_plane_Q.z;
	float	x1 = point_P.x;
	float	y1 = point_P.y;
	float	z1 = point_P.z;

	float	D = (-A * x0) - (B * y0) - (C * z0);

	distance = ((A * x1) + (B * y1) + (C * z1) + (D)) / sqrt((A * A) + (B * B) + (C * C));
	return (distance);
}

typedef struct{
	double x,y,z;
}vector;

vector addVectors(vector a,vector b){
	return (vector){a.x+b.x,a.y+b.y,a.z+b.z};
}

vector subVectors(vector a,vector b){
	return (vector){a.x-b.x,a.y-b.y,a.z-b.z};
}

double dotProduct(vector a,vector b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

vector scaleVector(double l,vector a){
	return (vector){l*a.x,l*a.y,l*a.z};
}

vector intersectionPoint(vector lineVector, vector linePoint, vector planeNormal, vector planePoint){
	vector diff = subVectors(linePoint,planePoint);

	return addVectors(addVectors(diff,planePoint),scaleVector(-dotProduct(diff,planeNormal)/dotProduct(lineVector,planeNormal),lineVector));
}

t_myvec	ft_vector_intersect(t_myvec plane_n, t_myvec plane_p, t_myvec lineStart, t_myvec lineEnd)
{
	//vec3d &plane_p, vec3d &plane_n, vec3d &lineStart, vec3d &lineEnd

	plane_n = ft_normalise(plane_n);
	float plane_d = -ft_dot_product(plane_n, plane_p);
	float ad = ft_dot_product(lineStart, plane_n);
	float bd = ft_dot_product(lineEnd, plane_n);
	float t = (-plane_d - ad) / (bd - ad);
	t_myvec lineStartToEnd = ft_vector_sub(lineEnd, lineStart);
	t_myvec lineToIntersect = ft_vector_multiply(lineStartToEnd, t);
	return ft_vector_add(lineStart, lineToIntersect);
}


int	ft_triangle_clips_again_plan(t_myvec point, t_myvec plane_norm, t_mytriangle *clipped_triangle, t_mytriangle *triangle, t_mywin *s_win)
{
	t_myvec		points_inside[3];
	t_myvec		points_outside[3];
	int			n_inside_points = 0;
	int			n_outside_points = 0;
	int			distance;
	int			result = 0;
	int			j;
	t_myvec		plane_N;
	t_myvec		point_plane_Q;

	j = 0;
	while (j < 3)
	{
		distance = 0;
		plane_N.x = plane_norm.x;
		plane_N.y = plane_norm.y;
		plane_N.z = plane_norm.z;
		point_plane_Q.x = point.x;
		point_plane_Q.y = point.y;
		point_plane_Q.z = point.z;
		distance = ft_distance(plane_N, point_plane_Q, triangle->vertice[j]);
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
	else
	{
		printf("no rejected\n");
		clipped_triangle[0] = *triangle;
		result = 1;
	}
	return (result);



	if (n_inside_points == 1)
	{
		printf("form one triangle\n");
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = ft_vector_intersect(plane_N, point_plane_Q, points_inside[0], points_outside[0]);
		clipped_triangle[0].vertice[2] = ft_vector_intersect(plane_N, point_plane_Q, points_inside[0], points_outside[1]);
		SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 255, 0, 0, 255);
		result = 1;
	}
	else if (n_inside_points == 2)
	{
		printf("==>form a quadra\n\n");
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = points_inside[1];
		clipped_triangle[0].vertice[2] = ft_vector_intersect(plane_N, point_plane_Q, points_inside[0], points_outside[0]);

		printf("le 1 = %f\n", points_inside[1].x);
		printf("le 1 = %f\n", clipped_triangle[1].vertice[0].x);

		clipped_triangle[1].vertice[0] = points_inside[1];
		clipped_triangle[1].vertice[1] = clipped_triangle[0].vertice[2];
		clipped_triangle[1].vertice[2] = ft_vector_intersect(plane_N,  point_plane_Q, points_inside[1], points_outside[0]);
		SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 0, 255, 0, 255);
		result = 2;
	}
	else if (n_inside_points == 3)
	{
		printf("do nothing\n");
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = points_inside[1];
		clipped_triangle[0].vertice[2] = points_inside[2];
		SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 0, 0, 255, 255);
		result = 1;
	}
	return (result);
}
