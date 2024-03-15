#!/bin/sh
#File prova-var-bis.sh
echo Il valore della variabile x = $x #stampo il valore della variabile x
echo Il valore della variabile y = $y #stampo il valore della variabile y
echo Il valore della variabile z = $z #stampo il valore della variabile z
z=0 #azzero il valore di z
export z		        #dato che abbiamo modificato z per compatibilita' dovremo fare di nuovo l'ezport, che pero' NON VALE INDIETRO, ma solo in AVANTI! 
echo Nuovo valore della variabile z = $z #stampo il valore aggiornato della variabile z
