#include "minishell.h"

int ft_pwd()
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "getcwd Err!/n", ft_strlen("getcwd Err!/n"));
		return 1;
	}
	printf("%s\n", getcwd(NULL, 0));
	return 0;
}

t_token *ft_newtok(char *word_start, int *j)
{
	int len;
	t_token *token;
	int i;
	int x;
	int single_quote_lock;
	int double_quotes_lock;
	char holder[1000];

	len = 0;
	i = 0;
	single_quote_lock = 0;
	double_quotes_lock = 0;
	while (word_start[i] == ' ')
		i++;
	x = 0;
	while (word_start[i])
	{
		if (double_quotes_lock && word_start[i] == '\'')
			holder[x++] = word_start[i];
		else if (single_quote_lock && word_start[i] == '"')
			holder[x++] = word_start[i];
		else if (!double_quotes_lock && word_start[i] == '"')
			double_quotes_lock = 1;
		else if (!single_quote_lock && word_start[i] == '\'')
			single_quote_lock = 1;
		else if (double_quotes_lock && word_start[i] == '"')
			double_quotes_lock = 0;
		else if (single_quote_lock && word_start[i] == '\'')
			single_quote_lock = 0;
		else if (!single_quote_lock && !double_quotes_lock && word_start[i] == ' ')
			break;
		else
			holder[x++] = word_start[i];
		i++;
	}
	while (word_start[i] == ' ')
		i++;
	if (double_quotes_lock)
		holder[x++] = '"';
	if (single_quote_lock)
		holder[x++] = '\'';
	holder[x] = 0;
	*j = *j + i;
	token = (t_token *)malloc(sizeof(*token));
	if (!token)
		return 0;
	printf("----allocated hoho\n");
	token->token_chars = ft_strdup(holder);
	token->next = NULL;
	return (token);
}

void ft_addback(t_token **head, t_token *new)
{
	t_token *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

// int cmds_counter(char **cmds)
// {
// 	int i;

// 	i = 0;
// 	while (cmds[i])
// 	{
// 		// printf("%s****\n", cmds[i]);
// 		i++;
// 	}
// 	return i;
// }

// char *update_word(char *word, int new_word_len)
// {
// 	int i;
// 	int j;
// 	char *new_word;
// 	int single_quote_lock;
// 	int double_quotes_lock;

// 	i = 0;
// 	j = 0;
// 	new_word = (char *)malloc(new_word_len + 1);
// 	if (!new_word)
// 		return 0;
// 	single_quote_lock = 0;
// 	double_quotes_lock = 0;
// 	while (word[i])
// 	{
// 		if (double_quotes_lock && word[i] == '\'')
// 			new_word[j++] = word[i];
// 		else if (single_quote_lock && word[i] == '"')
// 			new_word[j++] = word[i];
// 		else if (!double_quotes_lock && word[i] == '"')
// 			double_quotes_lock = 1;
// 		else if (!single_quote_lock && word[i] == '\'')
// 			single_quote_lock = 1;
// 		else if (double_quotes_lock && word[i] == '"')
// 			double_quotes_lock = 0;
// 		else if (single_quote_lock && word[i] == '\'')
// 			single_quote_lock = 0;
// 		else
// 			new_word[j++] = word[i];
// 		i++;
// 	}
// 	new_word[j] = 0;
// 	free(word);
// 	printf("here word == %s\n", new_word);
// 	return (new_word);
// }

// int check_quotes(char *word, char *new_word)
// {
// 	int i;
// 	int single_quote_lock;
// 	int double_quotes_lock;
// 	char *word_holder;
// 	int new_word_len;

// 	i = 0;
// 	single_quote_lock = 0;
// 	double_quotes_lock = 0;
// 	new_word_len = 0;
// 	while (word[i])
// 	{
// 		if (double_quotes_lock && word[i] == '\'')
// 			new_word_len++;
// 		else if (single_quote_lock && word[i] == '"')
// 			new_word_len++;
// 		else if (!double_quotes_lock && word[i] == '"')
// 			double_quotes_lock = 1;
// 		else if (!single_quote_lock && word[i] == '\'')
// 			single_quote_lock = 1;
// 		else if (double_quotes_lock && word[i] == '"')
// 			double_quotes_lock = 0;
// 		else if (single_quote_lock && word[i] == '\'')
// 			single_quote_lock = 0;
// 		else
// 			new_word_len++;
// 		i++;
// 	}
// 	if (double_quotes_lock || single_quote_lock)
// 	{
// 		printf("single %i | double %i\n", single_quote_lock, double_quotes_lock);
// 		return (1);
// 	}
// 	word_holder = word;
// 	new_word = update_word(word, new_word_len);
// 	return 0;
// }

void to_lower_case(char *word)
{
	int i;

	i = 0;
	while (word[i])
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
			word[i] += 32;
		i++;
	}
}

