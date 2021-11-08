/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:05:10 by nainhaja          #+#    #+#             */
/*   Updated: 2019/10/21 17:01:38 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_restt(void)
{
	char	**s;
	int		i;

	i = 0;
	s = ft_split(g_shell->buffer, ' ');
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (i);
}

static int	ft_clen(int a)
{
	int	i;

	i = 0;
	if (a < 0)
		i++;
	while (a != 0)
	{
		a = a / 10;
		i++;
	}
	return (i);
}

static char	*ft_rev(char *s, int a, int len)
{
	int		i;
	char	tmp;

	i = 0;
	if (a < 0)
		i++;
	len--;
	while (i < len)
	{
		tmp = s[i];
		s[i] = s[len];
		s[len] = tmp;
		i++;
		len--;
	}
	return (s);
}

static char	*ft_remplir(char *s, int a, int len)
{
	int				i;
	unsigned int	n;

	i = 0;
	if (a < 0)
	{
		s[i] = '-';
		i++;
		a = a * (-1);
	}
	n = a;
	while (i < len)
	{
		s[i] = (char)(n % 10) + 48;
		n = n / 10;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int a)
{
	int		len;
	char	*s;

	len = ft_clen(a);
	if (a != 0)
		s = (char *)malloc(sizeof(char) * (len + 1));
	else
	{
		s = (char *)malloc(sizeof(char) * (len + 2));
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	if (s == 0)
		return (0);
	s = ft_remplir(s, a, len);
	s = ft_rev(s, a, len);
	return (s);
}
