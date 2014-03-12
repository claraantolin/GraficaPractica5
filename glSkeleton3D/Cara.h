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
//---------------------------------------------------------------------------
class Cara                                                                     
{
   private:
        int numVertices;
        VerticeNormal** arrayVN;
   public:
        Cara();
        Cara(int numV, VerticeNormal** vn){ numVertices = numV; arrayVN = vn;}
        ~Cara(){                                                                                       
            for(int i = 0; i < numVertices; i++) delete arrayVN[i];
            delete[] arrayVN;
            numVertices = 0;
        }
        int getNumVertices(){ return numVertices; }
        VerticeNormal** getArrayVN(){ return arrayVN; }
        int getIndiceNormalK(int k){ return arrayVN[k]->getVerticeVertice(); }
        int getIndiceVerticeK(int k){ return arrayVN[k]->getVerticeNormal(); }
};

#endif