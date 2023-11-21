# Bash Scripts desarrollados para la práctica:

Todas estas heramientas de deben ejecutar desde la carpeta raiz del proyecto, no desde su carpeta, en concreto para pruebas_rendimiento.sh

Si se quieren ejecutar en local estos scripts, es necesario poner como último parámetro "local"

## 1. [**`Compilador`**](compila.sh)
Automatiza la compilación de un programa en C++ utilizando multiples cores para compilarse
```bash
sbatch compila
```

## 2. [**`Ejecutar`**](ejecuta.sh)
Toma dos parámetros de entrada, el numero de veces que se quiere ejecutar el test y el segundo es el número de iteraciones
```bash
sbatch ejecuta.sh <repeticiones> <iteracines>
```

## 3. [**`Pruebas de Rendimiento`**](pruebas_rendimiento.sh)
Realiza las pruebas de rendimiento para sacar las salidas para iteraciones 100 y de 500 a 10.000 iteraciones, con intervalos de 500
```bash
./pruebas_rendimiento.sh
```

## 4. [**`Traducir trz a txt`**](en_claro_salidas.sh)
Traduce las salidas del programa a un formato más legible para el usuario
```bash
./en_claro_salidas.sh <directorio_con_trz> 
```