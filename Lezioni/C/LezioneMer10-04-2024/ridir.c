#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define PERM 0644   /* in ottale per diritti UNIX */

int main (int argc, char** argv)
{    int infile, outfile, nread;	/* usati per open e valore ritorno read */
     char buffer[BUFSIZ];  		/* usato per i caratteri, letti dal file sorgente e scritti sul file destinazione */

	if (argc != 3)  /* controllo sul numero di parametri: devono essere esattamente 2! */
     	{ 	printf("Errore: numero di argomenti sbagliato dato che argc = %d\n", argc);
       		printf("Ci vogliono 2 argomenti: nome-file-sorgente e nome-file-destinazione\n");
       		exit(1); 
	}

	close(0);	/* vogliamo "simulare" le operazioni compiute dal S.O. per implementare la ridirezione, quindi per prima cosa facciamo una close dello standard input e quindi di 0! */ 
	if ((infile = open(argv[1], O_RDONLY)) < 0) 
	/* ERRORE se non si riesce ad aprire in LETTURA il primo file */
	{       printf("Errore in apertura file per %s dato che infile = %d\n", argv[1], infile);
		exit(2);
	}
	/* se la open ha successo viene occupato l'elemento di posto 0 della TFA del processo corrente e quindi il primo file verra' usato come standard input */

	close(1);	/* continuando la nostra "simulazione" delle operazioni compiute dal S.O. per implementare la ridirezione, dobbiamo ora passare a fare la close dello standard output e quindi di 1! */
	if ((outfile = creat(argv[2], PERM)) < 0 )
	/* ERRORE se non si riesce a creare il secondo file */
	{       /* questa volta non si puo' usare la printf perche' abbiamo CHIUSO lo standard output e quindi possiamo solo fare la exit - printf("Errore nella creazione file per %s dato che outfile = %d\n", argv[2], outfile); */
		exit(3);
	}
	/* se la creat ha successo viene occupato l'elemento di posto 1 della TFA del processo corrente e quindi il secondo file verra' usato come standard output */

	while ((nread = read(infile, buffer, BUFSIZ)) > 0 )	/* ciclo di lettura fino a che nread e' maggiore di 0 */
	{ 
		if (write(outfile, buffer, nread) < nread)	/* scriviamo sempre nread byte! */
		/* ERRORE se non si riesce a SCRIVERE */
		{       /* IDEM - printf("Errore nella scrittura del file per %s\n", argv[2]); */
			exit(4);
		}
	}	
	/* N.B. infile vale 0 e outfile vale 1 e quindi abbiamo implementato "a mano" la ridirezione */
	exit(0);
}
