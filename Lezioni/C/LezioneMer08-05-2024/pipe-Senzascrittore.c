/* FILE: pipe-Senzascrittore.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MSGSIZE 5 

int main (int argc, char **argv)
{       
   int pid, j, piped[2];            	/* pid per fork, j per indice, piped per pipe */
   char mess[MSGSIZE];          	/* array usato dal figlio per inviare stringa al padre e array usato dal padre per ricevere stringa inviata dal figlio */
   int pidFiglio, status, ritorno; 	/* per wait padre */

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
		close(piped[0]); 	/* il figlio CHIUDE il lato di lettura : sara' quindi lo SCRITTORE della pipe */
		if ((fd = open(argv[1], O_RDONLY)) < 0)	/* apriamo il file */
		{   	printf("Errore in apertura file %s\n", argv[1]);
            		exit(-1); /* torniamo al padre un -1 che sara' interpretato come 255 e quindi identificato come errore */
		}

		printf("DEBUG-Figlio %d sta per iniziare a scrivere una serie di messaggi, ognuno di lunghezza %d, sulla pipe dopo averli letti dal file passato come parametro\n", getpid(), MSGSIZE);
                j=0; /* il figlio inizializza la sua variabile j per contare i messaggi che mandera' al padre */
		/* IL FIGLIO TERMINA ===> PIPE SENZA SCRITTORE */
		exit(j);
	}

	/* padre */
	close(piped[1]); /* il padre CHIUDE il lato di scrittura: sara' quindi il LETTORE della pipe */		
	printf("DEBUG-Padre %d sta per iniziare a leggere i messaggi dalla pipe\n", getpid());
	j =0; /* il padre inizializza la sua variabile j per verificare quanti messaggi ha mandato il figlio*/
	while (read(piped[0], mess, MSGSIZE)) /* questo ciclo avra' termine appena il figlio terminera' dato che la read senza piu' scrittore tornera' 0! IN QUESTO ESEMPIO QUINDI TERMINERA' SUBITO! */ 
    	{ 	
        	/* dato che il figlio gli ha inviato delle stringhe, il padre le puo' scrivere direttamente con una printf */
        	printf("%d: %s\n", j, mess);
        	j++;
     	}
	if (j != 0) 
		printf("DEBUG-Padre %d letto %d messaggi dalla pipe\n", getpid(), j);
	else 
	{ 	printf("NON C'E' SCRITTORE dato che non ho ricevuto alcun messaggio\n"); 
		/* padre aspetta il figlio */
		if ((pidFiglio=wait(&status)) < 0)
		{
      			printf("Errore wait\n");
      			exit(4);
		}
		if ((status & 0xFF) != 0)
        		printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
		else
		{
       			ritorno=(int)((status >> 8) & 0xFF);
       			printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
		}
		exit(5);	/* il padre termina segnalando un errore dovuto al fatto che il figlio NON gli ha inviato stringhe! */ 
	}

	exit(0); /* in questo caso NON si arriverra' mai a questa istruzione! */
}
