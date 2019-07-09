/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_inventaire.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 07:32:26 by naali             #+#    #+#             */
/*   Updated: 2019/07/09 14:09:00 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <inventaire.h>

int				print_weapo_list(t_win *wn, t_joueurs *j, int *selected)
{
	int			i;
	int			max;
	t_weapons	*tmp;

	i = 0;
	tmp = j->inv->weapo;
	max = weapo_list_len(&(j->inv->weapo));
	while (i < max)
	{
		print_items_name(wn, tmp->name, i, ((*selected == i) ? 1 : 0));
		print_items_qty(wn, ft_itoa(tmp->munition), i, ((*selected == i) ? 1 : 0));
		tmp = tmp->next;
		if (*selected == i)
			*selected = -1;
		i++;
	}
	return (i);
}

void			print_conso_list(t_win *wn, t_joueurs *j, int selected, int pos)
{
	int				i;
	int				max;
	t_consumable	*tmp;

	i = 0;
	tmp = j->inv->conso;
	max = conso_list_len(&(j->inv->conso));
	selected -= pos;
	while (i < max)
	{
		print_items_name(wn, tmp->name, pos, ((selected == i) ? 1 : 0));
		print_items_qty(wn, ft_itoa(tmp->qty), pos, ((selected == i) ? 1 : 0));
		tmp = tmp->next;
		pos++;
		i++;
	}
}
