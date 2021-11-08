/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:58:01 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 18:58:02 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_only_char(char *str, int i, char **res)
{
	int		start;
	char	*s;
	char	*ptr;

	start = i;
	while (str[i] != ' ' && str[i] != '\'' && str[i] != '"' && str[i] != '\0')
		i++;
	ptr = *res;
	s = ft_substr(str, start, i - start);
	*res = ft_strjoin(*res, s);
	free(s);
	free(ptr);
	return (i);
}

int	skip_onlyspaces(int i, t_list *g_shell, char **res)
{
	int		flag;
	int		test;
	char	*str;
	char	*ptr;

	flag = 0;
	test = 0;
	ptr = ft_strdup(" ");
	while (g_shell->rest[i] == ' ' && g_shell->rest[i] != '\''
		&& g_shell->rest[i] != '"' && g_shell->rest[i] != '\0')
	{
		i++;
		flag = 1;
	}
	if (flag == 1 && g_shell->rest[i] != '\0')
	{
		str = *res;
		*res = ft_strjoin(*res, ptr);
		free(str);
	}
	free(ptr);
	return (i);
}

int	skip_quotes(int i, char c, char *str)
{
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return i;
	else
		return (i + 1);
}

void	skip_it(int *i, char **res)
{
	char	*str;
	int		start;

	start = *i;
	*i = skip_quotes(*i + 1, g_shell->rest[*i], g_shell->rest);
	str = ft_substr(g_shell->rest, start, *i - start);
	*res = ft_strjoin(*res, str);
	free(str);
}

char	*remove_spaces(t_list *g_shell)
{
	int		i;
	char	*res;
	int		flag;
	char	*ptr;

	res = ft_strdup("");
	i = 0;
	flag = 0;
	ptr = res;
	while (g_shell->rest[i] != '\0')
	{
		while ((g_shell->rest[i] == '\''
				|| g_shell->rest[i] == '"') && g_shell->rest[i] != '\0')
			skip_it(&i, &res);
		i = skip_onlyspaces(i, g_shell, &res);
		if (g_shell->rest[i] != '\0')
			i = get_only_char(g_shell->rest, i, &res);
	}
	// if (ft_strcmp(g_shell->rest, "") == 0
	// 	|| g_shell->rest[0] == '\'' || g_shell->rest[0] == '"')
	// 	free(ptr);
	return (res);
}
