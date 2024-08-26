# include "lexer_parser.h"
# include "minishell.h"

static t_tokens	cmd_id(char *token)
{
	if (ft_strcmp(token, "echo") == 0 ||
		ft_strcmp(token, "exit") == 0 ||
		ft_strcmp(token, "pwd") == 0 ||
		ft_strcmp(token, "cd") == 0 ||
		ft_strcmp(token, "unset") == 0 ||
		ft_strcmp(token, "env") == 0 ||
		ft_strcmp(token, "export") == 0)
	{
		return (T_CMD);
	}
	return (T_ARG);
}

void	add_tk_cmd_check(char *str, t_tools *tools)
{
	t_tokens	token_type;

	token_type = cmd_id(str);
	add_tk(&(tools->lexer_lst), make_tk(str, token_type));
}

void	label_cmds(t_tools *tools)
{
	t_lexer	*curr;

	if (tools->lexer_lst == NULL)
		return ;
	curr = tools->lexer_lst;
	while (curr)
	{
		if (curr->token == T_ARG)
			curr->token = cmd_id(curr->str);
		curr = curr->next;
	}
}

void	process_tokens(t_tools *tools)
{
	t_lexer	*curr;

	if (tools->lexer_lst == NULL)
		return ;
	curr = tools->lexer_lst;
	while (curr != NULL)
	{
		if (curr->token == T_REDIR_IN || curr->token == T_REDIR_OUT || 
			curr->token == T_APPEND || curr->token == T_HEREDOC)
		{
			tools->p_redir = curr;
			tools->redir_num++;
			if (curr->token == T_HEREDOC)
				tools->heredoc = true;
		}
		else if (curr->token == T_PIPE)
			tools->pipes++;
		curr = curr->next;
	}
}

void	handle_input(t_tools *tools)
{
	if (!tokenize_input(tools))
		ft_error(ERR_LEX, tools);
	if (tools->lexer_lst != NULL)
	{
		label_cmds(tools);
		process_tokens(tools);
	}
}
