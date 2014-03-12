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
        GLfloat x;
        GLfloat y;
        GLfloat z;

        int pv;

   public:
        PV3D();
        PV3D(GLfloat newX, GLfloat newY, GLfloat newZ){ x=newX; y=newY; z = newZ; };
        ~PV3D(){ x=0 ; y=0; x=0;};
        GLfloat getX(){return x;};
        GLfloat getY(){return y;};
        GLfloat getZ(){return z;};
        void setCoor(GLfloat newX, GLfloat newY, GLfloat newZ){x=newX; y=newY; z=newZ;};
        void setX(GLfloat newX){x=newX;};
        void setY(GLfloat newY){y=newY;};
        void setZ(GLfloat newZ){y=newZ;};
        
        void normaliza(){
            // TODO
        }


        PV3D* clona(){
            return new PV3D(x, y, z);
        }


        GLfloat profuctoEscalar(PV3D* v){
            // TODO
            return 0;
        }


        PV3D* profuctoVectorial(PV3D* v){
            // TODO
            return new PV3D();
        }
};

#endif
