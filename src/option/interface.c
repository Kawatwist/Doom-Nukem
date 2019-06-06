/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:44:02 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/29 18:53:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		option_interface(t_win *wn)
{
	if (wn->interface == KOPTION)
		keyboardoption(wn);
	else if (wn->interface == GOPTION)
		graphismeoption(wn);
	else if (wn->interface == COPTION)
		controloption(wn);
	else
		menuoption(wn);
}
