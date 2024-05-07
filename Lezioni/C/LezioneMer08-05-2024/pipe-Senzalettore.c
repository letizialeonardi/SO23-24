/* FILE: pipe-Senzalettore.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MSGSIZE 5 

int main (int argc, char **argv)
{   int pid, j, piped[2];                   /* pid per fork, j per indice, piped per pipe */
    char mess[MSGSIZE];                     /* array usato dal figlio per inviare stringa al padre */

	if (argc != 2)
	{   	printf("Numero dei parametri errato %d: ci vuole un singolo parametro\n", argc);
    		exit(1);
	}

	/* si crea una pipe: si DEVE sempre controllare che la creazione abbia successo! */
	if (pipe(piped) < 0 )
	{   	printf("Errore creazione pipe\n");
    		exit(2);
	}

	/* si crea un figlio (controllando sempre!) */
	if ((pid = fork()) < 0)
	{   	printf("Errore creazione figlio\n");
    		exit(3);
	}
	if (pid == 0)
	{   
		/* figlio */
	   int fd;	/* variabile presente solo nello stack del figlio; va bene anche definirla nel main */
		close(piped[0]); 	/* il figlio CHIUDE il lato di lettura: sara' quindi lo SCRITTORE della pipe */
		if ((fd = open(argv[1], O_RDONLY)) < 0)
		{   	printf("Errore in apertura file %s\n", argv[1]);
            		exit(-1); /* torniamo al padre un -1 che sara' interpretato come 255 e quindi identificato come errore */
		}
		sleep(5); 	/* inseriamo questa sleep cosi' da essere sicuri che quando il figlio tentera' di scrivere, il padre sia gia' morto ed inoltre per provare ad eseguire il comando ps -lf! */
		printf("DEBUG-Figlio %d sta per iniziare a scrivere una serie di messaggi, ognuno di lunghezza %d, sulla pipe dopo averli letti dal file passato come parametro\n", getpid(), MSGSIZE);
		j=0; /* il figlio inizializza la sua variabile j per contare i messaggi che mandera’ al padre */
		while (read(fd, mess, MSGSIZE)) /* il contenuto del file e' tale che in mess ci saranno 4 caratteri e il terminatore di linea */
		{
    			/* il padre ha concordato con il figlio che gli mandera' solo stringhe e quindi dobbiamo sostituire il terminatore di linea con il terminatore di stringa */
    			mess[MSGSIZE-1]='\0';
    			write(piped[1], mess, MSGSIZE);
    			j++;
		}
		printf("DEBUG-Figlio %d scritto %d messaggi sulla pipe\n", getpid(), j);
                exit(j);        /* figlio deve tornare al padre il numero di linee lette che corrispondono al numero di stringhe mandate al padre */
	}

	/* padre */
	close(piped[1]); /* il padre CHIUDE il lato di scrittura: sara' quindi il LETTORE della pipe  */		
	printf("DEBUG-Padre %d sta per iniziare a leggere i messaggi dalla pipe\n", getpid());
	j =0; /* il padre inizializza la sua variabile j per verificare quanti messaggi ha mandato il figlio */
	/* termina subito ===> PIPE SENZA PIU'LETTORE */
	/* BISOGNA FARE IN MODO CHE IL PADRE TERMINI PRIMA DEL FIGLIO E QUINDI BISOGNA ELIMINARE LA PARTE DOVE IL PADRE ASPETTEREBBE IL FIGLIO quindi padre NON aspetta il figlio */	
	exit(0);
}
