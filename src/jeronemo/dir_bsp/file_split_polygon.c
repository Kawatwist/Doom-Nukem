/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_split_polygon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:20:59 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/20 00:29:19 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h> 


int			ft_get_intersect(t_myvec *line_start,
		t_myvec *line_end,
		t_myvec *vertex,
		t_myvec *normal,
		t_myvec *intersection,
		float *percentage)
{
	t_myvec		direction;
	t_myvec		L1;
	float		line_length;
	float		dist_from_plane;

	direction.x = line_end->x - line_start->x;
	direction.y = line_end->y - line_start->y;
	direction.z = line_end->z - line_start->z;

	line_length = ft_dot_product(direction, normal);

	if (fabsf(line_length) < 0.0001)
		return 0;

	L1.x = vertex->x - line_start->x;
	L1.y = vertex->y - line_start->y;
	L1.z = vertex->z - line_start->z;

	dist_from_plane = ft_dot_product(L1, normal);
	percentage = dist_from_plane / line_length;

	if (percentage<0.0f)
		return (0);
	else if (percentage > 1.0f)
		return (0);

	intersection->x = line_start->x + direction.x * (percentage);
	intersection->y = line_start->y + direction.y * (percentage);
	intersection->z = line_start->z + direction.z * (percentage);
	return (1);
}

t_myvec		*ft_calculate_tex_coor(t_mypolygon *poly, t_myvec *intersect_point, int current_vertex, float percent, int i)
{
	float		delta_x;
	float		delta_y;
	float		tex_x;
	float		tex_y;

	delta_x = Poly->VertexList[CurrentVertex].tu - Poly->vertex_list[i - 1].x//.tu;
	delta_y = Poly->VertexList[CurrentVertex].tv - Poly->vertex_list[i - 1].y//.tv;
	tex_x = Poly->vertex_list[i - 1].x/*tu*/ + (delta_x * percent);
	tex_y = Poly->vertex_list[i - 1].y/*tv*/ + (delta_y * percent);
	return (D3DLVERTEX(intersect_point, RGB_MAKE(255,255,255), 0, tex_x, tex_y)); 
	//focntion d'application de texture
	//tu = Values describing the texture coordinates of the vertex.
	//tv = Values describing the texture coordinates of the vertex.
}