int ft_execution(t_cmd *commands)
{
	t_token *head;
	int i;

	i = 0;
	while (commands)
	{
		head = commands->head_token->next;
		to_lower_case(head->token_chars);
		printf("cmd ============= %s\n", commands->head_token->token_chars);
		while (head)
		{
			printf("will do --%s--\n", head->token_chars);
			head = head->next;
		}
		commands = commands->next;
	}
	return 0;
}

void ft_addbackcmd(t_cmd **head, t_cmd *new)
{
	t_cmd *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_cmd *ft_newcmd(char *head_token)
{
	t_cmd *new_cmd;
	int will_not_use;

	new_cmd = (t_cmd *)malloc(sizeof(*new_cmd));
	if (!new_cmd)
		return (0);
	printf("----allocated hehe\n");
	new_cmd->head_token = ft_newtok(head_token, &will_not_use);
	new_cmd->next = NULL;
	return (new_cmd);
}

void replace_char(char *str, char c1, char c2)
{
	int i;
	int double_quotes_lock;
	int single_quote_lock;

	i = 0;
	double_quotes_lock = 0;
	single_quote_lock = 0;
	while (str[i])
	{
		if (!double_quotes_lock && str[i] == '"')
			double_quotes_lock = 1;
		else if (!single_quote_lock && str[i] == '\'')
			single_quote_lock = 1;
		else if (double_quotes_lock && str[i] == '"')
			double_quotes_lock = 0;
		else if (single_quote_lock && str[i] == '\'')
			single_quote_lock = 0;
		else if (!double_quotes_lock && !single_quote_lock && str[i] == c1)
			str[i] = c2;
		i++;
	}
}

void _free(t_cmd *cmds, char *input, char **splitted)
{
	t_token *t_holder;
	t_cmd *c_holder;
	int i;

	while (cmds)
	{
		printf("hehe\n");
		c_holder = cmds->next;
		while (cmds->head_token)
		{
			printf("hoho\n");
			t_holder = cmds->head_token->next;
			free(cmds->head_token->token_chars);
			free(cmds->head_token);
			cmds->head_token = t_holder;
		}
		free(cmds);
		cmds = c_holder;
	}
	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
	free(input);
}

int ft_lstsize(t_cmd *cmd)
{
	int i;
	t_cmd *tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return i;
}

int ft_lstsize2(t_token *token)
{
	int i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return i;
}

t_final_args *ft_argnew(t_cmd *commands)
{
	t_final_args *final_args;
	t_cmd *tmp_cmd;
	t_token *tmp_token;
	int i;
	int j;

	final_args = (t_final_args *)malloc(sizeof(t_final_args) * ft_lstsize(commands));
	if (!final_args)
		return 0;
	tmp_cmd = commands;
	i = 0;
	while (tmp_cmd)
	{
		final_args[i].args_first_token = tmp_cmd->head_token->next->token_chars;
		printf("first == %s\n", final_args[i].args_first_token);
		final_args[i].args = (char **)malloc(sizeof(char *) * ft_lstsize2(tmp_cmd->head_token->next->next));
		tmp_token = tmp_cmd->head_token->next->next;
		j = 0;
		while (tmp_token)
		{
			final_args[i].args[j] = tmp_token->token_chars;
			printf("will do == %s\n", final_args[i].args[j]);
			j++;
			tmp_token = tmp_token->next;
		}
		final_args[i].args[j] = 0;
		i++;
		tmp_cmd = tmp_cmd->next;
	}
	final_args[i] = NULL;
	return final_args;
}

void ft_what_will_do(t_final_args *final_args)
{
	int i;
	int j;

	i = 0;
	while (final_args[i].args_first_token)
	{
		printf("firs token : %s\n", final_args[i].args_first_token);
		j = 0;
		while (final_args[i].args[j])
		{
			printf("will do %s \n", final_args[i].args[j]);
			j++;
		}
		i++;
	}
}

int main()
{
	char *input;
	char **splited_cmds;
	int i;
	int j;
	t_cmd *commands;
	t_cmd *cmd_head_holder;
	t_final_args *final_args;

	// printf("%i\n", getpid());
	while (1)
	{
		input = readline("-> promt ");
		replace_char(input, '|', 11);
		splited_cmds = ft_split(input, 11);
		commands = NULL;
		i = 0;
		while (splited_cmds[i])
		{
			j = 0;
			ft_addbackcmd(&commands, ft_newcmd("ignored_first"));
			while (commands->next)
				commands = commands->next;
			if (i == 0)
				cmd_head_holder = commands;
			while (splited_cmds[i][j])
				ft_addback(&commands->head_token, ft_newtok(splited_cmds[i] + j, &j));
			i++;
		}
		i = 0;
		commands = cmd_head_holder;
		// ft_line_up(commands);
		// ft_execution(cmd_head_holder);
		final_args = ft_argnew(commands);
		printf("-----------------\n");
		ft_what_will_do(final_args);
		_free(cmd_head_holder, input, splited_cmds);
	}
}
