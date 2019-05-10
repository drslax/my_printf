/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:29:28 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/20 01:50:53 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*string;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if ((string = (char *)malloc(sizeof(char) * (len + 1))))
	{
		while (s[i] != '\0' && i < len)
		{
			string[i] = s[start];
			start++;
			i++;
		}
		while (i < len)
		{
			string[i] = '\0';
			i++;
		}
		string[i] = '\0';
		return (string);
	}
	return (NULL);
}
