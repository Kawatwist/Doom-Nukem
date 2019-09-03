/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_split_polygon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:51:26 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/25 15:51:31 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h>

int			ft_get_intersect(t_myvec *line_start,
							t_myvec *line_end,
							t_myvec *vertex_on_plane,
							t_myvec *normal,
							t_myvec *intersection,
							float	*percentage)
{
	t_myvec		direction;
	t_myvec		line1; //vercteur from start point to vertex on splitter plane
	float		line_dist_to_plane; // distance vers splitter plane du point de start + celui du point end
	float		start_dist_to_plane;

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
	(*percentage) = start_dist_to_plane / line_dist_to_plane;
 	if ((*percentage) < 0.0 || (*percentage) > 1.0)
  		return (FALSE);
  	intersection->x = line_start->x + direction.x * (*percentage);
  	intersection->y = line_start->y + direction.y * (*percentage);
  	intersection->z = line_start->z + direction.z * (*percentage);
  	intersection->u = line_start->u + (line_end->u - line_start->u) * (*percentage);
  	intersection->v = line_start->v + (line_end->v - line_start->v) * (*percentage);
  	intersection->w = 1.0;
	return (TRUE);
}

t_myvec		*ft_copy_vertex_node(t_myvec *node_to_copy)
{
	t_myvec		*new_node;

	new_node = (t_myvec *)malloc(sizeof(t_myvec));
	if (!new_node)
		return (NULL);
	*new_node = *node_to_copy;
	return(new_node);
}

static void			ft_fill_splitted_node(t_mypolygon *front_split,
										t_mypolygon *back_split,
										t_mypolygon *poly)
{
	front_split->normal = poly->normal;
	front_split->number_of_indices = ft_calculate_number_of_indices(front_split);
	front_split->indices = ft_calculate_indices_tab(front_split);
	front_split->id = (poly->id) * 100 + 1;
	back_split->normal = poly->normal;
	back_split->number_of_indices = ft_calculate_number_of_indices(back_split);
	back_split->indices = ft_calculate_indices_tab(back_split);
	back_split->id = (poly->id) * 100 + 2;
}

static void		ft_put_first_vertex_in_lst(t_mypolygon *front_split,
											t_mypolygon *back_split,
											t_mypolygon *poly,
											t_mypolygon *plane)
{
	int			result;
	t_myvec 	*first_vertex;

	first_vertex = (poly->vertex_lst);
	result = ft_classify_point(*first_vertex, plane);
	if (result == FRONT)
	{
		ft_add_vertex(&(front_split->vertex_lst), first_vertex);
		front_split->number_of_vertex++;
	}
	else if (result == BACK)
	{
		ft_add_vertex(&(back_split->vertex_lst), first_vertex);
		back_split->number_of_vertex++;
	}
	else if (result == ON_PLANE)
	{
		ft_add_vertex(&(front_split->vertex_lst), first_vertex);
		ft_add_vertex(&(back_split->vertex_lst), first_vertex);
		front_split->number_of_vertex++;
		back_split->number_of_vertex++;
	}
}

void		ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split)
{
	t_myvec					intersect_point;
	t_myvec					*point_on_plane;
	t_myvec					*point_a;
	t_myvec					*point_b;
	t_myvec					*tmp_vertex;
	int						i;
	int						result;
	t_myvec					*next_vertex_keeper;
	t_myvec 				*first_vertex_keeper;
	float					percentage;

	percentage = 0.0;
	ft_bzero(&intersect_point, sizeof(t_myvec));
	next_vertex_keeper = NULL;
	point_on_plane = plane->vertex_lst;  //un point faisant partis du polygon splitter
	point_a = poly->vertex_lst;
	point_b = point_a->next;
	first_vertex_keeper = ft_copy_vertex_node(poly->vertex_lst);
	next_vertex_keeper = point_b->next;
	ft_put_first_vertex_in_lst(front_split, back_split, poly, plane);
	i = 0;
	while (i < poly->number_of_vertex)
	{
		result = ft_classify_point(*point_b, plane);
		if (result == ON_PLANE && i < poly->number_of_vertex - 1) //// on ajoute au deux list
		{
			ft_add_vertex(&(front_split->vertex_lst), point_b);
			ft_add_vertex(&(back_split->vertex_lst), point_b);
			front_split->number_of_vertex++;
			back_split->number_of_vertex++;
		}
		else
		{
			if (ft_get_intersect(point_a, point_b, point_on_plane, &(plane->normal), &intersect_point, &percentage) == TRUE)
			{
				tmp_vertex = ft_copy_vertex_node(&intersect_point);
				ft_add_vertex(&(front_split->vertex_lst), tmp_vertex);
				tmp_vertex = ft_copy_vertex_node(&intersect_point);
				ft_add_vertex(&(back_split->vertex_lst), tmp_vertex);
				front_split->number_of_vertex++;
				back_split->number_of_vertex++;
			}
			if (result == FRONT && i < poly->number_of_vertex - 1)
			{
				ft_add_vertex(&(front_split->vertex_lst), point_b);
				front_split->number_of_vertex++;
			}
			if (result == BACK && i < poly->number_of_vertex - 1)
			{
				ft_add_vertex(&(back_split->vertex_lst), point_b);
				back_split->number_of_vertex++;
			}
		}
		point_a = point_b;
		if (next_vertex_keeper == NULL)
			point_b = first_vertex_keeper;
		else
		{
			point_b = next_vertex_keeper;
			next_vertex_keeper = point_b->next;
		}
		i++;
	}
	free(first_vertex_keeper);
	ft_fill_splitted_node(front_split, back_split, poly);
}
