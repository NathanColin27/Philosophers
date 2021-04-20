#include <stdio.h>
#include <unistd.h>
#include <time.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void
	ft_putnbr_fd(int n, int fd)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
}

int main(void)
{
	int i = 0;
	 clock_t t;
    t = clock();
	while (i < 1000)
	{
		// ft_putnbr_fd(i, 1);
		// write(1, "\n", 1);
		printf("%d", i);
		i++;
	}
	 t = clock() - t;
	 double time_taken = ((double)t)/CLOCKS_PER_SEC;
	 printf("fun() took %f seconds to execute \n", time_taken);
}