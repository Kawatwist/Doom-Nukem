/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_split_polygon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:20:59 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/08 10:29:00 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "file_bsp.h"


int			ft_get_intersect(t_myvec *line_start,
							t_myvec *line_end,
							t_myvec *vertex_on_plane,
							t_myvec *normal,
							t_myvec *intersection)
{
	t_myvec		direction;
	t_myvec		line1; //vercteur from start point to vertex on splitter plane
	float		line_dist_to_plane; // distance vers splitter plane du point de start + celui du point end
	float		start_dist_to_plane;
	float		percentage;

	direction.x = line_end->x - line_start->x;
	direction.y = line_end->y - line_start->y;
	direction.z = line_end->z - line_start->z;
	line_dist_to_plane = ft_dot_product(direction, *normal);
	if (ft_abs_float(line_dist_to_plane) < 0.0001) // line doesn't cross plane
		return (FALSE);
	line1.x = vertex_on_plane->x - line_start->x;
	line1.y = vertex_on_plane->y - line_start->y;
	line1.z = vertex_on_plane->z - line_start->z;
	start_dist_to_plane = ft_dot_product(line1, *normal);
	percentage = start_dist_to_plane / line_dist_to_plane;
 	if (percentage < 0.0 || percentage > 1.0)
  		return (FALSE);
  	intersection->x = line_start->x + direction.x * percentage;
  	intersection->y = line_start->y + direction.y * percentage;
  	intersection->z = line_start->z + direction.z * percentage;
	return (TRUE);
}


static t_myvec		*ft_get_vertex_in_list(t_myvec *lst, unsigned int node_index)
{
	while (lst!= NULL)
	{
		if (node_index == 0)
			return (lst);
		lst = lst->next;
		node_index--;
	}
	return (NULL);
}

static t_myvec		*ft_copy_vertex_node(t_myvec *node_to_copy)
{
	t_myvec		*new_node;

	new_node = (t_myvec *)malloc(sizeof(t_myvec));
	*new_node = *node_to_copy;
	return(new_node);
}


void		ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split)
{
	t_myvec		*front_vertexlist;
	t_myvec		*back_vertexlist;
	t_myvec		plane_normal;
	t_myvec		intersect_point;
	t_myvec		*point_on_plane;
	t_myvec		*point_a;
	t_myvec		*point_b;
	t_myvec		*tmp_vertex;
	int			front_counter = 0;
	int			back_counter = 0;
	unsigned int			i;
	unsigned int			current_vertex;
	float		percent;
	int			result;

	printf("polygon to be splitted\n");
	ft_display_the_polygon_list(poly);
	point_on_plane = plane->vertex_lst;  //un point faisant partis du polygon splitter

	tmp_vertex = ft_copy_vertex_node(poly->vertex_lst);
	result = ft_classify_point(*(poly->vertex_lst), plane);
	if (result == FRONT)
	{
		printf("first vertex is on the front\n");
		ft_add_vertex(&(front_split->vertex_lst), tmp_vertex);
		front_counter++;
	}
	else if (result == BACK)
	{
		printf("first vertex is on the back\n");
		ft_add_vertex(&(back_split->vertex_lst), tmp_vertex);
		back_counter++;
	}
	else if (result == ON_PLANE)
	{
		printf("first vertex is on plane\n");
		ft_add_vertex(&(front_split->vertex_lst), tmp_vertex);
		ft_add_vertex(&(back_split->vertex_lst), tmp_vertex);
		front_counter++;
		back_counter++;
	}
	////////////////////////////////////
	i = 1;
	point_a = NULL;
	point_b = NULL;
	printf("number_of_vertex:%d\n", poly->number_of_vertex);

	while (i < poly->number_of_vertex + 1)
	{
		////on boucle le dernier point avec le premier
		if (i == poly->number_of_vertex)
			current_vertex = 0;
		else
			current_vertex = i;

		point_a = ft_get_vertex_in_list(poly->vertex_lst, i - 1);
		point_b = ft_get_vertex_in_list(poly->vertex_lst, current_vertex);
		if (point_b == NULL || point_a == NULL)
		{
			printf("ft_get_vertex_in_list: error in vertex list\n");
			exit(0) ;
		}
		result = ft_classify_point(*point_b, plane);
		tmp_vertex = ft_copy_vertex_node(point_b);
		if (result == ON_PLANE) //// on ajoute au deux list
		{
			printf("vertex is on plane\n");
			ft_add_vertex(&(front_split->vertex_lst), tmp_vertex);
			ft_add_vertex(&(back_split->vertex_lst), tmp_vertex);
			front_counter++;
			back_counter++;
		}
		else
		{
			printf("/n/nthis vertex is not on the splitter, intersect point test\n");
			if (ft_get_intersect(point_a, point_b, point_on_plane, &(plane->normal), &intersect_point) == TRUE)
			{
				printf("intersection test == TREUE\n");

				tmp_vertex = ft_copy_vertex_node(&intersect_point);
				ft_add_vertex(&(front_split->vertex_lst), tmp_vertex);
				tmp_vertex = ft_copy_vertex_node(&intersect_point);   //?????
				ft_add_vertex(&(back_split->vertex_lst), tmp_vertex);
				front_counter++;
				back_counter++;
				printf("intersect_point:  ");
				printf("x =%f\t", tmp_vertex->x);
				printf("y =%f\t", tmp_vertex->y);
				printf("z =%f\n", tmp_vertex->z);
			}
			tmp_vertex = ft_copy_vertex_node(point_b);
			if (result == FRONT && current_vertex != 0)
			{
				ft_add_vertex(&(front_split->vertex_lst), tmp_vertex);
				front_counter++;
			}
			else if (result == BACK && current_vertex != 0)
			{
				ft_add_vertex(&(back_split->vertex_lst), tmp_vertex);
				back_counter++;
			}
			printf("current vertex id :%d| front_counter:%d| back_counter:%d | \n", current_vertex, front_counter, back_counter);


		}
		i++;
	}

	/////////////////we process les deux vouveau polygones
	//normal
	//nombre de vertex
	//nombre d'indices
	//tableau d'indices
	front_split->normal = poly->normal;
	front_split->number_of_vertex = front_counter;
	front_split->id = (poly->id) * 100 + 1;
	back_split->normal = poly->normal;
	back_split->number_of_vertex = back_counter;
	back_split->id = (poly->id) * 100 + 2;
}



