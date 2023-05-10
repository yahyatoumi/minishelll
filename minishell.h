#ifndef MINI_SHELL
#define MINI_SHELL

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_token
{
	char *token_chars;
	struct s_token *next;
}			t_token;

typedef struct s_cmd
{
	t_token *head_token;
	struct s_cmd *next;
}			t_cmd;

typedef struct s_final_args
{
	char	**args;
	char	**arrows_n_files;
}			t_final_args;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char const *s1);

#endif
