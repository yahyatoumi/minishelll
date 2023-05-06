#include "minishell.h"

static	int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static	int	get_word(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static	char	*ft_word(char const *str, char c)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = get_word(str, c);
	word = (char *)malloc(len + 1);
	if (!word)
		return (0);
	while (str[i] && i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

void	ft_split2(char **strings, char const *s, char c, int leak)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
		s++;
		if (*s && *s != c)
		{
			strings[i] = ft_word(s, c);
			if (!strings[i])
			{
				while (i >= 0)
					free(strings[i--]);
				leak = 1;
				free(strings);
				return ;
			}
			i++;
			s++;
		}
		while (*s && *s != c)
		s++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**strings;
	int		leak;

	if (!s)
		return (0);
	i = 0;
	leak = 0;
	strings = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strings)
		return (0);
	ft_split2(strings, s, c, leak);
	if (leak)
		return (0);
	strings[count_words(s, c)] = 0;
	return (strings);
}
