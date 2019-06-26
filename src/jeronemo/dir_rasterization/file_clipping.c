/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:39:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/26 10:14:13 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

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

t_myvec	ft_vector_intersect(t_myvec plane_normal, t_myvec point_on_plane, t_myvec point1, t_myvec point2)
{
	//return a point if the line cross the plane
	// line intersect with plane

	//infinite ray = 0 -1 -1    lV     line direction
	//passing through 0 0 10    lp      
	//normal of plane 0 0 1     pN     
	//passing though 0 0 5      pP

	vector lV,lP,pN,pP,iP;
	t_myvec		intersection_point;

	t_myvec	line_direction = ft_vector_sub(point2, point1);
	lV.x = line_direction.x;
	lV.y = line_direction.y;
	lV.z = line_direction.z;

	lP.x = point1.x;
	lP.y = point1.y;
	lP.z = point1.z;

	pN.x = plane_normal.x;
	pN.y = plane_normal.y;
	pN.z = plane_normal.z;

	pP.x = point_on_plane.x;
	pP.y = point_on_plane.y;
	pP.z = point_on_plane.z;

	/* printf("Usage : %s <line direction, point on line, normal to plane and point on plane given as (x,y,z) tuples separated by space>"); */
	/* else{ */
	/* sscanf(argV[1],"(%lf,%lf,%lf)",&lV.x,&lV.y,&lV.z); */
	/* sscanf(argV[3],"(%lf,%lf,%lf)",&pN.x,&pN.y,&pN.z); */

	if(dotProduct(lV,pN)==0)
	{
		printf("Line and Plane do not intersect, either parallel or line is on the plane");
		exit(0);
	}
	else
	{
		/* sscanf(argV[2],"(%lf,%lf,%lf)",&lP.x,&lP.y,&lP.z); */
		/* sscanf(argV[4],"(%lf,%lf,%lf)",&pP.x,&pP.y,&pP.z); */
		iP = intersectionPoint(lV,lP,pN,pP);
		printf("Intersection point is (%lf,%lf,%lf)",iP.x,iP.y,iP.z);
		intersection_point.x = iP.x;
		intersection_point.y = iP.y;
		intersection_point.z = iP.z;
	}
	return (intersection_point);
}


int	ft_triangle_clips_again_plan(t_myvec point, t_myvec plane_norm, t_mytriangle *clipped_triangle, t_mytriangle *triangle)
{
	(void)point;
	(void)plane_norm;
	//we want the distance between the plane and the point

	t_myvec		points_inside[3];
	t_myvec		points_outside[3];
	int			n_inside_points = 0;
	int			n_outside_points = 0;
	int			distance;
	int			result = 0;
	int	j;
		t_myvec plane_N;
		t_myvec point_plane_Q;
	j = 0;
	while (j < 3)
	{
		distance = 0;
		/* float	ft_distance(t_myvec plane_N, t_myvec point_plane_Q, t_myvec point_P) */
		plane_N.x = plane_norm.x;
		plane_N.y = plane_norm.y;
		plane_N.z = plane_norm.z;
		point_plane_Q.x = point.x;
		point_plane_Q.y = point.y;
		point_plane_Q.z = point.z;

		distance = ft_distance(plane_N, point_plane_Q, triangle->vertice[j]);
		if (distance >= 0)
		{
			/* printf(" n_inside_point =%d triangle->vertice[j].x =%f et le j =%d etrange =%f\n", n_inside_points, triangle->vertice[j].x, j, points_inside[n_inside_points].x); */
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


	/* printf("LES point inside =%d\n\n", n_inside_points); */
	/* clipped_triangle[0] = *triangle; */
	/* return(1); */

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
		clipped_triangle[0].vertice[1] = points_inside[1];
/* t_myvec	ft_vector_intersect(t_myvec plane_normal, t_myvec point_on_plane, t_myvec point1, t_myvec point2) */
		clipped_triangle[0].vertice[2] = ft_vector_intersect(plane_N, point_plane_Q, points_inside[0], points_outside[0]);

		printf("le 1 = %f\n", points_inside[1].x);
		printf("le 1 = %f\n", clipped_triangle[1].vertice[0].x);

		clipped_triangle[1].vertice[0] = points_inside[1];
		clipped_triangle[1].vertice[1] = clipped_triangle[0].vertice[2];
		clipped_triangle[1].vertice[2] = ft_vector_intersect(plane_N,  point_plane_Q, points_inside[1], points_outside[0]);

		result = 2;
	}
	else if (n_inside_points == 1)
	{
		//form one triangle
		clipped_triangle[0].vertice[0] = points_inside[0];
		clipped_triangle[0].vertice[1] = ft_vector_intersect(plane_N, point_plane_Q, points_inside[0], points_outside[0]);
		clipped_triangle[0].vertice[2] = ft_vector_intersect(plane_N, point_plane_Q, points_inside[0], points_outside[1]);
		result = 1;
	}
	return (result);
}
