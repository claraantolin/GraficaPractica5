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
        Lista<PV3D*>* vertice;
        int numNormales; //=numCaras, frecuentemente
        Lista<PV3D*>* normal;
        int numCaras;
        Lista<Cara*>* cara;
   public:
        //Malla(){ Malla(0,new Lista<PV3D*>(), 0, new Lista<PV3D*>(), 0, new Lista<Cara*>()); };
        Malla();//{ Malla(0,NULL, 0, NULL, 0, NULL); };
        Malla(int inumV, Lista<PV3D*>* v, int numN, Lista<PV3D*>* n, int numC, Lista<Cara*>* c){
            numVertices = inumV; vertice = v;
            numNormales = numN;  normal = n;
            numCaras = numC;     cara = c;
        };
        ~Malla(){
        	
            delete vertice;
            delete normal;
            delete cara;

            numVertices = 0;
            numNormales = 0;
            numCaras = 0;
            
        };

        void setAtributosMalla(int inumV, Lista<PV3D*>* v, int numN, Lista<PV3D*>* n, int numC, Lista<Cara*>* c){
        	numVertices = inumV; vertice = v;
	     	numNormales = numN; normal = n;
	     	numCaras = numC; cara = c;
        }

        void dibuja(){

			GLdouble normalX, normalY, normalZ;
			GLdouble verticeX, verticeY, verticeZ;

			for (int i = 0; i < numCaras; i++) {
				
				glColor3d(0,0,0);
				glLineWidth(1.0);
				glBegin(GL_LINE_LOOP);

					for (int j = 0; j < cara->iesimo(i)->getNumVertices(); j++) {

						int iN = cara->iesimo(i)-> getIndiceNormal(j);
						int iV = cara->iesimo(i)-> getIndiceVertice(j);

						normalX = normal->iesimo(iN)->getX();
						normalY = normal->iesimo(iN)->getY();
						normalZ = normal->iesimo(iN)->getZ();

						glNormal3d(normalX,normalY,normalZ);
						
						//Si hubiera coordenadas de textura, aqui se suministrarian
						//las coordenadas de textura del vertice j con glTexCoor2f(...);

						verticeX = vertice->iesimo(iV)->getX();
						verticeY = vertice->iesimo(iV)->getY();
						verticeZ = vertice->iesimo(iV)->getZ();

						glVertex3d(verticeX,verticeY,verticeZ);
					}

				glEnd();
			}

	    }// Dibuja
 
            
            void RellenaVectorNormalPorNewell(){
			
                Cara* c; GLdouble x; GLdouble y; GLdouble z;
                PV3D* vertActual; PV3D* vertSiguiente;

                for(int pos = 0; pos < numCaras; pos++){

                        c = cara->iesimo(pos);
                        x = 0; y = 0; z = 0;

                        for(int i = 0; i < c->getNumVertices(); i++){

                                vertActual = vertice->iesimo(c->getIndiceVertice(i));
                                vertSiguiente = vertice->iesimo(c->getIndiceVertice((i+1) % c->getNumVertices()));
                                x += (vertActual->getY() - vertSiguiente->getY()) * (vertActual->getZ() + vertSiguiente->getZ());
                                y += (vertActual->getZ() - vertSiguiente->getZ()) * (vertActual->getX() + vertSiguiente->getX());
                                z += (vertActual->getX() - vertSiguiente->getX()) * (vertActual->getY() + vertSiguiente->getY());

                        }

                        PV3D* n = new PV3D(x,y,z);
                        n->normaliza();
                        //normal->iesimo(pos)->set3Coor(x,y,z);
                }
                        
            }// CalculoVectorNormalPorNewell
		
};

#endif