#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define PERM 0644		/* in ottale per diritti UNIX */

int main (int argc, char **argv)
{ 
	int fd; /* usiamo una sola variabile, tanto non ci serve agire contemporaneamente sui diversi file */

	/* passiamo un solo parametro che ci servira' per identificare se e' la prima volta che invochiamo questo programma */
	if (argc != 2) 	/* controllo sul numero di parametri: deve essere esattamente 1! */
	{       printf("Errore: numero di argomenti sbagliato dato che argc = %d\n", argc);
	        printf("Ci vuole 1 argomento: la stringa prima o seconda (in realta' qualunque altra stringa non uguale a prima!)\n");
		exit(1);
	}

	if ( (fd = open ("pippo", O_CREAT | O_WRONLY, PERM)) < 0 )
	/* apertura in creazione */
	{       printf("Errore in creazione file pippo\n");
		exit(1);
	}  
	/* se siamo qui siamo riusciti a creare il file pippo e lo diciamo all'utente */
	printf("Creato il file pippo\n");
	/* scriviamo nel file appena creato distinguendo se e' la prima volta o la seconda volta che invochiamo il programma */
	if (strcmp(argv[1], "prima") == 0)
		write(fd, "questa e' la prima volta che scriviamo sul file\n", 48);
	else 
		write(fd, "seconda volta che scriviamo su file\n", 36);

	if ( (fd = open ("paperino", O_CREAT | O_EXCL | O_WRONLY, PERM)) < 0 )
	/* apertura in creazione solo se NON esiste */
		printf("Il file paperino esiste\n");
	else 
	{
		printf("Il file paperino non esisteva: creato\n");
		write(fd, "questa e' la prima volta che scriviamo sul file\n", 48);
	}

	if ( (fd= open ("paperina", O_TRUNC | O_WRONLY)) < 0 )
	/* apertura distruggendo il contenuto precedente */
	{ 
		printf("Il file paperina non esiste\n");
		exit(2);
	}  

	/* se siamo qui il file paperina esisteva e abbiamo troncato il suo contenuto e lo diciamo all'utente */
	printf("Il file paperina esisteva: troncato\n");
	if (strcmp(argv[1], "prima") == 0)
		write(fd, "questa e' la prima volta che scriviamo sul file\n", 48);
	else 
		write(fd, "seconda volta che scriviamo su file\n", 36);

	exit(0);
}
