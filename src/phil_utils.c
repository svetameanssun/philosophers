#include "../include/philosophers.h"



int	ft_isspace(int c)
{
	return ((c == ' ') || (c >= 9 && c <= 13));
}
int is_number(char *str)
{
	int i;

	i = 0;
    while(str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return(ERROR_NUMBER);
        i++;
    }
    return(0);
}


int ft_atoi(char *str)
{
    if (is_number(str) != 0)
	{
        return(ERROR_ATOI);
	}
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (ft_isspace(str[i]) != 0)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res = res + str[i] - '0';
		i++;
	}
	return (res);
}
