#!/bin/bash
#Genera una pruebas aleatoria
NUMERO_DE_PRUEBAS=10
i=0
while [ $i -lt $NUMERO_DE_PRUEBAS ]
do
echo "Generando prueba $i ...."
./GeneradorPruebas "node_system$i.txt" "correct_output$i.txt"
i=$[$i+1]
done

