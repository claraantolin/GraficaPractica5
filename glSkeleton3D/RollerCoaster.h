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

        int numLados;
        int numRodajas;

   public:

        RollerCoaster();
        RollerCoaster(int nlados, int nRodajas):Malla(0,new Lista<PV3D*>(), 0, new Lista<PV3D*>(), 0, new Lista<Cara*>()){
            
            // Damos valor a nuestros atributos
            numLados = nlados;
            numRodajas = nRodajas;

            // Damos valor a los atributos de la malla
            numVertices = nlados * nRodajas;
            calculaVertices();
            numNormales = numVertices; //=numCaras, frecuentemente
            numCaras = numVertices;
            calculaCaras();

            //Llamamos a newell para calcular las normales
            RellenaVectorNormalPorNewell();
        }
        
        ~RollerCoaster(){
            numLados = 0;
            numRodajas = 0;          
        };

        GLdouble getAnguloX(){ return anguloX;}
        GLdouble getAnguloY(){ return anguloY;}
        GLdouble getAnguloZ(){ return anguloZ;}

        void setAnguloX(GLdouble angX){ anguloX = angX;}
        void setAnguloY(GLdouble angY){ anguloY = angY;}
        void setAnguloZ(GLdouble angZ){ anguloZ = angZ;}
       
//------------------------------------------------------------------------------
                        /***** calculaVertices *****/
//------------------------------------------------------------------------------

        void calculaVertices(){

            int radio = 1; GLdouble x, y, z;
            float t; double inc; Lista<PV3D*>* matriz;
            for(int valor=0; valor<numRodajas; valor++){
            
                t = (2* M_PI * valor) / 15;
                matriz = hazMatriz(t,7);
                inc = (2*PI/numLados);

                for(int i=0; i<numLados; i++){
                    x = radio*cos(2*PI-i*inc);
                    y = radio*sin(2*PI-i*inc);
                    z = 0;
                    PV3D* nodo = new PV3D(x, y, z, 1);
                    PV3D* res = multiplicaMatrices(matriz, nodo);
                    vertices->ponElem(res);
                    delete nodo;
                }
                delete matriz;
            }
        }

//------------------------------------------------------------------------------
                        /***** calculaCaras *****/
//------------------------------------------------------------------------------

        void calculaCaras(){

            for(int indiceRodaja = 0, lado = 0; indiceRodaja < numRodajas; indiceRodaja++, lado = lado+numLados){
                
                for(int indiceCara = lado, indAux = 0; indiceCara < (lado+numLados); indiceCara++, indAux++){ 

                    Lista<VerticeNormal*>* arrayVN = new Lista<VerticeNormal*>();

                    // Rellenamos arrayVN de la clase Cara
                    arrayVN->ponElem(new VerticeNormal(indiceCara % numVertices ,indiceCara));
                    
                    if(indAux == numLados-1){ // estamos en el ultimo lado de la rodaja actual
                        arrayVN->ponElem(new VerticeNormal(lado % numVertices ,indiceCara));
                        arrayVN->ponElem(new VerticeNormal((lado+numLados) % numVertices ,indiceCara));
                    }else{
                        arrayVN->ponElem(new VerticeNormal((indiceCara+1) % numVertices ,indiceCara));
                        arrayVN->ponElem(new VerticeNormal((indiceCara+numLados+1) % numVertices ,indiceCara));
                    }
                    
                    arrayVN->ponElem(new VerticeNormal((indiceCara+numLados) % numVertices ,indiceCara));

                    caras->ponElem(new Cara(4,arrayVN)); // Siempre una cara va a estar compuesta de 4 vertices, 2 a 2
                }
            }
        }

//------------------------------------------------------------------------------
                        /***** multiplicaMatrices *****/
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
                        /***** hazMatriz *****/
//------------------------------------------------------------------------------

        Lista<PV3D*>* hazMatriz(GLfloat t, GLfloat r){

            Lista<PV3D*>* matriz = new Lista<PV3D*>();

            PV3D* n = new PV3D(-1 * cos(t),0, -sin(t), r* cos(t));
            PV3D* b = new PV3D(0,-1, 0, 0);
            PV3D* tM = new PV3D(-sin(t),0, cos(t),  r*sin(t));
            PV3D* c = new PV3D(0,0,0, 1);

            matriz->ponElem(n); matriz->ponElem(b); matriz->ponElem(tM); matriz->ponElem(c);
            return matriz;
        }

//------------------------------------------------------------------------------
                        /***** dibujaRoller *****/
//------------------------------------------------------------------------------

        void dibujaRoller(){
            dibuja();
        }

//------------------------------------------------------------------------------
                        /***** rotaRoller *****/
//------------------------------------------------------------------------------

        void rotaRoller(int tipo){
            switch(tipo){
                case 0:
                    anguloY -= 10.0f;
                    break;
                case 1:
                    anguloY += 10.0f;
                    break;
                case 2:
                    anguloX -= 10.0f;
                    break;
                case 3:
                    anguloX += 10.0f;
                    break;
                case 4:
                    anguloZ -= 10.0f;
                    break;
                case 5:
                    anguloZ += 10.0f;
                    break;
                default: break;
            }
        }

//------------------------------------------------------------------------------

};

#endif