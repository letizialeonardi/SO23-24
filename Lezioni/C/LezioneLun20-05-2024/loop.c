#include <stdio.h>

/* ricordarsi di usare questo programma usando la ridirezione dello standard output su /dev/null */

int main()
{
	printf("SONO UN PROGRAMMA CHE VA IN LOOP\n");
	while (1)
		printf("Sono nel ciclo\n");
}
