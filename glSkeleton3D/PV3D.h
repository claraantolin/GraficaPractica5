//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef PV3DH
#define PV3DH

#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------
class PV3D
{
   private:
        // Coordenadas de un Punto o Vector en tres dimensiones
        GLdouble x;
        GLdouble y;
        GLdouble z;

        int pv;

   public:
        PV3D();
        PV3D(GLdouble newX, GLdouble newY, GLdouble newZ){ x=newX; y=newY; z = newZ; };
        ~PV3D(){ x=0 ; y=0; x=0;};
        GLdouble getX(){return x;};
        GLdouble getY(){return y;};
        GLdouble getZ(){return z;};
        void setCoor(GLdouble newX, GLdouble newY, GLdouble newZ){x=newX; y=newY; z=newZ;};
        void setX(GLdouble newX){x=newX;};
        void setY(GLdouble newY){y=newY;};
        void setZ(GLdouble newZ){y=newZ;};
        
        void normaliza(){
           GLdouble modulo = sqrt (pow (x,2) +  pow(y, 2) + pow (z,2)  );
           GLdouble componenteX = x / modulo;
           GLdouble componenteY = y / modulo;
           GLdouble componenteZ = z / modulo;
           x = componenteX; y = componenteY; z = componenteZ;
        }


        PV3D* clona(){
            return new PV3D(x, y, z);
        }


        GLdouble profuctoEscalar(PV3D* v){
             return (x * v->getX() + y * v->getY() + z * v->getZ());
        }


        PV3D* profuctoVectorial(PV3D* v){
            // TODO
            return new PV3D();
        }
};

#endif
