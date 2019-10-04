/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_select_spliter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:47:35 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 12:59:16 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h>

//The wall with the lowest score in the list wins and becomes the splitter for that node.Here's the formula
//score=abs(frontfaces-backfaces)+(splits*8)
t_mypolygon		*ft_select_the_best_poly_splitter(t_mypolygon *polygon_lst)
{
	t_mypolygon		*poly_spliter;
	t_mypolygon		*keep;
	t_mypolygon		*polygon_node;
	int				best_score;
	int				current_score;
	int				front, back, split;
	int				result;

	poly_spliter = NULL;
	best_score = 99999999;
	keep = polygon_lst;
	polygon_node = polygon_lst;

	printf("\n\n==>Select the best splitter<==\n");
	while (polygon_node != NULL)//boucle des spliter
	{
		// printf ("On test le polygone splitter ayant id %d\n", polygon_node->id);

		current_score = 0;
		front = 0;
		back = 0;
		split = 0;
		polygon_lst = keep;
		while (polygon_lst != NULL)//boucle des polygone par rapport au splitter
		{
			if (polygon_lst == polygon_node)
				polygon_lst = polygon_lst->next;
			if (polygon_lst == NULL)
				break;
			// printf("\tOn test le polygone ayant id %d ", polygon_lst->id);
			result = ft_classify_polygon(polygon_node, polygon_lst);

			// if (result == FRONT)
			// printf(" qui est FRONT\n");
			// if (result == BACK)
			// printf(" qui est BACK\n");
			// if (result == SPANNING)
			// printf(" qui est SPANNING\n");
			// if (result == ON_PLANE)
			// printf(" qui est ON_PLANE\n");

			if (result == FRONT || result == ON_PLANE)
				front++;
			else if (result == BACK)
				back++;
			else if (result == SPANNING)
				split++;
			polygon_lst = polygon_lst->next;
		}
		current_score = ft_abs(front - back) + (split * 8);
		// printf ("\t\tle scrore de ce splitter de %d\n", current_score);
		if (current_score < best_score)
		{
			best_score = current_score;
			poly_spliter = polygon_node;
		}
		polygon_node = polygon_node->next;
	}
	polygon_lst = keep;
	printf("\n On choist le poly ayant id %d\n", poly_spliter->id);
	return (poly_spliter);
}
