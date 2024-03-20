#!/bin/sh
#file comandi con primo esempio di case
#chiediamo all'utente di fornire una risposta
echo -n 'Fornire una risposta (affermativa ===> Si, si, Yes, yes) '	#usiamo l'opzione -n per fare in modo che l'echo NON iserisca l'a-capo; N.B. abbiamo inserito un carattere spazio per maggiore leggibilita'!
#leggiamo la risposta dell'utente
read risposta
#verifichiamo con un case la risposta dell'utente
case $risposta in
S* | s* | Y* | y*) echo OK;;
*)		   echo NO;;
esac
