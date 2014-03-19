//---------------------------------------------------------------------------

#ifndef NodoH
#define NodoH
//---------------------------------------------------------------------------
template<class T>
class Nodo{

      // friend class Lista;
        private:
                T* info;
                Nodo<T>* sig;
                Nodo<T>* ant;  

        public:
                Nodo(){info=NULL;sig=NULL;ant=NULL;};
                Nodo(T* i){info=i;sig=NULL;ant=NULL;};

                ~Nodo(){delete info;info=NULL;};

                Nodo<T>* gSig(){return sig;};
                Nodo<T>* gAnt(){return ant;};
                T gInfo(){return info;};
                void sInfo(T* i){info=i;};
                
                void sSig(Nodo<T>* n){sig=n;};
                void sAnt(Nodo<T>* n){sig=n;};

                };
#endif
