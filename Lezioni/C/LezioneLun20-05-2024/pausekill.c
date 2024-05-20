/* FILE: pausekill.c  */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int ntimes = 0; /* variabile contatore globale: due copie una per ogni processo */

/* funzione che verra' invocata alla ricezione del segnale SIGUSR1 */
void handler(int signo)
{
	printf ("Processo %d ricevuto #%d volte il segnale %d\n", getpid(), ++ntimes, signo);
}

int main ()
{
   int pid, ppid;	/* pid figlio e pid padre */

   	/* agganciamo il segnale SIGUSR1 alla funzione gestore di nome handler */
	signal(SIGUSR1, handler);

	if ((pid = fork()) < 0) 
	{
		/* fork fallita */
		printf("Errore nella fork");
		exit(1); 
	}

	if (pid == 0)  /* figlio */
	{ 	
		/* l'aggancio alla specifica azione (handler) viene ereditato dal figlo */
		ppid = getppid(); 	/* PID del padre */
		for (;;) /* ciclo infinito */
		{ 
			printf("FIGLIO %d\n", getpid());
			sleep(1); 		/* per evitare deadlock */
			kill(ppid, SIGUSR1);	/* invio segnale al padre */
			pause();		/* attesa di un segnale */
		}	
	}
	else 	/* ATTENZIONE IN QUESTO CASO DOBBIAMO METTERE l'ELSE PERCHE' IL FIGLIO NON ESEGUE EXIT MA UN CICLO INFINITO */
	/* padre */
	{ 
		for(;;) /* ciclo infinito */
		{ 
			printf("PADRE %d\n", getpid());
			pause();		/* attesa di un segnale */
			sleep(1);		/* per evitare deadlock */
			kill(pid, SIGUSR1);	/* invio segnale al figlio */
		}
	}
	
	/* NOTA BENE: il padre NON puo' aspettare il figlio in questo caso! */
}
