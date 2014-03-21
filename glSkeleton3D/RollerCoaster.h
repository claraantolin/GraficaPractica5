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

#define PI 3.14159265

#include "Malla.h"
#include "Lista.h"
#include "Cara.h"
//---------------------------------------------------------------------------
class RollerCoaster : public Malla
{
   private:
        GLdouble numLados;
        GLdouble numRodajas;
        GLdouble numVerticesTotales;
        
   public:
        RollerCoaster();
        RollerCoaster(GLdouble nlados, GLdouble nRodajas):Malla(0,new Lista<PV3D*>(), 0, new Lista<PV3D*>(), 0, NULL){
            
            // Damos valor a nuestros atributos
            numLados = nlados;
            numRodajas = nRodajas;
            numVerticesTotales = nlados * nRodajas;

            // Damos valor a los atributos de la malla
            GLdouble numVertices = numVerticesTotales;
            Lista<PV3D*>* vertices = calculaVertices();
            GLdouble numNormales = numLados;
            Lista<PV3D*>* normales = new Lista<PV3D*>();
            GLdouble numCaras = numLados;
            Lista<Cara*>* caras = calculaCaras();

            // Rellenamos la malla
            setAtributosMalla(numVertices, vertices, numNormales, normales, numCaras, caras);

            //Llamamos a newell para calcular las normales
            RellenaVectorNormalPorNewell();
        }
        
        ~RollerCoaster(){
            numLados = 0;
            numRodajas = 0;
            numVerticesTotales = 0;
            
        };
        
        Lista<PV3D*>* calculaVertices(){

            Lista<PV3D*>* verticesT = new Lista<PV3D*>();
            int radio = 3;

            for(int valor=0; valor<numRodajas; valor++){

                float t = (2* M_PI * valor) / numLados; // habia 15.0
                Lista<PV3D*>* matriz = hazMatriz(t,radio);  // en vez de radio habia un 7
                Lista<PV3D*>* poligono = new Lista<PV3D*>();
                double inc=(2*PI/numLados);

                for(int i=0; i<numLados; i++){
                    PV3D* nodo = new PV3D(radio*cos(2*PI-i*inc) , radio*sin(2*PI-i*inc),0,1);
                    poligono->ponElem(nodo);
                }
                for(int i=0; i<numLados; i++){
                    PV3D* res = multiplicaMatrices(matriz, poligono->iesimo(i));
                    verticesT->ponElem(res);
                }

                delete poligono;
                delete matriz;
            }

            return verticesT;
        }

        Lista<Cara*>* calculaCaras(){

            Lista<Cara*>* listaCaras = new Lista<Cara*>();
            int lado = 0;

            for(int indiceCara = 0; indiceCara < numVerticesTotales; indiceCara++, lado = lado+numLados){
                
                Cara* cara = new Cara();
                cara->setNumVertices(numLados);
                Lista<VerticeNormal*>* arrayVN = new Lista<VerticeNormal*>();

                // Rellenamos arrayVN de la clase Cara
                for(int i = lado; i < lado+numLados; i++)
                    arrayVN->ponElem(new VerticeNormal(i,indiceCara));
                
                cara->setArrayVN(arrayVN);
                listaCaras->ponElem(cara);
            }

            return listaCaras;

        }

        void dibujaRoller(){
            dibuja();
        }

        PV3D* multiplicaMatrices(Lista<PV3D*>* m, PV3D* p){

            PV3D* n = m->iesimo(0);
            GLfloat xPrima = n->getX() * p->getX() + n->getY() * p->getY() + n->getZ() * p->getZ() + n->getW() * p->getW();

            PV3D* b = m->iesimo(1);
            GLfloat yPrima = b->getX() * p->getX() + b->getY() * p->getY() + b->getZ() * p->getZ() + b->getW() * p->getW();

            PV3D* t = m->iesimo(2);
            GLfloat zPrima = t->getX() * p->getX() + t->getY() * p->getY() + t->getZ() * p->getZ() + t->getW() * p->getW();

            PV3D* c = m->iesimo(3);
            GLfloat wPrima = c->getX() * p->getX() + c->getY() * p->getY() + c->getZ() * p->getZ() + c->getW() * p->getW();

            return new PV3D(xPrima, yPrima, zPrima, wPrima);

        }

        Lista<PV3D*>* hazMatriz(GLfloat t, GLfloat r){

            Lista<PV3D*>* matriz = new Lista<PV3D*>();

            PV3D* n = new PV3D(-1 * cos(t),0, -sin(t), r* cos(t));
            PV3D* b = new PV3D(0,-1, 0, 0);
            PV3D* tM = new PV3D(-sin(t),0, cos(t),  r*sin(t));
            PV3D* c = new PV3D(0,0,0, 1);

            matriz->ponElem(n); matriz->ponElem(b); matriz->ponElem(tM); matriz->ponElem(c); 
            return matriz;
        }
};

#endif