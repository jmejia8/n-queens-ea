# N-Queens

Resuelve el problema de las N-reynas usando un algoritmo genético.

## Compilar y Ejecutar

Para compliar:
```
gcc main.c -o main
```

Correr ejecutable:

```
./main
```
e ingresar datos solicitado.

Para entradas por defecto (1000 individuos de la población, 1000 iteraciones y 0.1 de probabilidad para la matación).

```
./main < input
```

## Ejemplo de Salida

```
$ ./main

Population size: 1000
Iteration: 1000
Mutation rate (0, 1): 0.1
=========================
 - - - - Q - - Q
 - - Q - - - - -
 Q - - - - - - -
 - - Q - - - - -
 - - - - - - - -
 - Q - - - - - -
 - - - - - - Q -
 - - - - Q - - -
>>>>> 6
=========================
 - - - - - - - Q
 - - Q - - - - -
 Q - - - - - - -
 - - Q - - - - -
 - - - - - - Q -
 - Q - - - - - -
 - - - - - - Q -
 - - - - Q - - -
>>>>> 4
=============================
	 Solution
	 iter: 29
=============================
=========================
 - - - - - - - Q
 - - - Q - - - -
 Q - - - - - - -
 - - Q - - - - -
 - - - - - Q - -
 - Q - - - - - -
 - - - - - - Q -
 - - - - Q - - -
>>>>> 0
```
