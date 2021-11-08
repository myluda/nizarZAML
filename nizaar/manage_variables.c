/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:58:33 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 15:58:34 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_beforeeq(char *k)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * strlen(k));
	while (k[i])
	{
		if (k[i] == '=')
		{
			str[i] = 0;
			break ;
		}
		str[i] = k[i];
		i++;
	}
	return (str);
}

void	stock_path(t_list *g_shell, char *str)
{
	int		i;
	char	*path;
	char	*test;

	i = 0;
	if (strstr(str, "PATH") != NULL)
	{
		path = strstr(str, "PATH");
		g_shell->path = ft_split(&path[5], ':');
		while (g_shell->path[i])
		{
			test = g_shell->path[i];
			g_shell->path[i] = ft_strjoin(g_shell->path[i], "/");
			free(test);
			i++;
		}
	}
}

char	*ft_aftereq(char *k, t_list *g_shell)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(char) * strlen(k));
	i = 0;
	j = 0;
	stock_path(g_shell, k);
	i = 0;
	while (k[i])
	{
		if (k[i] == '=')
		{
			i++;
			while (k[i] == ' ')
				i++;
			break ;
		}
		i++;
	}
	free(str);
	str = ft_strdup(k + i);
	return (str);
}
