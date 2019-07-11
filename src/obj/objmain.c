/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:17:44 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 11:47:42 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

static void		*free_obj(t_obj *obj)
{
	(void)obj;
	// FREE STRUCT HERE
	return (NULL);
}

static int		init_obj(t_obj *obj)
{
	if ((obj->elem = malloc(sizeof(t_elem))) == NULL)
		return (1);
	obj->elem->next = NULL;
	obj->point = NULL;
	obj->normal = NULL;
}

t_obj			*load_obj(const char *path)
{
	t_obj *obj;

	obj = NULL;
	if ((obj = malloc(sizeof(t_obj))) == NULL)
		return (NULL);
	if (ini_tobj(obj) == 1)
		return (free_obj(obj));
	return (obj);
}
