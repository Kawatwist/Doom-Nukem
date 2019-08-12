/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:12:42 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 09:49:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memjoinfree(char *s1, char *s2, size_t len1, size_t len2)
{
	char 			*ret;
	unsigned int	i;

	if (!(ret = malloc(sizeof(char) * (len1 + len2))))
		return (NULL);
	i = -1;
	while (++i < len1)
		ret[i] = s1[i];
	ft_putstrindec(ret, len1);
	i = -1;
	while (++i < len2)
		ret[i + len1] = s2[i];
	ft_putstrindec(ret, len1 + len2);
	return (ret);
}
