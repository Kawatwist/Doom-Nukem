/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:08:20 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/09 14:08:40 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_mytriangle	*ft_triangle_node_create(t_mytriangle tri)
{
	t_mytriangle	*triangle;

	triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle));
	triangle = memcpy(triangle, &tri, sizeof(t_mytriangle));
	triangle->next = NULL;
	return (triangle);
}

void			ft_triangle_add_node(t_mytriangle **lst, t_mytriangle *node)
{
	if (*lst == NULL)
	{
		*lst = node;
	}
	else
	{
		node->next = *lst;
		*lst = node;
	}
}

t_mytriangle	*ft_get_before(t_mytriangle *head, t_mytriangle *node)
{
	t_mytriangle	*before;

	before = head;
	if (before == node)
		return (NULL);
	while (before->next && before->next != node && before != NULL)
		before = before->next;
	return (before);
}

void	ft_swap_node_with_the_next(t_mytriangle **head, t_mytriangle *node2)
{
	t_mytriangle	*bfr;
	t_mytriangle	*tmp;

	bfr = ft_get_before(*head, node2);
	tmp = node2->next->next;
	if (bfr == NULL)
	{
		(*head) = node2->next;
		(*head)->next = node2;
		node2->next = tmp;
	}
	else
	{
		bfr->next  = node2->next;
		bfr->next->next = node2;
		node2->next= tmp;
	}
}
