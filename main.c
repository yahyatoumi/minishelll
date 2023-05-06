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

t_token *ft_newtok(char *word_start)
{
	int len;
	t_token *token;
	char *token_chars;
	int i;
	int j;
	int single_quote_lock;
	int double_quotes_lock;

	len = 0;
	i = 0;
	single_quote_lock = 0;
	double_quotes_lock = 0;
	while (word_start[i] == ' ')
		i++;
	if (word_start[i] == '"')
	{
		i++;
		while ((word_start[len + i] && word_start[len + i] != '"' && word_start[len + i + 1] != '"') || !word_start[len + i + 1])
			len++;
	}
	if (word_start[i] == '\'')
	{
		i++;
		while (word_start[len + i] && word_start[len + i] != '\'' && word_start[len + i + 1] != '\'')
			len++;
	}
	printf("len == %i\n", len);
	token_chars = (char *)malloc(len + 1);
	if (!token_chars)
		return 0;
	j = 0;
	while (j < len)
	{
		token_chars[j] = word_start[j + i];
		// printf("%c\n", word_start[j + i]);
		j++;
	}
	token_chars[j] = 0;
	// printf("str ==%s\n", token_chars);
	token = (t_token *)malloc(sizeof(*token));
	if (!token)
		return 0;
	token->token_chars = token_chars;
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

int cmds_counter(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		// printf("%s****\n", cmds[i]);
		i++;
	}
	return i;
}

char *update_word(char *word, int new_word_len)
{
	int i;
	int j;
	char *new_word;
	int single_quote_lock;
	int double_quotes_lock;

	i = 0;
	j = 0;
	new_word = (char *)malloc(new_word_len + 1);
	if (!new_word)
		return 0;
	single_quote_lock = 0;
	double_quotes_lock = 0;
	while (word[i])
	{
		if (double_quotes_lock && word[i] == '\'')
			new_word[j++] = word[i];
		else if (single_quote_lock && word[i] == '"')
			new_word[j++] = word[i];
		else if (!double_quotes_lock && word[i] == '"')
			double_quotes_lock = 1;
		else if (!single_quote_lock && word[i] == '\'')
			single_quote_lock = 1;
		else if (double_quotes_lock && word[i] == '"')
			double_quotes_lock = 0;
		else if (single_quote_lock && word[i] == '\'')
			single_quote_lock = 0;
		else
			new_word[j++] = word[i];
		i++;
	}
	new_word[j] = 0;
	printf("here word == %s\n", new_word);
	return (new_word);
}

int check_quotes(char *word, char *new_word)
{
	int i;
	int single_quote_lock;
	int double_quotes_lock;
	char *word_holder;
	// char *new_word;
	int new_word_len;

	i = 0;
	single_quote_lock = 0;
	double_quotes_lock = 0;
	new_word_len = 0;
	printf("started with %s\n", word);
	while (word[i])
	{
		if (double_quotes_lock && word[i] == '\'')
			new_word_len++;
		else if (single_quote_lock && word[i] == '"')
			new_word_len++;
		else if (!double_quotes_lock && word[i] == '"')
			double_quotes_lock = 1;
		else if (!single_quote_lock && word[i] == '\'')
			single_quote_lock = 1;
		else if (double_quotes_lock && word[i] == '"')
			double_quotes_lock = 0;
		else if (single_quote_lock && word[i] == '\'')
			single_quote_lock = 0;
		else
			new_word_len++;
		i++;
	}
	if (double_quotes_lock || single_quote_lock)
	{
		printf("single %i | double %i\n", single_quote_lock, double_quotes_lock);
		return (1);
	}
	printf("well done!\n");
	printf("new_wordlen== %i\n", new_word_len);
	word_holder = word;
	new_word = update_word(word, new_word_len);
	// free(word);
	printf("new word ==== %s\n", new_word);
	return 0;
}

int ft_execution(t_cmd *commands)
{
	t_token *head;
	int i;

	i = 0;
	while (commands)
	{
		head = commands->head_token;
		printf("cmd ============= %s\n", commands->head_token->token_chars);
		while (head)
		{
			check_quotes(head->token_chars, head->token_chars_updated);
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

	new_cmd = (t_cmd *)malloc(sizeof(*new_cmd));
	if (!new_cmd)
		return (0);
	new_cmd->head_token = ft_newtok(head_token);
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

int main()
{
	// char *input;
	// char **splited_cmds;
	// int i;
	// int j;
	// t_cmd *commands;
	t_token *tmp_token;
	// t_cmd *cmd_head_holder;

	tmp_token = ft_newtok("      \"echo xx\"");
	printf("%s\n", tmp_token->token_chars);
	// printf("%i\n", getpid());
	// commands = ft_newcmd("  hello bb");
	// printf("***%s\n", commands->head_token->token_chars);
	// while (1)
	// {
	// 	input = readline("-> promt ");
	// 	replace_char(input, '|', 11);
	// 	splited_cmds = ft_split(input, 11);
	// 	printf("sssss%s\n", input);
	// 	commands = (t_cmd *)malloc(sizeof(t_cmd));
	// 	if (!commands)
	// 		return 0;
	// 	commands = NULL;
	// 	i = 0;
	// 	while (splited_cmds[i])
	// 	{
	// 		j = 0;
	// 		printf("splited %s\n", splited_cmds[i]);
	// 		ft_addbackcmd(&commands, ft_newcmd("ignored_first"));
	// 		if (i == 0)
	// 			cmd_head_holder = commands;
	// 		while (splited_cmds[i][j])
	// 		{
	// 			ft_addback(&commands->head_token, ft_newtok(splited_cmds[i] + j));
	// 			while (splited_cmds[i][j] == ' ')
	// 				j++;
	// 			while (splited_cmds[i][j] != ' ' && splited_cmds[i][j])
	// 				j++;
	// 			while (splited_cmds[i][j] == ' ')
	// 				j++;
	// 		}
	// 		commands = commands->next;
	// 		i++;
	// 	}
	// 	i = 0;
	// 	commands = cmd_head_holder;
	// 	ft_execution(cmd_head_holder);
	// }
}
