/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:40:46 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/06 18:49:39 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_if_infile(t_data *g_data, char *start, t_env *envp)
{
	if (*start == '<' && (g_data->cmd_lst->bcomillas == 0
			|| g_data->cmd_lst->bcomillas2 == 0))
	{
		if (g_data->cmd_lst->infile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 1)
			ft_error(2, g_data, envp);
		g_data->cmd_lst->infile_tag = 1;
		start++;
		if (*start == '<')
		{
			g_data->cmd_lst->infile_tag = 2;
			g_data->herecount++;
			start++;
		}
		start--;
	}
	return (start);
}

char	*ft_if_outfile(t_data *g_data, char *start, t_env *envp)
{
	if (*start == '>' && (g_data->cmd_lst->bcomillas == 0
			|| g_data->cmd_lst->bcomillas2 == 0))
	{
		if (g_data->cmd_lst->infile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 1)
			ft_error(3, g_data, envp);
		g_data->cmd_lst->outfile_tag = 1;
		start++;
		if (*start == '>')
		{
			g_data->cmd_lst->outfile_tag = 2;
			start++;
		}
		start--;
	}
	return (start);
}

char	*skip_delimiters2(char *start, t_data *g_data)
{
	const char	delimiters[] = "<|>";

	if (*start == '\\' && (g_data->cmd_lst->bcomillas == 0
			|| g_data->cmd_lst->bcomillas2 == 0))
	{
		start++;
		if (ft_strchr(delimiters, *start) == NULL)
			g_data->cmd_lst->bjoin = 0;
		else
			g_data->cmd_lst->bjoin = 1;
	}
	if (*start != '\0')
		start++;
	return (start);
}

char	*skip_delimiters(char *start, t_data *g_data, t_env *envp)
{
	const char	delimiters[] = "<|>";
	int			ntokens;

	ntokens = 0;
	while (*start != '\0' && ft_strchr(delimiters, *start) != NULL)
	{
		if (*start == '|' )
		{
			if (g_data->cmd_lst->previous == 0
				|| g_data->cmd_lst->infile_tag == 1
				|| ntokens > 0 || g_data->cmd_lst->outfile_tag == 1)
				ft_error(1, g_data, envp);
			ntokens++;
		}
		if (*start == '"')
			check_marks(g_data, 0);
		if (*start == '\'')
			check_marks(g_data, 1);
		start = ft_if_infile(g_data, start, envp);
		start = ft_if_outfile(g_data, start, envp);
		start = skip_delimiters2(start, g_data);
		start = skip_spaces(start);
	}
	start = skip_spaces(start);
	return (start);
}

char	*skip_spaces(char *start)
{
	while (*start == ' ')
		start++;
	return (start);
}
