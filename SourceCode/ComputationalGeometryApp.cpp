// ComputationalGeometryApp.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdio.h>

#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include "config.h"
#include "OpenGLControl.h"
#include "Polygon.h"
#include "cglib.h"


char userInput[20] = "";

void handleUserInput() {
    while (true) {
        cin >> userInput;

        if (strcmp(userInput, "NEWPOL") == 0) {
            newPolygon(new Poligono());
        }
        else if (strcmp(userInput, "FECHAR") == 0) {
            Poligono* currentPol = getCurrentPolygon();
            currentPol->edges.pushBack(
                new Edge(
                    currentPol->edges.get(currentPol->edges.size()-1)->p2,
                    currentPol->edges.get(0)->p1
                )
            );
        }
        else if (strcmp(userInput, "CLIP") == 0) {
            Poligono* clip = getPolygonInScreen(0);

            for (int i = 1; i < getPolygonsNumber(); i++) {
                if (areaPoligono(getPolygonInScreen(i)->points.list, getPolygonInScreen(i)->points.len) > 0) {
                    clip = clipping(clip, getPolygonInScreen(i));
                    printf("entrou! %f\n", areaPoligono(getPolygonInScreen(i)->points.list, getPolygonInScreen(i)->points.len));
                }
            }

            for (int i = 1; i < getPolygonsNumber(); i++) {
                if (!(areaPoligono(getPolygonInScreen(i)->points.list, getPolygonInScreen(i)->points.len) > 0)) {
                    clip = (unionn((clip), (getPolygonInScreen(i)))[0]);
                    printf("entrou! %d\n", areaPoligono(getPolygonInScreen(i)->points.list, getPolygonInScreen(i)->points.len));
                }
            }

        

            newPolygon(clip);

            setInteractionControlFlag(INT_EDGES_WITH_INTERSECTIONS);
        }
        else if (strcmp(userInput, "UNION") == 0) {
            Poligono** result = (unionn(getPolygonInScreen(0), getPolygonInScreen(1)));


            setPolygons(result, 2);
        }
        else if (strcmp(userInput, "NOT") == 0) {
            Poligono* vet[10];

            for (int i = 0; i < getPolygonsNumber(); i++) {
                vet[i] = nott(getPolygonInScreen(i));
            }

            setPolygons(vet, getPolygonsNumber());
        }
      

        glutPostRedisplay();
    }
}

int main(int argc, char* argv[])
{   
    //string userInput = "";
    Poligono* pol = new Poligono();
    thread userInputThread(handleUserInput);
    setPolygon(pol);


    //userInputThread.join();


    glutInit(&argc, argv);

    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);

    glutCreateWindow("OpenGL me da medo");

    glewInit();

    glutDisplayFunc(render);

    glutMouseFunc(onClick);

    glutMainLoop();

    createVertexBuffer();
}