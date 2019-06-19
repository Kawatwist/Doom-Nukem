/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_split_polygon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:20:59 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/19 14:16:19 by jleblond         ###   ########.fr       */
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
	t_myvec					plane_normal;
	t_myvec					intersect_point;
	t_myvec					*point_on_plane;
	t_myvec					*point_a;
	t_myvec					*point_b;
	t_myvec					*tmp_vertex;
	int						front_counter = 0;
	int						back_counter = 0;
	unsigned int			i;
	float					percent;
	int						result;
	t_myvec					*next_vertex_keeper;
	t_myvec 				*first_vertex_keeper;


	point_on_plane = plane->vertex_lst;  //un point faisant partis du polygon splitter
	first_vertex_keeper = poly->vertex_lst;
	point_a = poly->vertex_lst;
	point_b = point_a->next;

//////////////////add the first vertex in lst

	result = ft_classify_point(*point_a, plane);
	if (result == FRONT)
	{
		printf("vertex 0 is on the front\n");
		ft_add_vertex(&(front_split->vertex_lst), point_a);
		front_counter++;
	}
	else if (result == BACK)
	{
		printf("vertex 0 is on the back\n");
		ft_add_vertex(&(back_split->vertex_lst), point_a);
		back_counter++;
	}
	else if (result == ON_PLANE)
	{
		printf("vertex 0 is on plane\n");
		ft_add_vertex(&(front_split->vertex_lst), point_a);
		ft_add_vertex(&(back_split->vertex_lst), point_a);
		front_counter++;
		back_counter++;
	}



	////////////////////////////////////
	i = 0;
	printf("number_of_vertex:%d\n", poly->number_of_vertex);
	while (i < poly->number_of_vertex)
	{
		next_vertex_keeper = point_b->next;
		result = ft_classify_point(*point_b, plane);
		if (result == ON_PLANE && next_vertex_keeper != NULL) //// on ajoute au deux list
		{
			printf("vertex is on plane\n");
			ft_add_vertex(&(front_split->vertex_lst), point_b);
			ft_add_vertex(&(back_split->vertex_lst), point_b);
			front_counter++;
			back_counter++;
		}
		else
		{
			printf("\nvertex number %d vertex is not on the splitter, intersect point test:\n", i + 1);
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
			if (result == FRONT && next_vertex_keeper != NULL)
			{
				ft_add_vertex(&(front_split->vertex_lst), point_b);
				front_counter++;
			}
			else if (result == BACK && next_vertex_keeper != NULL)
			{
				ft_add_vertex(&(back_split->vertex_lst), point_b);
				back_counter++;
			}
		}
		point_a = point_b;
		if (next_vertex_keeper == NULL)
			point_b = first_vertex_keeper;
		else
			point_b = next_vertex_keeper;
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



