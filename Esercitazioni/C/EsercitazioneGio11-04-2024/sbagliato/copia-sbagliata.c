/* versione di copia.c in cui si deve andare via via a commentare le diretive di include: nel seq
 * uito commentata la prima */
//#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 	/* per poter usare, oltre che la primitiva close, anche read e write */
#include <fcntl.h>
#define PERM 0644   	/* in ottale per diritti UNIX */

int main (int argc, char** argv)
{    int infile, outfile, nread;	/* usati per open e valore ritorno read */
     char buffer[BUFSIZ];  		/* usato per i caratteri, letti dal file sorgente e scritti sul file destinazione */

	if (argc != 3)  /* controllo sul numero di parametri: devono essere esattamente 2! */
     	{ 	printf("Errore: numero di argomenti sbagliato dato che argc = %d\n", argc);
       		printf("Ci vogliono 2 argomenti: nome-file-sorgente e nome-file-destinazione\n");
       		exit(1); 
	}

	if ((infile = open(argv[1], O_RDONLY)) < 0) 
	/* ERRORE se non si riesce ad aprire in LETTURA il primo file */
	{       printf("Errore in apertura file per %s dato che infile = %d\n", argv[1], infile);
		exit(2);
	}

	if ((outfile = creat(argv[2], PERM)) < 0 )
	/* ERRORE se non si riesce a creare il secondo file */
	{       printf("Errore nella creazione file per %s dato che outfile = %d\n", argv[2], outfile);
		exit(3);
	}

	while ((nread = read(infile, buffer, BUFSIZ)) > 0 )	/* ciclo di lettura fino a che nread e' maggiore di 0 */
	{ 
		if (write(outfile, buffer, nread) < nread)	/* scriviamo sempre nread byte! */
		/* ERRORE se non si riesce a SCRIVERE */
		{       printf("Errore nella scrittura del file per %s\n", argv[2]);
			exit(4);
		}
	}	
	/* se arriviamo qui, vuol dire che tutto e' andato bene */
	exit(0);
}
