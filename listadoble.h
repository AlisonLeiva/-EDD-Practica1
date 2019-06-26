#ifndef LISTADOBLE_H
#define LISTADOBLE_H
#include <QString>
#include <stdio.h>
#include <pila.h>
using namespace std;

    struct Caja{
        int id;
        bool estado;
        int cliente;
        int carreta;
        int tiempo;
        Caja *siguiente;
        Caja *anterior;
        Caja(int dato,int cliente, int carreta);

        void setEstado(bool estado);
        bool getEstado();

        void setCliente(int cliente);
        int getCliente();

        void setCarreta(int carreta);
        int getCarreta();


        void setTiempo(int tiempo);
        int getTiempo();
    };

    struct ListaDoble{
        Caja *inicio;
        Caja * fin;
        ListaDoble();
        int Size();
        bool Disponible();
        void Insertar(int dato,int cliente, int carreta);
        void Eliminar(int id);
        void Mostrar();
        void ActualizarCajas(int time, Pila *pila1, Pila *pila2);
        void BuscarDisponible(int cliente,int carreta,int tiempo);
        QString Subgraph();
    };


#endif //LISTADOBLE_H
