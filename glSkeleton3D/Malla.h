//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef MallaH
#define MallaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "PV3D.h"
#include "Cara.h"
#include "Lista.h"
//---------------------------------------------------------------------------
class Malla
{
   protected:
    
        int numVertices;
        Lista<PV3D*>* vertices;
        int numNormales; //=numCaras, frecuentemente
        Lista<PV3D*>* normales;
        int numCaras;
        Lista<Cara*>* caras;

   public:
        
        Malla();
        Malla(int inumV, Lista<PV3D*>* v, int numN, Lista<PV3D*>* n, int numC, Lista<Cara*>* c){
            numVertices = inumV; vertices = v;
            numNormales = numN;  normales = n;
            numCaras = numC;     caras = c;
        };
        
        ~Malla(){
        	
            delete vertices;
            delete normales;
            delete caras;

            numVertices = 0;
            numNormales = 0;
            numCaras = 0;
            
        };                     

        void dibuja(){
        
			GLdouble normalX, normalY, normalZ;
			GLdouble verticeX, verticeY, verticeZ;

			for (int i = 0; i < numCaras; i++) {

                                glColor3d(0,0,0);
				glLineWidth(1.0);
				glBegin(GL_LINE_LOOP);

					for (int j = 0; j < caras->iesimo(i)->getNumVertices(); j++) {

						int iN = caras->iesimo(i)-> getIndiceNormal(j);
						int iV = caras->iesimo(i)-> getIndiceVertice(j);

						normalX = normales->iesimo(iN)->getX();
						normalY = normales->iesimo(iN)->getY();
						normalZ = normales->iesimo(iN)->getZ();

						glNormal3d(normalX,normalY,normalZ);
						
						//Si hubiera coordenadas de textura, aqui se suministrarian
						//las coordenadas de textura del vertice j con glTexCoor2f(...);

						verticeX = vertices->iesimo(iV)->getX();
						verticeY = vertices->iesimo(iV)->getY();
						verticeZ = vertices->iesimo(iV)->getZ();
                      
						glVertex3d(verticeX,verticeY,verticeZ);
	     			}

                glEnd();
			}

	    }// Dibuja        
 
            
        void RellenaVectorNormalPorNewell(){
		
            Cara* c; GLdouble x; GLdouble y; GLdouble z;
            PV3D* vertActual; PV3D* vertSiguiente;

            for(int pos = 0; pos < numCaras; pos++){

                c = caras->iesimo(pos);
                x = 0; y = 0; z = 0;

                for(int i = 0; i < c->getNumVertices(); i++){

                    GLdouble a = c->getIndiceVertice(i);
                    GLdouble b = c->getIndiceVertice((i+1) % c->getNumVertices());
                    vertActual = vertices->iesimo(a);
                    vertSiguiente = vertices->iesimo(b);
                    x += (vertActual->getY() - vertSiguiente->getY()) * (vertActual->getZ() + vertSiguiente->getZ());
                    y += (vertActual->getZ() - vertSiguiente->getZ()) * (vertActual->getX() + vertSiguiente->getX());
                    z += (vertActual->getX() - vertSiguiente->getX()) * (vertActual->getY() + vertSiguiente->getY());

                }

                PV3D* n = new PV3D(x,y,z);
                n->normaliza();
                normales->ponElem(n);
            }
                    
        }// CalculoVectorNormalPorNewell
		
};

#endif