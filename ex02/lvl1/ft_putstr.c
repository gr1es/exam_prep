
#include <unistd.h>

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int main(int argc, char const *argv[])
{
	ft_putstr("\n\n  bing bong \t\t\t\t let's go\n lul\n\n");
	return 0;
}

