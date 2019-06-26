#ifndef PILA_H
#define PILA_H
#include <QString>
#include <stdio.h>
using namespace std;

    struct NodoPila{
        int id;
        NodoPila *siguiente;
        NodoPila(int dato);
    };

    struct Pila{
        NodoPila *inicio;
        Pila();
        void Push(int id);
        NodoPila *Pop();
        void Mostrar();
        NodoPila Buscar(int id);
        int Size();
        bool estaVacia();
        QString SubgraphPila(QString nombre);
    };
#endif // PILA_H
