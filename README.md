# Philo
Un proyecto para iniciarse en el mundo de los hilos
# Project tree

```c
.
├── Makefile
├── include
│   └── philosophers.h
├── objs
│   ├── args.o
│   ├── init.o
│   ├── main.o
│   ├── monitor.o
│   ├── philos.o
│   └── states.o
├── philo
└── src
    ├── args.c
    ├── init.c
    ├── main.c
    ├── monitor.c
    ├── philos.c
    └── states.c
```

# Project Basics

Es fundamental para hacer este proyecto saber [cómo trabajar con hilos](https://github.com/erivero-p/42-Tutorials/tree/master/Threads).

Entendiendo esto, sabremos que cada filósofo deberá ser un hilo, y cada tenedor será un mutex. Los básicos requeridos del programa serán que los filósofos deben imprimir por pantalla cada uno de sus estados (pensar, comer, dormir), así como cada vez que cojan un tenedor, necesitarán dos tenedores para comer, y si pasan demasiado tiempo sin comer, morirán.

En términos generales, nuestro programa seguirá cuatro grandes pasos:

1) Chequear que los argumentos estén correctos
2) Inicializar las estructuras y los mutex
3) Poner a trabajar a los hilos y monitorearlos
4) Limpiar y cerrar

## Chequeo de argumentos

El número de argumentos `ac` deberá ser 5 ó 6.

Todos los argumentos deberán ser enteros y positivos, de lo contrario el programa deberá cerrarse.

## Iniciadores

Una vez chequeados los argumentos, deberemos guardar la información que contienen en la estructura. 

También deberemos haber alojado memoria para ciertas variables y, en especial, los mutex.

En mi caso utilizo tres tipos de estructura: 

- Una general con la información que afecta a todos los filósofos
- Una con mutex que van a evitar los data races
- Una para contener la información relativa a cada filósofo

Una vez iniciados los mutex que serán los tenedores, podremos asignar a cada filósofo su tenedor izquierdo y derecho, teniendo en cuenta que se sientan en círculo.

## Hilos

En mi caso, además de crear un hilo para cada filósofo, creo, para cada uno, un hilo extra que monitoreará si el filósofo sigue vivo. Además, si el programa recibe un quinto argumento con el número de comidas que deben hacer los filósofos, crearé un hilo más, que hará que el programa pare cuando todos los filósofos hayan comido.

### Rutina de los filósofos

La rutina de los filósofos debrerá:

- Inicializar en el momento actual el `last_meal` del filósofo
- Crear y esperar al hilo que monitorizará la muerte
- Poner al filósofo a pensar
- Poner al filósofo a comer:
    - Tomar ambos tenedores
    - Comer durante el tiempo requerido
    - Actualizar el tiempo del `last_meal`
    - Actualizar el número de comidas que ha hecho ese filósofo
    - Soltar los tenedores
- Poner al filósofo a dormir

## Limpieza y cierre

A la hora de cerrar y liberar memoria, habrá que tener en cuenta que también deberemos destruir todos los mutex que hayamos creado.

Antes de finalizar el proyecto, además de checkear que no haya leaks de memoria, deberemos comprobar que no haya data races, con la flag `-fsanitize=thread -g3`
