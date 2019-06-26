#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H
#include <QString>
#include <stdio.h>
using namespace std;

    struct NodoCompra{
        int id;
        int carreta;
        NodoCompra *siguiente;
        NodoCompra *anterior;
        NodoCompra(int dato, int carreta);
    };

    struct ListaCircularDoble{
        NodoCompra *inicio;
        NodoCompra * fin;
        ListaCircularDoble();

        int Size();
        void Insertar(int cliente, int carreta);
        NodoCompra *Eliminar(int id);
        void Mostrar();
        NodoCompra Buscar(int id);
        QString Subgraph();
    };

#endif // LISTACIRCULARDOBLE_H
