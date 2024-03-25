#!/bin/sh
#contaB.sh
#file comandi ricorsivo che torna il numero totale di file 
#contati fino a quel punto
conta=0
#la variabile conta e' una variabile locale ad ogni sottoshell

cd $1	#ci spostiamo nella directory in cui dobbiamo fare la ricerca per questa invocazione

for i in *	#per tutti i file/dir
do
	if test -f $i	#se e' un file, dato che dobbiamo SOLO contare i file!
	then 	
		conta=`expr $conta + 1`		#incrementiamo la variabile di shell
	fi
done

#passiamo ora alla parte ricorsiva
for i in *
do
	if test -d $i -a -x $i
	then
		contaB.sh `pwd`/$i
		conta=`expr $conta + $?` 	#aggiorniamo conta sommandoli il conteggio risultante dalla sotto-gerarchia esplorata!
	fi
done

echo in `pwd` conta = $conta
exit $conta	#ritorniamo il valore di conta corrente
