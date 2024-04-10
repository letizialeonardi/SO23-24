#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define PERM 0644   /* in ottale per diritti UNIX */

int main (int argc, char** argv)
{    int infile, outfile, nread;	/* usati per open e valore ritorno read */
     char buffer[BUFSIZ];  		/* usato per i caratteri, letti dal file sorgente e scritti sul file destinazione */
     int fd; /* per file/dispositivo /dev/tty */
     char sErroreCreat[]= "Errore nella creazione file\n";
     char sErroreWrite[]= "Errore nella scrittura del file\n";
     char s[100] = "Valore di infile ";	/* stringa usata nella funzione sprintf */
     char s1[5];			/* stringa per infile e poi outfile */
     char s2[] = " e di outfile ";	/* stringa ulteriore */
     char s3[] = "\n";			/* stringa conclusiva */

	if (argc != 3)  /* controllo sul numero di parametri: devono essere esattamente 2! */
     	{ 	printf("Errore: numero di argomenti sbagliato dato che argc = %d\n", argc);
       		printf("Ci vogliono 2 argomenti: nome-file-sorgente e nome-file-destinazione\n");
       		exit(1); 
	}

	if ((fd = open("/dev/tty", O_WRONLY)) < 0) 
	/* ERRORE se non si riesce ad aprire in SCRITTURA il dispositivo */
	{       printf("Errore in apertura file per %s dato che fd = %d\n", "/dev/tty", fd);
		exit(2);
	}

	close(0);	/* vogliamo "simulare" le operazioni compiute dal S.O. per implementare la ridirezione, quindi per prima cosa facciamo una close dello standard input e quindi di 0! */ 
	if ((infile = open(argv[1], O_RDONLY)) < 0) 
	/* ERRORE se non si riesce ad aprire in LETTURA il primo file */
	{       printf("Errore in apertura file per %s dato che infile = %d\n", argv[1], infile);
		exit(3);
	}
	/* se la open ha successo viene occupato l'elemento di posto 0 della TFA del processo corrente e quindi il primo file verra' usato come standard input */

	close(1);	/* continuando la nostra "simulazione" delle operazioni compiute dal S.O. per implementare la ridirezione, dobbiamo ora passare a fare la close dello standard output e quindi di 1! */
	if ((outfile = creat(argv[2], PERM)) < 0 )
	/* ERRORE se non si riesce a creare il secondo file */
	{ 	write(fd, sErroreCreat, strlen(sErroreCreat));	/* ora scriviamo su fd e quindi su /dev/tty */
		exit(4);
	}
	/* se la creat ha successo viene occupato l'elemento di posto 1 della TFA del processo corrente e quindi il secondo file verra' usato come standard output */
	/* STAMPA DI DEBUGGER */
	sprintf(s1, "%d", infile);	/* ricaviamo la stringa corrispondente a infile */
	strcat(s, s1);			/* la concateniamo alla stringa s */
	strcat(s, s2);			/* quindi conteniamo s2 */
	sprintf(s1, "%d", outfile);	/* ricaviamo la stringa corrispondente a outfile */
	strcat(s, s1);			/* la concateniamo alla stringa s */
	strcat(s, s3);			/* quindi conteniamo s3 */
	write(fd, s, strlen(s));	/* ora scriviamo su fd e quindi su /dev/tty */

	while ((nread = read(infile, buffer, BUFSIZ)) > 0 )	/* ciclo di lettura fino a che nread e' maggiore di 0 */
	{ 
		if (write(outfile, buffer, nread) < nread)	/* scriviamo sempre nread byte! */
		/* ERRORE se non si riesce a SCRIVERE */
		{ 	write(fd, sErroreWrite, strlen(sErroreWrite));	/* ora scriviamo su fd e quindi su /dev/tty */
			exit(5);
		}
	}	
	/* N.B. infile vale 0 e outfile vale 1 e quindi abbiamo implementato "a mano" la ridirezione */
	exit(0);
}
