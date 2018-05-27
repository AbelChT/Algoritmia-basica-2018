#!/bin/bash
# Autores: Abel Chils Trabanco (NIA:718997) y Jorge Aznar López (NIA:721556)
# Descripción: Genera $NUMERO_DE_PRUEBAS pruebas aleatorias (no las ejecuta
# solamente genera los sistemas de nodos)
NUMERO_DE_PRUEBAS=2
i=0
while [ $i -lt $NUMERO_DE_PRUEBAS ]
do
echo "Generando prueba $i ...."
./GeneradorPruebas "node_system$i.txt" "correct_output$i.txt"
i=$[$i+1]
done
