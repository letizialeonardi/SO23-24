#!/bin/sh
#File prova-inibizioni.sh
a=ciao 			#assegno alla variabile a la stringa ciao
#visualizziamo su standard output il valore della variabile a, della esecuzione del comando pwd e del metacarattere ASTERISCO
echo Valore della variabile a = $a, valore della dir corrente `pwd` e valore di ASTERISCO * 	
#PROCEDIAMO CON LA INIBIZIONE DI TUTTE LE SOSTITUZIONI: si devono usare le singole virgolette!
echo 'Valore della variabile a = $a, valore della dir corrente `pwd` e valore di ASTERISCO *' 	
#ORA PROCEDIAMO CON LA INIBIZIONE SOLO DELL'ULTIMA SOSTITUZIONE: si devono usare le doppie virgolette!
echo "Valore della variabile a = $a, valore della dir corrente `pwd` e valore di ASTERISCO *" 	
