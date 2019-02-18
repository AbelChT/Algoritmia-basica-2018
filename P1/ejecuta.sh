#!/bin/bash
# Autores: Abel Chils Trabanco (NIA:718997) y Jorge Aznar López (NIA:721556)
# Descripción: Ejecuta el algoritmo sobre $NUMERO_DE_PRUEBAS pruebas diferentes
# que han debido se ser anteriormente generadas
NUMERO_DE_PRUEBAS=2
i=0
while [ $i -lt $NUMERO_DE_PRUEBAS ]
do
echo "Generando prueba $i ...."
#Busca la solución en la prueba generada 
echo "Ejecutando algoritmo para prueba $i ...."
./Algoritmo "node_system$i.txt" "output$i.txt"

#Comprueba que la solución encontrada sea correcta
echo "Comprobando resultado para prueba $i  ...."
./ComprobadorSolucion "correct_output$i.txt" "output$i.txt"

i=$[$i+1]
done

