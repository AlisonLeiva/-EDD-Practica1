#include "cola.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <iostream>
using namespace std;

//-----------------------------------------  COLA      ---------------------------------------

NodoCola::NodoCola(int id){
    this->id = id;
    this->siguiente = NULL;
}

NodoCola::NodoCola(int id, int carreta){
    this->id = id;
    this->carreta = carreta;
    this->siguiente = NULL;
}

Cola::Cola(){
    this->inicio  = NULL;
}

void Cola::EncolarCliente(int id, int carreta){
    NodoCola *nuevo = new NodoCola(id, carreta);
    if (inicio == NULL) {
        inicio = nuevo;
    }
    if (!Existe(id)) {
        NodoCola *aux = inicio;
        while (aux != NULL) {
            if (aux->siguiente == NULL) {
                aux->siguiente =nuevo;
                break;
            }
            aux = aux->siguiente;
        }
    }
}



NodoCola Cola::Buscar(int id){
    NodoCola *aux = inicio;
    while(aux!=NULL){
        if(aux->id == id){
            return *aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

bool Cola::Existe(int id){
    NodoCola *aux = inicio;
    while(aux!=NULL){
        if(aux->id == id){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

int Cola::Size(){
    NodoCola *aux = inicio;
    int i =0;
     while(aux!=NULL){
         i++;
         aux = aux->siguiente;
     }
     return i;
}


NodoCola *Cola::Desencolar(){
    if (inicio != NULL) {
        NodoCola *actual = inicio;
        inicio = inicio->siguiente;
        return actual;
    }
}


void Cola::Mostrar(){
    NodoCola *aux = inicio;
     while(aux!=NULL){
         cout<<aux->id<<endl;
         aux = aux->siguiente;
     }
}
QString Cola::Subgraph(QString nombre, QString color)
{
   QString texto ="";
   if(Size()!=0){
       NodoCola *aux = inicio;
         texto = " subgraph "+ nombre+ "{ \n rankdir=TB; ranksep = 1; size = \"10,10\";"+
                     "node [shape = record, style=filled,fontname=\"Calibri Light\", fillcolor=\"#"+color+"\" penwidth =0 width = 1.5];";

           while(aux!=NULL)
           {
               if(aux->carreta==0){
                   texto += nombre + QString::number(aux->id)+" [label =\"Cliente " + QString::number(aux->id)+"\"]; \n";
               }else{
                   texto += nombre + QString::number(aux->id)+" [label =\"Cliente " + QString::number(aux->id)+" \\n Carreta: "+QString::number(aux->carreta) +"\"]; \n";
                  }
                aux = aux->siguiente;
           }

           aux = inicio;
           while(aux->siguiente!=NULL)
           {
               texto +=nombre+QString::number(aux->id) + "->";
                aux = aux->siguiente;
                texto +=nombre+ QString::number(aux->id) +"; \n";
           }
           texto+="}";
   }
     return texto;
}


