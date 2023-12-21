# Laboratorio 3 - Estructura de datos

## Integrantes:
Constanza Vázquez

María Victoria Quiroga

## Funciones del main:
vector<Servidor*> leerCsv(string nombreCsv): Lee el archivo de servidores, crea y agrega estos servidores a la lista general de servidores.

vector<Servidor*> generarGrafo(string nombreCsv, vector<Servidor*> servidoresArchivo): Crea un grafo a partir de las conexiones de los servidores.

void enviarMensaje(vector<Servidor*> servidores): Pide al usuario ingresar el servidor de origen, el servidor de destino y el tamaño del mensaje, y en base a esto se intenta mandar el mensaje.

void menu(vector<Servidor*> servidores): Se le pregunta al usuario si desea ver todos los servidores, enviar un mensaje o salir.

## Explicación del algoritmo Bellman Ford:

•	El primer ciclo for sirve para inicializar todas las distancias desde el servidor en la posición i hasta el origen como un valor muy grande (megadouble).

•	Se realiza un bucle principal que itera n - 1 veces, donde n es el número de servidores en la red. Esto garantiza que el algoritmo explore todos los posibles caminos más cortos.

•	El siguiente ciclo for “for (Servidor* servidorActual : servidores)” itera sobre cada servidor. Esto significa que en cada paso, el algoritmo considera todos los servidores como posibles nodos intermedios en los caminos más cortos.

•	El bucle “for (const auto& conexionActual : servidorActual->getConexiones())” itera sobre todas las conexiones del servidor actual, calculando el tiempo de transmisión del mensaje para cada conexión y quednadose con el que sea menor.

## Comandos para iniciar el codigo desde la terminal
g++ -o main main.cpp
./main
