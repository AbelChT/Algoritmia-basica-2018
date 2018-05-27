#! /usr/bin/env bash
# Autores: Abel Chils Trabanco (NIA:718997) y Jorge Aznar López (NIA:721556)
# Descripción: Ejecuta los algoritmos pertenecientes a los 3 criterios y comprueba
# que su resultado haya sido correcto sobre $NUMERO_DE_PRUEBAS vectores de enteros
# generados de forma aleatoria. En caso de que estos se hayan ejecutado correctamente,
# muestra el tiempo medio de ejecución de cada uno en nanosegundos. En caso contrario
# muestra un mensaje de error.
NUMERO_DE_PRUEBAS=10

# Tamaño del vector a ordenar
VECTOR_SIZE=10000

i=1

mediatmp=0
media1=0
media2=0
media3=0

while [ $i -le $NUMERO_DE_PRUEBAS ]
do
	echo "Iteracion numero: $i"
	echo "Generando el vector a ordenar..."
	./GeneradorVectores $VECTOR_SIZE

	echo "Lanzando algoritmos en orden creciente..."

	mediatmp=$(./Quicksort | cut -d ' ' -f 6)
	media1=`expr $media1 + $mediatmp`

	if [ ./TestVectores ]; then
		echo "[SUCCESS]"
	else
		echo "[ERROR]: Criterio 1 ha fallado"
		exit 1
	fi

	mediatmp=$(./Quicksort_2 | cut -d ' ' -f 6)
	media2=`expr $media2 + $mediatmp`

	if [ ./TestVectores ]; then
		echo "[SUCCESS]"
	else
		echo "[ERROR]: Criterio 2 ha fallado"
		exit 1
	fi

	mediatmp=$(./Quicksort_3 | cut -d ' ' -f 6)
	media3=`expr $media3 + $mediatmp`

	if [ ./TestVectores ]; then
		echo "[SUCCESS]"
		echo " "
	else
		echo "[ERROR]: Criterio 3 ha fallado"
		exit 1
	fi

	i=`expr $i + 1`
done

media1=`expr $media1 / $NUMERO_DE_PRUEBAS`
media2=`expr $media2 / $NUMERO_DE_PRUEBAS`
media3=`expr $media3 / $NUMERO_DE_PRUEBAS`

echo "Coste medio en nanosegundos del algoritmo 1: $media1"
echo "Coste medio en nanosegundos del algoritmo 2: $media2"
echo "Coste medio en nanosegundos del algoritmo 3: $media3"
