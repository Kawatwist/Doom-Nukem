/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:57:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/12 13:04:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		setcloud(t_win *wn, int nb_cloud)
{
	t_cloud *tmp;
	t_text	*img;
	int		nb;

	tmp = wn->cloud;
	deletcloud(wn);
	setcloudsize(wn);
	nb = 0;
	while (nb < nb_cloud)
	{
		if (tmp->next != NULL)
		{
			tmp = tmp->next;
			nb++;
		}
		else
		{
			(tmp->next = malloc(sizeof(t_cloud))) == NULL
				? stop_exec("Fail malloc cloud\n", wn) : 0;
			tmp = tmp->next;
			img = (findpostxt(wn, "game", "skybox",
						rand() % 2 == 0 ? "bribri" : "cloudy"));
			tmp->txt = img->txt;
			tmp->tmp = 0;
			tmp->flag = 0;
			tmp->size = rand() % 300 + 200;
			tmp->life = (rand() % 350) + 350;
			tmp->start = (rand() % wn->xscreen) * 3;
			tmp->sens = (tmp->start > (wn->xscreen * 1.5) ? 1 : 0);
			tmp->next = NULL;
			nb++;
		}
	}
}

void		setcloudsize(t_win *wn)
{
	t_cloud *tmp;

	tmp = wn->cloud;
	while (tmp != NULL && tmp->next != NULL)
	{
		tmp->currsize = (((float)(tmp->life / ((tmp->life - tmp->tmp == 0 ? 1 : (tmp->life - tmp->tmp))))) * (tmp->size));
		tmp = tmp->next;
	}
}
