# Laboratorio 3

## Integrantes:
Constanza Vázquez
María Victoria Quiroga

## Funciones del main:
vector<Servidor*> leerCsv(string nombreCsv): Lee el archivo de servidores, crea y agrega estos servidores a la lista con todos los servidores.
vector<Servidor*> generarGrafo(string nombreCsv, vector<Servidor*> servidoresArchivo): Crea un grafo a partir de las conexiones de los servidores.
void enviarMensaje(vector<Servidor*> servidores): Pide al usuario ingresar el servidor de origen, el servidor de destino y el tamaño del mensaje, y en base a esto se intenta mandar el mensaje.
void menu(vector<Servidor*> servidores): Se le pregunta al usuario si desea ver todos los servidores, enviar un mensaje o salir.

## Explicación del algoritmo Bellman Ford:
vector<pair<Servidor*, pair<Servidor*, double>>> bellmanFord(vector<Servidor*> servidores, Servidor* origen, Servidor* destino, double pesoMensaje):
•	Inicialización de distancias: Se crea un vector distancias con tripletes inicializados con cada servidor, el servidor de origen como previo, y un valor inicial de tiempo (inicializado a un valor grande megaDouble).
•	Se realiza un bucle principal que itera n - 1 veces, donde n es el número de servidores en la red. Esto garantiza que el algoritmo explore todos los posibles caminos más cortos.
•	El bucle “for (Servidor* servidorActual : servidores)” itera sobre cada servidor en la red en cada iteración del bucle externo. Esto significa que en cada paso, el algoritmo considera todos los servidores como posibles nodos intermedios en los caminos más cortos.
•	El bucle “for (const auto& conexionActual : servidorActual->getConexiones())” itera sobre todas las conexiones del servidor actual, calculando el tiempo de transmisión para cada conexión y compara las distancias para cada una, si se encuentra un camino más corto se actualiza.
