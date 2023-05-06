#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	str = (char *)malloc(ft_strlen(s1) + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
