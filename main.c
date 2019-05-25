#include<stdio.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>
#include "includes/printf.h"
int main(int argc, char const *argv[])
{
	printf("%d\n",ft_printf("%t|\n", time(NULL)));
		return 0;
}
