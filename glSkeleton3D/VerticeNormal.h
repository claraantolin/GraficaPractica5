//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef VerticeNormalH
#define VerticeNormalH

#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------
class VerticeNormal
{
   private:
        int indiceVertice;   
        int indiceNormal;
   public:
        VerticeNormal();
        VerticeNormal(int indVertice, int indNormal){ indiceVertice = indVertice; indiceNormal = indNormal;}
        ~VerticeNormal(){indiceVertice = 0; indiceNormal = 0;};
        void setVerticeVertice(int indVertice){ indiceVertice = indVertice; }
        void setVerticeNormal(int indNormal){ indiceNormal = indNormal; }
        int getVerticeVertice(){ return indiceVertice; }
        int getVerticeNormal(){ return indiceNormal; }
};

#endif