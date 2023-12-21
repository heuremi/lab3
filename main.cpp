#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

const double megaDouble = 999999999999999;

class Servidor{
    private:
        string id;
        string nombre;
        string tipo;
        vector<pair<Servidor*,pair<double, double>>> conexiones;
    public:
        Servidor(string id, string nombre, string tipo){
            this -> id = id;
            this -> nombre = nombre;
            this -> tipo = tipo;
        }
        string getId(){return id;}
        void setId(string id){this -> id = id;}
        string getNombre(){return nombre;}
        void setNombre(string nombre){this -> nombre = nombre;}
        string getTipo(){return tipo;}
        void setTipo(string tipo){this -> tipo = tipo;}
        vector<pair<Servidor*,pair<double, double>>> getConexiones(){ return conexiones;}
        void agregarConexion(Servidor* servidor, double velocidad, double distancia){
            conexiones.push_back(make_pair(servidor, make_pair(velocidad, distancia)));
        }
};

vector<Servidor*> leerCsv(string nombreCsv){
    vector<Servidor*> servidores;
    ifstream archivo(nombreCsv);
    if(!archivo){
        cout << "El archivo " << nombreCsv << " no pudo abrirse." << endl;
        return servidores;
    }
    string line; 

    getline(archivo, line);
    while(getline(archivo, line)){

        stringstream ss(line);
        string id, nombre, tipo;

        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, tipo, ',');

        Servidor* servidor = new Servidor(id, nombre, tipo);
        servidores.push_back(servidor);
    }
    archivo.close();
    return servidores;
};

vector<Servidor*> generarGrafo(string nombreCsv, vector<Servidor*> servidoresArchivo){
    ifstream archivo(nombreCsv);
    if(!archivo){
        cout << "El archivo " << nombreCsv << " no pudo abrirse." << endl;
        return servidoresArchivo;
    }
    string line; 
    getline(archivo, line);
    while(getline(archivo, line)){

        stringstream ss(line);
        string idCliente, idServidor, velocidad_, distancia_;

        getline(ss, idCliente, ',');
        getline(ss, idServidor, ',');
        getline(ss, velocidad_, ',');
        getline(ss, distancia_, ',');
        
        int velocidad = stoi(velocidad_);
        int distancia = stoi(distancia_);

        for (Servidor *servidor : servidoresArchivo) {
            if (servidor->getId() == idCliente) {
                for (Servidor *servidor2 : servidoresArchivo) {
                    if (servidor2->getId() == idServidor) {
                        servidor->agregarConexion(servidor2, (double) velocidad, (double) distancia);
                        servidor2->agregarConexion(servidor, (double) velocidad, (double) distancia);
                        break;
                    }
                }
                break;
            }
        }
    }
    archivo.close();
    return servidoresArchivo;
};

vector<pair<Servidor*, pair<Servidor*, double>>> bellmanFord(vector<Servidor*> servidores, Servidor* origen, Servidor* destino, double pesoMensaje) {
    int n = servidores.size();
    vector<pair<Servidor*, pair<Servidor*, double>>> distancias(n);

    // Inicialización de distancias
    for (int i = 0; i < n; i++) {
        distancias[i].first = servidores[i];
        distancias[i].second.first = origen;
        distancias[i].second.second = megaDouble;
    }
    // Implementar Bellman-Ford para calcular el tiempo
    for (int i = 0; i < n - 1; i++) {
        for (Servidor* servidorActual : servidores) {
            for (const auto& conexionActual : servidorActual->getConexiones()) {
                double tiempo = (pesoMensaje / conexionActual.second.first) * conexionActual.second.second; // Calcular tiempo
                try {
                    int idServidorActual = stoi(servidorActual->getId());
                    int idConexionActual = stoi(conexionActual.first->getId());
                    if(servidorActual == origen){
                        distancias[idServidorActual].second.second = 0;
                    }
                    if (distancias[idServidorActual].second.second < megaDouble && distancias[idServidorActual].second.second + tiempo < distancias[idConexionActual].second.second) {
                        distancias[idConexionActual].second.first = servidorActual;
                        distancias[idConexionActual].second.second = distancias[idServidorActual].second.second + tiempo;
                    }
                } catch (const std::invalid_argument& e) {
                    // Manejar el error, por ejemplo, imprimir un mensaje y salir
                    cerr << "Error: ID no válido\n";
   
                }
            }
        }
    }

    return distancias;
};

