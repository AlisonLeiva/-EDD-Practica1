#ifndef COLA_H
#define COLA_H
#include <QString>
#include <stdio.h>
using namespace std;

    struct NodoCola{
        int id;
        int carreta;
        NodoCola *siguiente;
        NodoCola(int dato);
        NodoCola(int cliente, int carreta);
    };

    struct Cola{
        NodoCola *inicio;
        Cola();
        int Size();
        void EncolarCliente(int id,int carreta);
        NodoCola *Desencolar();
        void Mostrar();
        bool Existe(int id);
        NodoCola Buscar(int id);
        QString Subgraph(QString nombre, QString color) ;
    };

#endif // COLA_H
