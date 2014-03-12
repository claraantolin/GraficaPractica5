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
        	for (int i = 0; i < numCaras; i++) {
				glLineWidth(1.0);
				glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
				for (int j = 0; j < cara[i]-> getNumVertices(); j++) {
					int iN = cara[i]-> getIndiceNormalK(j);
					int iV = cara[i]-> getIndiceVerticeK(j);
					glNormal3f(normal[iN]->getX(),normal[i]->getY(),normal[iN]->getZ());
					//Si hubiera coordenadas de textura, aqui se suministrarian
					//las coordenadas de textura del vertice j con glTexCoor2f(...);
					glVertex3f(vertice[iV]->getX(),vertice[iV]->getY(),vertice[iV]->getZ());
				}
				glEnd();
			}
	    }// Dibuja
};

#endif