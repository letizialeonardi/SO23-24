#!/bin/sh
#file comandi trova-file.sh 
case $# in 							#controlliamo che sia invocato con un solo parametro: usato un case perche' e' piu' versatile!
1) echo DEBUG-OK un solo parametro $1 ;;			#caso giusto!
*) echo echo $# non numero giusto di parametri! Uso: $0 file	#casi NON giusti!
   exit 1;;
esac
#controllo che il primo parametro sia dato in forma relativa semplice 
case $1 in
*/*) echo Errore: $1 non in forma relativa semplice 		#notare che questa forma di controllo ingloba anche il caso /*
     exit 2;;
*) ;;
esac
if test -f $1 	#controlliamo che sia un file
then
	echo -n 'DEBUG-il file $1 esiste e si trova in '	#stampa aggiunta, ma non richiesta; N.B. Uso di -n e singole virgolette
	pwd
	echo il suo nome assoluto e\' `pwd`/$1			#UNICA STAMPA RICHIESTA
else 	echo -n 'DEBUG-non esiste un file di nome $1 in ' 	#stampa aggiunta, ma non richiesta; IDEM come sopra!
	pwd
fi
