/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:55:33 by naali             #+#    #+#             */
/*   Updated: 2019/07/09 12:23:17 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		COMPONENTS_H
# define	COMPONENTS_H

#include "inventaire.h"

typedef struct	s_component	t_component;

struct		s_component
{
	unsigned int	id;
	char			*name;
	unsigned int	qty;
	t_component		*next;
	t_component		*previous;
};

/* COMPONENT */
t_component			*new_compo(char *name, unsigned int qty, t_consumable **start);
/* void				pushback_compo(t_component **start, t_component *node); */
/* void				destroy_compo_list(t_component **start); */
/* int					compo_list_len(t_component **start); */
/* t_component			*get_compo_by_id(t_component **start, unsigned int id); */
/* void				compo_swap_elem(t_component **start, \ */
/* 									unsigned int id1, unsigned int id2); */
/* void				destroy_one_compo(t_component **start, unsigned int id); */

#endif
