#include "listadoble.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <iostream>
using namespace std;

//-----------------------------------------  LISTA DOBLEMENTE ENLAZADA       ---------------------------------------

Caja::Caja(int dato,int cliente, int carreta){
    this->id = dato;
    this->estado = true;
    this->tiempo = 0;
    this->cliente = cliente;
    this->carreta= carreta;
    this->siguiente = NULL;
    this->anterior = NULL;
}

void Caja::setEstado(bool e){
    estado = e;
}
void Caja::setCliente(int e){
    cliente = e;
}
void Caja::setCarreta(int e){
    carreta = e;
}

void Caja::setTiempo(int e){
    tiempo = e;
}

bool Caja::getEstado(){
    return estado;
}
int Caja::getCarreta(){
    return carreta;
}
int Caja::getCliente(){
    return cliente;
}
int Caja::getTiempo(){
    return tiempo;
}

ListaDoble::ListaDoble(){
    this->inicio = this->fin = NULL;
}

void ListaDoble::Insertar(int id, int cliente,int carreta){
    Caja *nuevo = new Caja(id,cliente,carreta);

       if(inicio == NULL){
            inicio = nuevo;
            inicio -> siguiente = NULL;
            inicio->anterior = NULL;
            fin= inicio;
        } else {
           if(id>fin->id){
               fin->siguiente = nuevo;
               nuevo->anterior = fin;
               nuevo->siguiente = NULL;
               fin = nuevo;
           }else if(id < inicio->id){
               inicio->anterior = nuevo;
               nuevo->anterior = NULL;
               nuevo->siguiente = inicio;
               inicio = nuevo;
           }else{
               Caja *aux = inicio;
               while(aux!=NULL){

                   if(id < aux->siguiente->id){
                       Caja *aux2 = aux->siguiente;
                       aux->siguiente = nuevo;
                       nuevo->anterior = aux;
                       nuevo->siguiente = aux2;
                       aux2->anterior = nuevo;
                       break;
                   }

                   aux = aux->siguiente;


               }
           }
      }
  }


bool ListaDoble::Disponible(){
    Caja *aux = inicio;
    while(aux!=NULL)
    {
        if(aux->getEstado()){
                return true;
        }
         aux = aux->siguiente;
    }
    return false;
}


void ListaDoble::BuscarDisponible(int cliente,int carreta,int tiempo){
    Caja *aux = inicio;
    while(aux!=NULL){
        if(aux->getEstado()){
            cout<<"Cliente "<< cliente<<", esta siendo atendido por Caja"<<aux->id<<endl;
             aux->setCliente(cliente);
             aux->setCarreta(carreta);
             aux->setTiempo(tiempo);
             aux->estado=false;
             return;
           }
        aux = aux->siguiente;
    }
}

int ListaDoble::Size(){
    Caja *aux = inicio;
    int i =0;
     while(aux!=NULL){
         i++;
         aux = aux->siguiente;
     }
     return i;
}

void ListaDoble::ActualizarCajas(int segundos, Pila *Pila1, Pila *Pila2){
    Caja *aux = inicio;

    while(aux!=NULL){
        int tiempo = segundos - aux->getTiempo();
        if(aux->tiempo== 0){
            aux->estado=true;
        }else if(tiempo < 60){
             aux->estado=false;
         }else if(tiempo > 60){
            cout<<"Cliente "<< aux->id<<", sale del sistema. Libera carreta "<<aux->carreta<< " y la caja "<<aux->id<<endl;
            srand(time(NULL));
            int NoPila= 1+rand()%(3-1);
            if(NoPila==1){
                  Pila1->Push(aux->carreta);
              }else if(NoPila==2){
                  Pila2->Push(aux->carreta);

            }
            aux->estado=true;
            aux->setCliente(0);
            aux->setCarreta(0);
            aux->setTiempo(0);
        }
  aux = aux->siguiente;
    }
}


void ListaDoble::Eliminar(int  u){
   Caja *aux2= NULL;
   Caja *aux = inicio;
        while((aux != NULL)){
            if(aux->id== u){
                    if(aux == inicio){
                        inicio = inicio->siguiente;
                        inicio ->anterior = NULL;
                    }else if(aux == fin){
                        fin = fin->anterior;
                        fin->siguiente = NULL;
                    }else{
                        aux2->siguiente = aux->siguiente;
                        aux->siguiente->anterior = aux->anterior;

                      }
            }
            aux2=aux;
            aux=aux->siguiente;
        }
}


void ListaDoble::Mostrar(){
    Caja *aux = inicio;
     while(aux!=NULL){
         cout<<aux->id<<endl;
         aux = aux->siguiente;
     }
}

QString ListaDoble::Subgraph()
{
QString texto="";
     if(Size()!=0){
         Caja *aux = inicio;
         texto += "\n subgraph Cajas{ \n  rankdir=LR;  \n node [shape = record, style=filled, fontname=\"Calibri Light\",fillcolor=\"#C8EBBA\" penwidth =0 width = 1.5];";

         while(aux!=NULL)
         {
             if(aux->getEstado()){
                 texto +="ClienteCaja" + QString::number(aux->id)+" [label =\" Caja " + QString::number(aux->id)+ "\\n Cliente: "+ QString::number(aux->getCliente()) +"\\n Carreta: "+QString::number(aux->getCarreta()) +" \\n Libre\"]; \n";
             }else{
                 texto +="ClienteCaja" + QString::number(aux->id)+" [label =\" Caja " + QString::number(aux->id)+ "\\n Cliente: "+ QString::number(aux->getCliente()) +"\\n Carreta: "+QString::number(aux->getCarreta()) +" \\n Ocupado\"]; \n";
             }
              aux = aux->siguiente;
         }

         aux = inicio;
         while(aux->siguiente!=NULL)
         {
             texto +="ClienteCaja" +QString::number(aux->id) + "->";
              aux = aux->siguiente;
              texto +="ClienteCaja" +QString::number(aux->id) +"; \n";
         }

         aux = fin;
         while(aux->anterior!=NULL)
         {
              texto +="ClienteCaja" + QString::number(aux->id)+ "->";
              aux = aux->anterior;
              texto +="ClienteCaja" +QString::number(aux->id)+"; \n";
         }
          texto +="}";
        //  cout << texto.toUtf8().constData() << endl;
          return texto;
     }
     return texto;
}

