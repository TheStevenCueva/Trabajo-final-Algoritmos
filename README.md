# Trabajo-final-Algoritmos
Se adjunta en el repositorio los diagramas y el video de ejecucion

EJERCICIO 2 Usar la comunicación BCast

long RECTAS = 20000000;

  double mid, height, width, area;

  double sum = 0.0;

  width = 1.0 / (double) RECTAS;

  for (long i = 0; i < RECTAS; i++) {

  mid = (i + 0.5) * width;

  height = 4.0 / (1.0 + mid * mid);

  sum += height;

  }

  area = width * sum; 

  PRINT("Resultado = %f", area);

  }

EJERCICIO 3: generar un archivo de 20000 con numeros aleatorios y sumarlo, se debe usar algun metodo de ordenamiento. Ádemas se debe usar cualquier método de comunicación
