/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:24:49 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/08 22:18:38 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

// TODO: duplicate envp in array/list

// get_var from tools->envp/path

// append_var

char	*get_env_value(const char *var_name, t_tools *tools)
{
	t_list	*env_var;
	size_t	var_len;
	char	*env_str;

	env_var = tools->envp;
	var_len = ft_strlen(var_name);
	if (tools->debug_mode == true)
		printf("[DEBUG] Searching for env var: %s\n", var_name);
	while (env_var)
	{
		env_str = (char *)env_var->content;
		if (tools->debug_mode == true)
			printf("[DEBUG] Checking env var: %s\n", env_str);
		if (ft_strncmp(env_str, var_name, var_len) == 0
			&& env_str[var_len] == '=')
		{
			if (tools->debug_mode == true)
				printf("[DEBUG] Found env var: %s\n", env_str);
			return (env_str + var_len + 1);
		}
		env_var = env_var->next;
	}
	if (tools->debug_mode == true)
		printf("[DEBUG] Env var not found: %s\n", var_name);
	return (NULL);
}

static char	*append_char(char *str, char c)
{
	char	*temp_str;
	size_t	len;

	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	temp_str = malloc(len + 2); // Allocate memory for the new string
	if (!temp_str)
	{
		free(str);
		return (NULL);
	}
	if (str)
	{
		ft_strlcpy(temp_str, str, len + 1); // Copy the original string
		free(str);
	}
	if (len + 1 < len + 2)    // Check if we can safely append the character
		temp_str[len] = c;    // Append the new character
	temp_str[len + 1] = '\0'; // Null-terminate the new string
	return (temp_str);
}

static char	*expand_single_var(const char *s, size_t *i, t_tools *tools)
{
	size_t	var_start;
	size_t	var_end;
	char	*var_name;
	char	*var_value;

	var_start = *i + 1;
	var_end = var_start;
	while (s[var_end] && (ft_isalnum(s[var_end]) || s[var_end] == '_'))
		var_end++;
	var_name = ft_substr(s, var_start, var_end - var_start);
	var_value = get_env_value(var_name, tools);
	free(var_name);
	*i = var_end - 1;
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

char	*expand_var(const char *s, t_tools *tools)
{
	char	*result;
	char	*temp;
	char	*new_result;
	size_t	i;

	result = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && (ft_isalpha(s[i + 1]) || s[i
				+ 1] == '_'))
			temp = expand_single_var(s, &i, tools);
		else
			temp = append_char(ft_strdup(""), s[i]);
		new_result = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = new_result;
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
