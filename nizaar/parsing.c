/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:16:00 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 16:16:01 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*contunie_parsing(int *i, char *str, char *res)
{
	int		start;
	char	*ptr;

	start = *i;
	while (str[*i] != '\'' && str[*i] != '"' && str[*i] != '\0')
		*i = *i + 1;
	ptr = ft_substr(str, start, *i - start);
	res = ft_strjoin(res, ptr);
	free(ptr);
	return (res);
}

void	rm_quotes(char **res, int *i, char *str)
{
	char	*s;
	char	*ptr;

	ptr = *res;
	s = NULL;
	if (str[*i] == '\'')
		s = inside_squotes(str, i);
	else if (str[*i] == '"')
		s = inside_dquotes(str, i);
	*res = ft_strjoin(*res, s);
	free(ptr);
	free(s);
}

char	*remove_quotes(char *str)
{
	int		start;
	int		i;
	char	*res;
	char	*ptr;

	start = 0;
	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			rm_quotes(&res, &i, str);
		else if (str[i] == '"')
			rm_quotes(&res, &i, str);
		ptr = res;
		res = contunie_parsing(&i, str, res);
		free(ptr);
	}

	return res;
}

void	get_first_command(t_list *g_shell)
{
	int		i;
	int		start;
	int		len;
	char	*ptr;
	char	*str;

	i = skip_spaces(0, g_shell->buffer);
	str = g_shell->buffer;
	len = ft_strlen(g_shell->buffer);
	start = i;
	while (g_shell->buffer[i] != ' ' && g_shell->buffer[i] != '\t'
		&& g_shell->buffer[i] != '\0')
	{
		while (g_shell->buffer[i] == '\'' || g_shell->buffer[i] == '"')
			i = skip_quotes(i + 1, g_shell->buffer[i], g_shell->buffer);
		if (g_shell->buffer[i] != ' ')
			i++;
	}
	
	g_shell->f_cmd = ft_substr(g_shell->buffer, start, i - start);
	
	ptr = g_shell->f_cmd;
	
	g_shell->f_cmd = remove_quotes(g_shell->f_cmd);
	g_shell->buffer = ft_substr(g_shell->buffer, i, len - i);
	free(ptr);
	free(str);
	
}

void	get_first_command_pipe(t_list *g_shell, int c)
{
	int	i;
	int	start;
	int	len;

	i = skip_spaces(0, g_shell->tab[c]);
	len = ft_strlen(g_shell->tab[c]);
	start = i;
	while (g_shell->tab[c][i] != ' ' && g_shell->tab[c][i] != '\t'
			&& g_shell->tab[c][i] != '\0')
	{
		while (g_shell->tab[c][i] == '\'' || g_shell->tab[c][i] == '"')
			i = skip_quotes(i + 1, g_shell->tab[c][i], g_shell->tab[c]);
		if (g_shell->tab[c][i] != ' ')
			i++;
	}
	g_shell->f_cmd = ft_substr(g_shell->tab[c], start, i - start);
	g_shell->f_cmd = remove_quotes(g_shell->f_cmd);
	g_shell->tab[c] = ft_substr(g_shell->tab[c], i, len - i);
}
