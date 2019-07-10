/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrindec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:35:29 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 11:05:48 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// PRINTF ICI !

void		ft_putstrindec(char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		printf("|%d => %c|", s[i], s[i]);
		i++;
	}
	printf("\n");
}
