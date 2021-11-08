/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:36:45 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 19:36:46 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_spaces_2(t_list *g_shell)
{
	int		i;
	int		start;
	char	*res;
	int		flag;

	res = ft_strdup("");
	i = 0;
	flag = 0;
	start = 0;
	while (g_shell->rest[i] != '\0')
	{
		i = skip_onlyspaces(i, g_shell, &res);
		i = get_only_char(g_shell->rest, i, &res);
		i++;
	}
	return (res);
}

void	get_rest_command(t_list *g_shell)
{
	int		i;
	int		len;
	char	*ptr;
	char	*s;


				i = skip_spaces(0, g_shell->buffer);
	len = ft_strlen(g_shell->buffer);
	
	g_shell->rest = ft_substr(g_shell->buffer, i, len - i);
	ptr = g_shell->rest;
	g_shell->rest = remove_spaces(g_shell);
	free(ptr);
	
	if (g_shell->rest && ft_check_restt() > 1)
	{
		s = g_shell->rest;
		g_shell->rest = remove_quotes(g_shell->rest);
		if (ft_strcmp(g_shell->rest, ""))
			free(s);
	}
	
	
}

char	*split_and_join(char *ptr)
{
	char	**t;
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	t = ft_split(ptr, ' ');
	while (t[i] != 0)
	{
		str = ft_strjoin(str, t[i]);
		if (t[i + 1] != 0)
			str = ft_strjoin(str, ft_strdup(" "));
		i++;
	}
	return (str);
}

char	*inside_dquotes(char *str, int *i)
{
	int		start;
	char	c;
	char	*res;
	char	*s;
	char	*ss;

	c = str[*i];
	*i = *i + 1;
	start = *i;
	while (str[*i] != '\0')
	{
		if (str[*i] == c)
		{
			ss = ft_strdup("");
			s = ft_substr(str, start, *i - start);
			res = ft_strjoin(ss, s);
			free(s);
			free(ss);
			*i = *i + 1;
			return (res);
		}
		*i = *i + 1;
	}
	return (0);
}

void	free_tab(void)
{
	int	i;

	i = 0;
	while (g_shell->tab[i])
	{
		free(g_shell->tab[i]);
		i++;
	}
	free(g_shell->tab);
}
