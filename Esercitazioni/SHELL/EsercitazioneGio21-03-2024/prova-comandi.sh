#!/bin/sh
#File prova-comandi.sh
echo Nome assoluto del file p.txt: `pwd`/p.txt
echo -n 'Directory corrente '	#N.B. L'opzione -n serve per non andare a capo; abbiamo usato le singole virgolette per inserire lo spazio alla fine per non avere la stampa della dir corrente attaccata
pwd
echo -n "DEBUG-Directory corrente "	#facciamo la prova anche con le doppie virgolette che servono allo stesso scopo indicato sopra
pwd
