#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	int		strlen;
	char	*str;

	if (!s2)
		return (0);
	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(strlen + 1);
	if (!str)
		return (0);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		str[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	str[i + ft_strlen(s1)] = 0;
	return (str);
}
