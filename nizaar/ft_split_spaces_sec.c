/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces_sec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:45:33 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/31 16:45:34 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalise_it(char **t, size_t *cpt, int *j, const char *s)
{
	t[0][*j] = s[*cpt];
	*cpt = *cpt + 1;
	*j = *j + 1;
}

void	split_spaces_sec(char **t, size_t *cpt, int *j, const char *s)
{
	if (s[*cpt] == '"')
	{
		*cpt = *cpt + 1;
		while (s[*cpt] != '"' && s[*cpt] != '\0')
			finalise_it(t, cpt, j, s);
		*cpt = *cpt + 1;
	}
	else if (s[*cpt] == '\'')
	{
		*cpt = *cpt + 1;
		while (s[*cpt] != '\'' && s[*cpt] != '\0')
			finalise_it(t, cpt, j, s);
		*cpt = *cpt + 1;
	}
	else
		finalise_it(t, cpt, j, s);
}

char	**ft_remplirr(const char *s, char c, char **t, int i)
{
	size_t	cpt;
	int		j;

	cpt = 0;
	while (s[cpt])
	{
		j = 0;
		while (s[cpt] == c && s[cpt] != '\0')
			cpt++;
		if (s[cpt] == '\0')
			break ;
		while (s[cpt] != c && s[cpt] != '\0')
			split_spaces_sec(&t[i], &cpt, &j, s);
		t[i][j] = '\0';
		i++;
		cpt++;
		if (cpt > ft_strlen(((char *)s)))
			break ;
	}
	t[i] = 0;
	return (t);
}

void	ft_word_count_sec(const char *s, int *i)
{
	if (s[*i] == '"')
	{
		*i = *i + 1;
		while (s[*i] != '"' && s[*i] != '\0')
			*i = *i + 1;
		*i = *i + 1;
	}
	else if (s[*i] == '\'')
	{
		*i = *i + 1;
		while (s[*i] != '\'' && s[*i] != '\0')
			*i = *i + 1;
		*i = *i + 1;
	}
	else
		*i = *i + 1;
}

int	ft_word_countt(const char *s, char c)
{
	int	cpt;
	int	i;

	i = 0;
	cpt = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (cpt);
		cpt++;
		while (s[i] != c)
		{
			ft_word_count_sec(s, &i);
			if (s[i] == '\0')
				return (cpt);
		}
	}
	return (cpt);
}
