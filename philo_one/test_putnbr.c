#include <stdio.h>
#include <unistd.h>
#include <time.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void reverse(char x[10], int begin, int end)
{
   char c;

   if (begin >= end)
      return;

   c          = *(x+begin);
   *(x+begin) = *(x+end);
   *(x+end)   = c;

   reverse(x, ++begin, --end);
}

void
	ft_putnbr_fd(int n, int fd)
{
	char	str[10];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if(length > 0)
		length--;
	if(length)
		reverse(str, 0, length);
	write(fd, str, length + 1);
}

int main(void)
{
	int i = 0;
	 clock_t t;
    t = clock();
	while (i < 1000000)
	{
		ft_putnbr_fd(i, 1);
		// write(1, " a random string\n", 18);
		// printf("%d %s\n", i, " a random string");
		i++;
	}
	 t = clock() - t;
	 double time_taken = ((double)t)/CLOCKS_PER_SEC;
	 printf("fun() took %f seconds to execute \n", time_taken);
}