#!/bin/sh
#file comandi crea.sh
case $# in
0) 	echo Errore nel numero di parametri: $# non numero giusto di parametri!
	exit 1;;          #usciamo 
*)	echo Sono stati forniti i seguenti parametri: $*;;
esac
echo Verranno creati nella directory corrente i file, vuoti, aventi come nome quelli specificati come parametri
for i 	#for per tutti i parametri
do
	> $i 	#con la ridirezione nulla si crea un file vuoto
done
