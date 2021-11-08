/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rest_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:49:22 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 20:49:24 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*surrond_with_quotes(char *ptr, char c)
{
	if (c == '"')
	{
		ptr = ft_strjoin(ft_strdup("\""), ptr);
		ptr = ft_strjoin(ptr, ft_strdup("\""));
	}
	return (ptr);
}

char	*remove_spaces_frquotes(char *str, int *i, char c)
{
	int		start;
	char	*ptr;
	int		flag;
	int		flag_2;

	start = *i + 1;
	flag = 0;
	flag_2 = 0;
	ptr = ft_strdup("");
	*i = *i + 1;
	while (str[*i] != c && str[*i])
		*i = *i + 1;
	ptr = ft_strjoin(ptr, ft_substr(str, start, *i - start));
	*i = *i + 1;
	ptr = split_and_join(ptr);
	ptr = surrond_with_quotes(ptr, c);
	return (ptr);
}

char	*parse_export(t_list *g_shell)
{
	int		i;
	char	*ptr;
	int		start;

	i = 0;
	ptr = ft_strdup("");
	while (g_shell->rest[i] != '\0')
	{
		if (g_shell->rest[i] == '"')
			ptr = ft_strjoin(ptr,
					remove_spaces_frquotes(g_shell->rest, &i, '"'));
		start = i;
		while (g_shell->rest[i] != '\0' && g_shell->rest[i] != '"')
			i++;
		ptr = ft_strjoin(ptr, ft_substr(g_shell->rest, start, i - start));
	}
	return (ptr);
}

void	get_rest_command_exp(t_list *g_shell)
{
	int		i;
	int		len;
	char	*s;

	i = skip_spaces(0, g_shell->buffer);
	len = ft_strlen(g_shell->buffer);
	s = ft_substr(g_shell->buffer, i, len - i);
	if (ft_strcmp(s, ""))
	{
		g_shell->rest = s;
		g_shell->rest = remove_spaces(g_shell);
	}
	else
		g_shell->rest = ft_strdup("");
	free(s);
}

void	get_rest(t_list *g_shell)
{
	if (ft_strcmp(g_shell->f_cmd, "export"))
		get_rest_command(g_shell);
	else
		get_rest_command_exp(g_shell);
}
