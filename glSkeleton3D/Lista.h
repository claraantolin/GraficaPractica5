//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef ListaH
#define ListaH

#include <iostream>
#include <fstream>

using namespace std;

template<class T> class Lista;

   template<class T>
class Nodo{

        friend class Lista<T>;
        private:
                T info;
                Nodo<T>* sig;
                Nodo<T>* ant;

        public:
                Nodo(){info=NULL;sig=NULL;ant=NULL;};
                Nodo(T i){info=i;sig=NULL;ant=NULL;};

                ~Nodo(){delete info;info=NULL;};

                };


template <class T>

class Lista
{
   private:

      Nodo<T>* primero;
      Nodo<T>* ultimo;
      int elem;

   public:

 // ------CONSTRUCTORA----------------------
      Lista(){elem=0; primero=NULL; ultimo=NULL;};
 //----------DESTRUCTORA---------------
      ~Lista()
      {
      Nodo<T>* aux;

      while(elem>0)
         {
            aux=primero;
            primero=primero->sig;
            if(primero!=NULL){primero->ant=NULL;}
            aux->sig=NULL;
            delete aux;
            elem--;
         }
         ultimo=NULL;
      };
  //---------NUM_ELEM----------------
      int numElem(){return elem;};
  //---------IESIMO--------------------
      T iesimo(int n)
      {
         Nodo<T>* aux;
         aux=primero;
         while((aux!=NULL) && n>0)
         {
             n--;
             aux=aux->sig;
         }

         return aux->info;
      };

  //--------PON_ELEM----------------
      bool ponElem(const T& e)
      {
         if(primero==NULL)
         {
                primero= new Nodo<T>(e);
                ultimo=primero;
                elem ++;
                return true;
         }
         else{
                Nodo<T>* nuevoNodo = new Nodo<T>(e);
                ultimo->sig=nuevoNodo;
                nuevoNodo->ant=ultimo;
                ultimo = nuevoNodo;
                elem ++;
                return true;
         }

      };
  //-----------QUITA_ELEM_IESIMO--------------
      bool quitaElemIesimo(int i)
      {
         Nodo<T>* aux;
         aux=primero;
         while((aux!=NULL) && i>0)
         {
             i--;
             aux=aux->sig;
         }

         //A la hora de borrar distinguimos los siguientes casos

         //Que el elemento a borrar sea el unico
         if(aux->ant==NULL && aux->sig==NULL)
         {
            primero=NULL;
            ultimo=NULL;
         }


         //Que el elemento a borrar sea el primero, pero no sea el unico
         if(aux->ant==NULL && aux->sig!=NULL)
         {
            primero=primero->sig;
            aux->sig=NULL;
            primero->ant=NULL;
         }


         //Que el elemento a borrar sea el ultimo de la lista, pero no sea el unico
         if(aux->ant!=NULL && aux->sig==NULL)
         {
             ultimo=ultimo->ant;
             aux->ant=NULL;
             ultimo->sig=NULL;
         }


         //Que el elemento esté en medio de la lista
         if(aux->ant!=NULL && aux->sig!=NULL)
         {
            Nodo<T>* aux1;
            Nodo<T>* aux2;

            aux1=aux->ant;
            aux2=aux->sig;

            aux1->sig=aux2;
            aux2->ant=aux1;

            aux->sig=NULL;
            aux->ant=NULL;

         }

         delete aux->info;
         aux->info=NULL;

         delete aux;

         elem--;
         return true;

      };



   }; //Fin clase


    #endif
//---------------------------------------------------------------------------


