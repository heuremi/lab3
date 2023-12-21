#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

class Servidor{
    private:
        string id;
        string nombre;
        string tipo;
        vector<pair<Servidor*,pair<int,int>>> conexiones;
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
        vector<pair<Servidor*,pair<int, int>>> getConexiones(){ return conexiones;}
        void agregarConexion(Servidor* servidor, int velocidad, int distancia){
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
                        servidor->agregarConexion(servidor2, velocidad, distancia);
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

void bellmanFord(vector<Servidor*> servidores, Servidor* origen){
    vector<pair<Servidor*, pair<Servidor*,int>>> distancias;
    for(Servidor* servidor : servidores){
        if(servidor == origen){
            distancias.push_back(make_pair(origen, make_pair(origen, 0)));
        } else {
            int max = numeric_limits<int>::max();
            distancias.push_back(make_pair(servidor, make_pair(origen, max)));
        }
    }
};

void menu(vector<Servidor*> servidores){
    string opcion;
    cout << "\n\tMenu\n";
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
                cout << "- " << conexiones.first->getNombre() << ", Velocidad: "<< conexiones.second.first << ", Distance: " << conexiones.second.second << '\n';
                }
            }
            cout << '\n';
        }
        menu(servidores);
    } 
    else if(opcion == "2"){
        cout << "Aun no implementado\n";
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
