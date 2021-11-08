/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:33:43 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 19:33:45 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*inside_squotes(char *str, int *i)
{
	int		start;
	char	c;
	char	*res;

	start = *i + 1;
	c = str[*i];
	*i = *i + 1;
	while (str[*i] != '\0')
	{
		if (str[*i] == c)
		{
			res = ft_substr(str, start, *i - start);
			*i = *i + 1;
			return (res);
		}
		*i = *i + 1;
	}
	return (0);
}

int	check_dollarq(t_list *g_shell, int i)
{
	if (g_shell->buffer[i + 1] == '?' && (g_shell->buffer[i + 2] == ' '
			|| g_shell->buffer[i + 2] == '$' || g_shell->buffer[i + 2] == '\0'))
		return (1);
	else
		return (0);
}

char	*dollar_cases(char *ptr, int *i, t_list *g_shell, int start)
{
	char	*str;
	char	*s;
	char	*p;
	char	*kk;

	
	if (!ptr)
		ptr = ft_strdup("");
	str = ptr;
	p = ft_substr(g_shell->buffer, start, *i - start);
	ptr = ft_strjoin(ptr, p);
	free(p);
	free(str);
	if (check_dollarq(g_shell, *i))
	{
		*i = *i + 2;
		return (ft_strjoin(ptr, ft_itoa(g_shell->g_exit_code)));
	}
	else
	{
		s = expand_variable(g_shell, g_shell->buffer, i, ptr);
		// if (ft_strcmp(ptr, s) == 0)
		// 	free(p);
		return (s);
	}
}

void	clear_leaks(char *ptr, char *str, int start, int i)
{
	char	*ss;
	char	*s;

	ss = g_shell->buffer;
	s = ft_substr(g_shell->buffer, start, i - start);

	if (start != 0)
		g_shell->buffer = ft_strjoin(ptr, s);
	if (ss != g_shell->buffer)
		free(ss);
	free(s);
	
}

void	expand_command(t_list *g_shell)
{
	char	*ptr;
	int		i;
	int		start;
	char	*str;
	char	*p;

	i = 0;
	start = 0;
	ptr = NULL;
	while (g_shell->buffer[i] != '\0')
	{
		if (g_shell->buffer[i] == '\'')
			i = skip_quotes(i + 1, '\'', g_shell->buffer);
		else if (g_shell->buffer[i] == '$' && g_shell->buffer[i + 1] != ' '
			&& g_shell->buffer[i + 1] != '\0')
		{
			ptr = dollar_cases(ptr, &i, g_shell, start);
			start = i;
		}
		else
			i++;
	}
	clear_leaks(ptr, str, start, i);
	free(ptr);
}
