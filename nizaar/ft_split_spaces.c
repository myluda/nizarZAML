/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:42:48 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/31 16:42:49 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_letter_count_sec(int *j, int *cpt, const char *s)
{
	int	c;

	if (s[*j] == '"')
		c = '"';
	else if (s[*j] == '\'')
		c = '\'';
	else
		c = 'x';
	if (s[*j] != '\'' && s[*j] != '\'')
	{
		*j = *j + 1;
		*cpt = *cpt + 1;
	}
	else if (s[*j] == c)
	{
		*j = *j + 1;
		*cpt = *cpt + 1;
		while (s[*j] != c && s[*j] != '\0')
		{
			*j = *j + 1;
			*cpt = *cpt + 1;
		}
		*cpt = *cpt + 1;
		*j = *j + 1;
	}
}

static int	ft_letter_count(char const *s, char c, int *j)
{
	int	cpt;

	cpt = 0;
	while (s[*j] == c)
		*j = *j + 1;
	if (s[*j] == '\0')
		return (cpt);
	while (s[*j] != c)
	{
		if (s[*j] == '\0')
			return (cpt);
		ft_letter_count_sec(j, &cpt, s);
	}
	return (cpt);
}

static char	**ft_freemem(char **t, int r)
{
	while (r != 0)
	{
		free(t[r]);
		r--;
	}
	free(t[r]);
	free(t);
	return (0);
}

char	**ft_split_spaces(char const *s, char c)
{
	int		cpt;
	int		wc;
	int		*j;
	int		r;
	char	**t;

	cpt = 0;
	r = 0;
	wc = ft_word_countt(s, c);
	j = &cpt;
	t = (char **)malloc(sizeof(char *) * (wc + 1));
	if (t == 0)
		return (0);
	while (r < wc)
	{
		t[r] = (char *)malloc(sizeof(char) * (ft_letter_count(s, c, j) + 1));
		if (t[r] == 0)
			return (ft_freemem(t, r));
		r++;
	}
	cpt = 0;
	r = 0;
	t = ft_remplirr(s, c, t, r);
	return (t);
}
