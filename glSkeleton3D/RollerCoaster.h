//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef RollerCoasterH
#define RollerCoasterH

#include <gl\gl.h>
#include <gl\glu.h>

#include "Malla.h"
#include "Lista.h"
#include "Cara.h"
//---------------------------------------------------------------------------
class RollerCoaster : public Malla                                                                    
{
   private:
        GLdouble numlados;
        GLdouble numRodajas;

   public:
        RollerCoaster(GLdouble nlados, GLdouble nRodajas):Malla(){
            numlados = nlados;
            numRodajas = nRodajas;
            GLdouble numVertices = nlados * nRodajas;
            Lista<PV3D*>* vertices;
            GLdouble numCaras = nlados * nRodajas;
            //Lista<Cara*>* caras = calculaCaras();

            // Rellenamos la malla
            //Llamamos a newell
        }
        
        ~RollerCoaster(){      
        }
       
        //Lista<Cara*>* calculaCaras()
};

#endif