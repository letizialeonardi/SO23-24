#!/bin/sh
echo SONO DIRCTL2.sh
case $# in	#controlliamo con un case i vari casi
0) echo non sono stati passati parametri
   echo DEBUG-eseguo 'ls -l' paginato nella directory corrente
   ls -l | more
   exit 0;;	#in questo caso abbiamo terminato il compito assegnato e quindi per uscire con successo usiamo exit 0
1) echo passato un parametro $1;;
*) echo Errore: voglio o zero oppure un parametro, mentre ne hai passati $#
   exit 1;;
esac
#se arriviamo qui siamo sicuri che sia stato passato un singolo parametro
echo '$0 ===>' $0	#queste due stampe vanno sempre fatte
echo '$1 ===>' $1	#e quindi conviene non replicarle per i due singoli casi!
if test -f $1	#controlliamo se e' un file
then 	echo $1 file
	echo "DEBUG-Ora eseguo ls -l $1"
	ls -l $1
else
	if test -d $1	#controlliamo se e' una directory
	then	echo $1 directory
		echo "DEBUG-Ora eseguo ls -ld $1"
		ls -ld $1
	else	#altrimenti non esiste
		echo $1 non file o non directory
	fi
fi
