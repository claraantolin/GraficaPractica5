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
//---------------------------------------------------------------------------
class Malla
{
   private:
        int numVertices;
        PV3D** vertice;
        int numNormales; //=numCaras, frecuentemente
        PV3D** normal;
        int numCaras;
        Cara** cara;
   public:
   		Malla();
        Malla(int inumV, PV3D** v, int numN, PV3D** n, int numC, Cara** c){
      		numVertices = inumV;
        	vertice = v;
	     	numNormales = numN;
	        normal = n;
	     	numCaras = numC;
	        cara = c;
        };
        ~Malla(){
        	
        	for(int i = 0; i < numVertices; i++) delete vertice[i];
	       	for(int i = 0; i < numNormales; i++) delete normal[i];
	        for(int i = 0; i < numCaras; i++) delete cara[i];

	        delete[] vertice;
	    	delete[] normal;
	    	delete[] cara;
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
				//glBegin(GL_POLYGON);
                                glBegin(GL_LINE_LOOP);

				for (int j = 0; j < cara[i]-> getNumVertices(); j++) {

					int iN = cara[i]-> getIndiceNormal(j);
					int iV = cara[i]-> getIndiceVertice(j);

					normalX = normal[iN]->getX();
					normalY = normal[iN]->getY();
					normalZ = normal[iN]->getZ();

					glNormal3d(normalX,normalY,normalZ);
					
					//Si hubiera coordenadas de textura, aqui se suministrarian
					//las coordenadas de textura del vertice j con glTexCoor2f(...);

					verticeX = vertice[iV]->getX();
					verticeY = vertice[iV]->getY();
					verticeZ = vertice[iV]->getZ();

					glVertex3d(verticeX,verticeY,verticeZ);
				}
				glEnd();
			}
	    }// Dibuja

		void RellenaVectorNormalPorNewell(){
			
			Cara* c; GLdouble x; GLdouble y; GLdouble z;
			PV3D* vertActual; PV3D* vertSiguiente;

			for(int pos = 0; pos < numCaras; pos++){

				c = cara[pos];
				x = 0; y = 0; z = 0;

				for(int i = 0; i < c->getNumVertices(); i++){

					vertActual = vertice[c->getIndiceVertice(i)];
					vertSiguiente = vertice[c->getIndiceVertice((i+1) % c->getNumVertices())];
					x += (vertActual->getY() - vertSiguiente->getY()) * (vertActual->getZ() + vertSiguiente->getZ());
					y += (vertActual->getZ() - vertSiguiente->getZ()) * (vertActual->getX() + vertSiguiente->getX());
					z += (vertActual->getX() - vertSiguiente->getX()) * (vertActual->getY() + vertSiguiente->getY());

				}

				PV3D* n = new PV3D(x,y,z);
				n->normaliza();
				normal[pos] = n;
			}

		}// CalculoVectorNormalPorNewell
		
};

#endif