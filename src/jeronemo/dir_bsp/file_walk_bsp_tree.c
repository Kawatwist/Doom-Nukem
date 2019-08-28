/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_walk_bsp_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:14:28 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/27 12:14:35 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h>

void	ft_copy_and_add_bot(t_mypolygon **alst, t_mypolygon *new)
{
	t_mypolygon	*tmp;
	t_mypolygon *copy;

	copy = (t_mypolygon*)malloc(sizeof(t_mypolygon));
	if (!copy)
		return ;
	*copy = *new;
	copy->next = NULL;
	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = copy;
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = copy;
	}
}

void	ft_walk_bsp_tree(t_mynode *s_node, t_myvec *pos, t_mypolygon **new_lst)
{
	int			result;

	if (s_node->is_leaf == TRUE)
		return ;
	result = ft_classify_point(*pos, s_node->splitter);
	if (result == FRONT)
	{
		if (s_node->back != NULL)
		{
			ft_walk_bsp_tree(s_node->back, pos, new_lst);
			ft_copy_and_add_bot(new_lst, s_node->splitter);
		}
		if (s_node->front != NULL)
			ft_walk_bsp_tree(s_node->front, pos, new_lst);
		return ;
	}
	// this happens if we are at back or on plane
	if (s_node->front != NULL)
		ft_walk_bsp_tree(s_node->front, pos, new_lst);
	if (s_node->back != NULL)
		ft_walk_bsp_tree(s_node->back, pos, new_lst);
}