void		ft_split_polygon(t_mypolygon *poly, t_mypolygon *plane, t_mypolygon *front_split, t_mypolygon *back_split)
{
	t_myvec		front_list[20];
	t_myvec		back_list[20];
	t_myvec		first_vertex;
	t_myvec		plane_normal;
	t_myvec		intersect_point;
	t_myvec		point_on_plane;
	t_myvec		point_a;
	t_myvec		point_b;
	int			front_counter = 0;
	int			back_counter = 0;
	int			i = 0;
	int			current_vertex;
	float		percent;


	point_on_plane = plane->vertex_lst[0]t;  //un point fesant partis du polygon splitter
	first_vertex = poly->vertex_lst[0];
	int result;
	result = ft_classify_point(first_vertex, plane);
	if (result == FRONT)
		front_list[front_counter++] = first_vertex;
	else if (result == BACK)
		back_list[back_counter++] = first_vertex;
	else if (result == ON_PLANE)
	{
		front_list[front_counter++] = first_vertex;
		back_list[back_counter++] = first_vertex;
	}
	////////////////////////////////////
	i = 1;
	while (i < poly->number_of_vertex + 1)
	{
		////on boucle le dernier point avec le premier
		if (i == poly->number_of_vertex)
			current_vertex = 0;
		else
			current_vertex = i;

		point_a = poly->vertex_list[i - 1];  ///////a changer
		point_b = poly->vertex_list[current_vertex]; ///// a changer

		result = ft_classify_point(point_b, plane);

		if (result == ON_PLANE) //// on ajoute au deux list
		{
			front_list[front_counter++] = poly->vertex_list[current_vertex];
			back_list[back_counter++] = poly->vertex_list[current_vertex];
		}
		else
		{

			if (ft_get_intersect(point_a, point_b, point_on_plane, plane_normal, intersect_point, percent))
			{
				copy = ft_calculate_tex_coor(poly, intersect_point, current_vertex, percent, i)
					/////si il y intersection if a edge get intersect
					if (result == FRONT)
					{
						back_list[back_counter++] = copy;
						front_list[FrontCounter++] = copy;
						if (current_vertex != 0)
							front_list[front_counter++] = poly->vertex_list[current_vertex];
					}
				if (result == BACK)
				{
					front_list[front_counter++] = copy;
					back_list[back_counter++] = copy;
					if (current_vertex != 0)
						back_list[back_counter++] = poly->vertex_list[current_vertex];
				}
				else
				{
					///// si il il n'y a pas d'intersection
					if (result == FRONT && current_vertex != 0)
						front_list[front_counter++] = poly->vertex_list[current_vertex]; ///// a changer
					if (result == BACK && curent_vertex != 0)
						back_list[back_counter++] = poly->vertex_list[current_vertex]; ///// a changer
				}
			}
			i++;
		}
		front_split->number_of_vertices = 0;
		back_split->number_of_Vertices = 0;

		i = 0;
		while (i < front_counter)
		{
			front_split->number_of_vertices++;
			front_split->vertex_list[i] = front_list[i];
			i++;
		}

		i = 0;
		while (i < back_counter)
		{
			back_split->number_of_vertices++;
			Back_split->vertex_list[i] = back_list[i];
			i++;
		}

		back_split->number_of_indices = (back_split->number_of_vertices - 2) * 3;
		front_split->number_of_indices = (front_split->number_of_vertices - 2) * 3;

		// Fill in the Indices Array
		int		v0;
		int		v1;
		int		v2;
		i = 0;
		// for (loop=0;loop<FrontSplit->NumberOfIndices/3;loop++)
		while (i < front_split->number_of_indices / 3)
		{
			if (i == 0)
			{
				v0 = 0;
				v1 = 1;
				v2 = 2;
			}
			else
			{
				v1 = v2;
				v2++;
			}
			front_split->indices[loop * 3] = v0;
			FrontSplit->indices[(loop * 3) + 1] = v1;
			FrontSplit->indices[(i * 3) + 2] = v2;
			i++;
		}

		i = 0;
		while (i < back_split->number_of_indices / 3)
		{
			if (i == 0)
			{
				v0 = 0;
				v1 = 1;
				v2 = 2;
			}
			else
			{
				v1 = v2;
				v2++;
			}
			back_split->indices[i * 3] = v0;
			back_split->indices[(i * 3) + 1] = v1;
			back_split->indices[(i * 3) + 2] = v2;
			i++;
		}
		// calculate polygon Normals

		t_myvect edg1;
		t_myvect edg2;

		edge1 = front_split->vertex_list[front_split->indices[1]] - front_split->vertex_list[front_split->indices[0]];

		edge2 = front_split->vertex_list[front_split->indices[front_split->number_of_indices - 1]] - front_split->vertex_list[front_split->indices[0]];

		front_split->normal = ft_cross_product(edge1, edge2);
		front_split->normal = ft_normalise(front_split->normal);

		edge1 = back_split->vertex_list[back_split->indices[1]] - back_split->vertex_list[back_split->indices[0]];

		edge2 = back_split->vertex_list[back_split->indices[back_split->number_of_indices - 1]] - back_split->vertex_list[back_split->indices[0]];

		back_split->normal = ft_cross_product(edge1, edge2);
		back_split->normal = ft_normalise(back_split->normal);
	}
	void SplitPolygon(POLYGON *Poly,POLYGON *Plane,POLYGON *FrontSplit,POLYGON *BackSplit) 
		//nombre de vertex
		//nombre d'indices
		//tableau d'indices
}



