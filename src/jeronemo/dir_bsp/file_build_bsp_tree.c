/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_build_bsp_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:02:54 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/21 16:47:01 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h>

static void			ft_split_then_distribute(t_mypolygon **front_lst, t_mypolygon **back_lst, t_mypolygon *splitter, t_mypolygon *polygon_lst)
{
	t_mypolygon		*front_split;
	t_mypolygon		*back_split;

	front_split = (t_mypolygon*)malloc(sizeof(t_mypolygon));
	ft_bzero(front_split, sizeof(t_mypolygon));
	back_split = (t_mypolygon*)malloc(sizeof(t_mypolygon));
	ft_bzero(back_split, sizeof(t_mypolygon));
	ft_split_polygon(polygon_lst, splitter, front_split, back_split);
	ft_add_polygon(front_lst, front_split);
	ft_add_polygon(back_lst, back_split);
}

void		ft_build_bsp_tree(t_mynode *current_node, t_mypolygon *polygon_lst)
{
	t_mypolygon		*poly_test;
	t_mypolygon		*next_poly_keeper = NULL;
	t_mynode		*new_node;

	// t_mypolygon		*keep;
	t_mypolygon		*back_lst;
	t_mypolygon		*front_lst;
	// t_mynode		*new_front;
	// t_mynode		*new_back;
	int				result;


/////////////////////affichage///////////////////
	printf("\n=======================>CREATION DUN NODE\n");
	poly_test = polygon_lst;
	printf("== La liste des poly :\n");
	while (poly_test != NULL)
	{
		printf("==id =%d\n", poly_test->id);
		poly_test = poly_test->next;
	}
/////////////////////affichage///////////////////
	poly_test = polygon_lst;

	back_lst = NULL;
	front_lst = NULL;
	current_node->splitter = ft_select_the_best_poly_splitter(poly_test);


	printf("======> On choisit le spliter ayant %d vertex\n", current_node->splitter->number_of_vertex);
	while (poly_test != NULL)
	{
		next_poly_keeper = poly_test->next;
		//poly_test->next sera deplacé dans les "if", donc creer un keeper
		if (poly_test != current_node->splitter)
		{
			result = ft_classify_polygon(current_node->splitter, poly_test);
			if (result == FRONT || result == ON_PLANE)
			{
				printf("Le polygon id %d est front\n", poly_test->id);
				poly_test->next = front_lst;
				front_lst = poly_test;
			}
			else if (result == BACK)
			{
				printf("Le polygon id %d est back\n", poly_test->id);
				poly_test->next = back_lst;
				back_lst = poly_test;
			}
			else if (result == SPANNING)
			{
				printf("\n===========Le polygon id %d will be splitted by polygon id %d------\n\n", poly_test->id, current_node->splitter->id);
				ft_split_then_distribute(&front_lst, &back_lst, current_node->splitter, poly_test);
				free(poly_test);
				poly_test = NULL;
				 //the polygon splited is of no use any more, so free this polygon.
				//And the vertex_list of the polygon is relocated in ft_split_polygon(), so no need to free
			}
		}
		poly_test = next_poly_keeper;
	}

	////////////affichage////////////////////
	t_mypolygon *keep = front_lst;
	printf("== La liste front :\n");
	while (keep != NULL)
	{
		printf("==id =%d\n", keep->id);
		keep = keep->next;
	}
	keep = back_lst;
	printf("== La liste back :\n");
	while (keep != NULL)
	{
		printf("==id =%d\n", keep->id);
		keep = keep->next;
	}
	////////////affichage////////////////////




	///////////gestion du fils front
	new_node = (t_mynode*)malloc(sizeof(t_mynode));
	ft_bzero(new_node, sizeof(t_mynode));
	if (front_lst == NULL)
	{
		new_node->is_leaf = TRUE;
		new_node->is_solid = FALSE;
		current_node->front = new_node;
	}
	else if (front_lst != NULL)
	{
		new_node->is_leaf = FALSE;
		current_node->front = new_node;
		ft_build_bsp_tree(new_node, front_lst);
	}
	///////////gestion du fils back
	new_node = (t_mynode*)malloc(sizeof(t_mynode));
	ft_bzero(new_node, sizeof(t_mynode));
	if (back_lst == NULL)
	{
		new_node->is_leaf = TRUE;
		new_node->is_solid = TRUE;
		current_node->back = new_node;
	}
	else if (back_lst != NULL)
	{
		new_node->is_leaf = FALSE;
		current_node->back = new_node;
		ft_build_bsp_tree(new_node, back_lst);
	}
}
