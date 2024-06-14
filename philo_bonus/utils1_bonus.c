/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:37:35 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/13 23:11:47 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define MAX 2147483647
#define MIN -2147483648

int	ft_strlen(const char *s)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	p = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	fcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	zero(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != '0' && s[i] != ' ')
			return (1);
		i++;
	}
	if ((s[i - 1] == '-' || s[i - 1] == '+') && s[i] == '\0')
		return (1);
	return (0);
}

int	ft_atoi(char *s, int *error)
{
	int					i;
	int					sign;
	long long			n;

	i = 0;
	if (!fcmp(s, "-0") || !fcmp(s, "+0") || !fcmp(s, "0") || !zero(s))
		return (0);
	n = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			sign = -1;
	}
	while (s[i] >= '0' && s[i] <= '9')
		n = n * 10 +(s[i++] - 48);
	if (s[i] != '\0' || n == 0 || (n * sign) > MAX || (n * sign) < MIN)
		*error = 1;
	return (n * sign);
}
