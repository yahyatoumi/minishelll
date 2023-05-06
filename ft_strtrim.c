#include "minishell.h"

static int ft_char_in_set(char c)
{
	size_t i;

	i = 0;
	if (c == 10 || c == 9 || c == 32)
		return (1);
	i++;
	return (0);
}

char *ft_strtrim(char const *s1)
{
	char *str;
	size_t i;
	size_t start;
	size_t end;

	if (!s1)
		return (0);
	start = 0;
	while (s1[start] && ft_char_in_set(s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1]))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
