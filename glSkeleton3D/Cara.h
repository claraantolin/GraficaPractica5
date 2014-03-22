//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef CaraH
#define CaraH

#include <gl\gl.h>
#include <gl\glu.h>

#include "VerticeNormal.h"
#include "Lista.h"
//---------------------------------------------------------------------------
class Cara                                                                     
{                                                             
    private:

        int numVertices;
        Lista<VerticeNormal*>* arrayVN;

    public:

        Cara(){numVertices = 0;};
        Cara(int numV, Lista<VerticeNormal*>* vn){ numVertices = numV; arrayVN = vn; }
        ~Cara(){ delete arrayVN; numVertices = 0; }
        int getNumVertices(){ return numVertices; }
        Lista<VerticeNormal*>* getArrayVN(){ return arrayVN; }
        int getIndiceNormal(int k){ return arrayVN->iesimo(k)->getVerticeNormal(); }
        int getIndiceVertice(int k){ return arrayVN->iesimo(k)->getVerticeVertice(); }
        void setNumVertices(int numV){ numVertices = numV; }
        void setArrayVN(Lista<VerticeNormal*>* aVN){ arrayVN = aVN; }
};

#endif