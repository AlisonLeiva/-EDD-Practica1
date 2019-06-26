#include "nodo.h"

Nodo::Nodo(struct user nuevo){
user = nuevo;
siguiente = NULL;
 }


Nodo::Nodo(){

}


struct user Nodo::getuser(){
    return user;
}
