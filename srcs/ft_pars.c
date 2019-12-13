#include "../includes/libftprintf.h"

int	pars_nb(char *str)
{
        int     i;
        int     j;

        i = 0;
        j = 0;
        while (str[i] && !(str[i] >= '1' && str[i] <= '9') && str[i] != '*' && !is_conversion(str[i]))
        {
                j = i +1;
                if (str[i + 1] && str[i] == '.' && !(str[i + 1] >= '0' && str[i + 1] <= '9'))
                        return (0);
                while (str[j] && !(str[j] >= '1' && str[j] <= '9') && str[j] != '*' && !is_conversion(str[i]))
                {
                        if (str[i] == str[j] ||
                        (((str[i] == ' ' || str[i] == '+') && (str[j] == ' ' || str[j] == '+'))
                         || ((str[i] == '-' || str[i] == '0') && (str[j] == '-' || str[j] == '0'))
                         || ((str[i] == '.' || str[i] == '0') && (str[j] == '.' || str[j] == '0'))))
                                return (0);
                        j++;
                }
                i++;
        }
        return (1);

}

int	pars_str(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && !is_conversion(str[i]))
	{
		if ((str[i] == '0' && str[i - 1] == '%') || str[i] == '+' || str[i] == ' ')
			return (0);
		if (str[i] == '-')
			count++;
		i++;
	}
	if (count > 1)
		return(0);
	return (1);
}

int	pars_char(char *str)
{
	int     i;
        int     count;

        i = 0;
        count = 0;
        while (str[i] && !is_conversion(str[i]))
        {
                if ((str[i] == '0' && str[i - 1] == '%') || str[i] == '+' || str[i] == ' ' || str[i] == '.')
                        return (0);
                if (str[i] == '-')
                        count++;
                i++;
        }
        if (count > 1)
                return(0);
        return (1);
}