void enviarMensaje(vector<Servidor*> servidores) {
    // Obtener el servidor de origen
    string idOrigen;
    cout << "Ingrese el ID del servidor de origen: ";
    cin >> idOrigen;

    Servidor* origen = nullptr;
    for (Servidor* servidor : servidores) {
        if (servidor->getId() == idOrigen) {
            origen = servidor;
            break;
        }
    }

    if (!origen) {
        cout << "Servidor de origen no encontrado.\n";
        return;
    }
    else if(origen->getTipo() == "router"){
        cout << "El servidor origen no puede ser un router.\n";
        return;
    }

    // Obtener el servidor destino
    string idDestino;
    cout << "Ingrese el ID del servidor destino: ";
    cin >> idDestino;

    Servidor* destino = nullptr;
    for (Servidor* servidor : servidores) {
        if (servidor->getId() == idDestino) {
            destino = servidor;
            break;
        }
    }

    if (!destino) {
        cout << "Servidor destino no encontrado.\n";
        return;
    }
    else if(destino->getTipo() == "router"){
        cout << "El servidor destino no puede ser un router.\n";
        return;
    }

    // Obtener el peso del mensaje
    double pesoMensaje;
    cout << "Ingrese el peso del mensaje (en MB): ";
    cin >> pesoMensaje;

    // Calcular la ruta y tiempos utilizando Bellman-Ford
    vector<pair<Servidor*, pair<Servidor*, double>>> distancias = bellmanFord(servidores, origen, destino, pesoMensaje);

    // Mostrar la ruta y los tiempos
    for(int i = 0; i < distancias.size(); i++){
        if(distancias[i].first->getId() == destino->getId()){
            if(distancias[i].second.first == origen){
                cout << "No fue posible enviar el mensaje.\n";
            }
            cout << "Ultimo servidor: " << distancias[i].second.first->getId() << ", tiempo total: " << distancias[i].second.second << endl;
            return;
        }
    }

};

void menu(vector<Servidor*> servidores){
    string opcion;
    cout << "\n------ Menu ------\n";
    cout << "\n1) Ver servidores.\n";
    cout << "2) Enviar mensaje.\n";
    cout << "3) Salir.\n";
    cout << "\nSeleccione una opcion: ";
    cin >> opcion;
    cout << '\n';

    if(opcion == "1"){
        for(Servidor *servidor : servidores){
            cout << "Id: " << servidor->getId() << ", Nombre: " << servidor->getNombre() << ", Tipo: "<< servidor->getTipo() << '\n';
            cout << "Conexiones:\n";
            if(servidor->getConexiones().empty()){
                cout << "- El servidor no tiene conexiones\n";
            }
            else {
                for(pair<Servidor*, pair<int,int>> conexiones : servidor->getConexiones()){
                cout << "- " << conexiones.first->getNombre() << ", Velocidad: "<< conexiones.second.first << ", Distancias: " << conexiones.second.second << '\n';
                }
            }
            cout << '\n';
        }
        menu(servidores);
    } 
    else if(opcion == "2"){
        enviarMensaje(servidores);
        menu(servidores);
    }
    else if(opcion == "3"){
        cout << "Hasta luego\n";
        return;
    }
    else {
        cout << "Opcion invalida\n";
        menu(servidores);
    }
};

int main() {
    vector<Servidor*> servidores = generarGrafo("conexiones.csv", leerCsv("servidores.csv"));
    menu(servidores);
    return 0;
}
