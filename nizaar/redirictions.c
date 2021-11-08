/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:53:41 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 18:53:42 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_redr(t_list *g_shell, char **ptr, int *start, int i)
{
	char	*str;
	char	*p;

	p = *ptr;
	str = ft_substr(g_shell->buffer, *start, i - *start);
	*ptr = ft_strjoin(*ptr, str);
	free(str);
	free(p);
	i = i + 2;
	while (g_shell->buffer[i] == ' ' && g_shell->buffer[i])
		i++;
	g_shell->g_red_start = i;
	i = ft_remove_quotes_file(g_shell->buffer, i, g_shell);
	g_shell->g_fd = open(g_shell->g_red_buff, O_APPEND
			| O_RDONLY | O_WRONLY | O_CREAT, 0777);
	init_var(&i, start, g_shell, 1);
	return (i);
}

int	single_redr(t_list *g_shell, char **ptr, int *start, int i)
{
	char	*str;
	char	*p;

	p = *ptr;
	str = ft_substr(g_shell->buffer, *start, i - *start);
	*ptr = ft_strjoin(*ptr, str);
	free(str);
	free(p);
	i++;
	while (g_shell->buffer[i] == ' ' && g_shell->buffer[i])
		i++;
	g_shell->g_red_start = i;
	i = ft_remove_quotes_file(g_shell->buffer, i, g_shell);
	g_shell->g_fd = open(g_shell->g_red_buff,
			O_TRUNC | O_WRONLY | O_CREAT, 0777);
	init_var(&i, start, g_shell, 1);
	return (i);
}

int	check_readrd(t_list *g_shell, char **ptr, int *start, int i)
{
	char	*str;
	char	*p;

	p = *ptr;
	str = ft_substr(g_shell->buffer, *start, i - *start);
	*ptr = ft_strjoin(*ptr, str);
	free(str);
	free(p);
	i = i + 1;
	while (g_shell->buffer[i] == ' ' && g_shell->buffer[i])
		i++;
	g_shell->g_red_start = i;
	i = ft_remove_quotes_file(g_shell->buffer, i, g_shell);
	if (open(g_shell->g_red_buff, O_RDONLY, 0777) == -1)
	{
		printf("No such file or directory \n");
		close(g_shell->g_fd);
		g_shell->g_read = -1;
	}
	else
	{
		g_shell->g_fd = open(g_shell->g_red_buff, O_RDONLY, 0777);
		init_var(&i, start, g_shell, 0);
	}
	return (i);
}

int	found_redr(char **ptr, int *start, int i, int flag)
{
	while (g_shell->buffer[i])
	{
		if (is_quote(g_shell->buffer[i]) && flag == 0)
			flag = 1;
		else if (is_quote(g_shell->buffer[i]) && flag == 1)
			flag = 0;
		else
		{
			while (g_shell->buffer[i] == '>'
				&& g_shell->buffer[i + 1] != '\0' && flag == 0)
			{
				if (g_shell->buffer[i] == '>' && g_shell->buffer[i + 1] == '>')
					i = double_redr(g_shell, ptr, start, i);
				if (g_shell->buffer[i] == '>' && g_shell->buffer[i + 1] != '>')
					i = single_redr(g_shell, ptr, start, i);
			}
			while (g_shell->buffer[i] == '<'
				&& flag == 0 && g_shell->buffer[i + 1] != '\0')
				i = check_readrd(g_shell, ptr, start, i);
		}
		if (g_shell->buffer[i] != '\0')
		i++;
	}
	return (i);
}

void	ft_check_redr(t_list *g_shell)
{
	int		i;
	int		start;
	char	*str;
	char	*ptr;

	i = 0;
	start = 0;
	ptr = ft_strdup("");
	g_shell->g_red_buff = ft_strdup("");
	i = found_redr(&ptr, &start, i, 0);
	str = ptr;
	finalise(ptr, i, start);
	free(str);
}
