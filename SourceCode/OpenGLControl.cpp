//#include <stdio.h>
#include "OpenGLControl.h"
#include "Polygon.h"
#include "Lists.h"
#include "stdio.h"
#include "cglib.h"

unsigned int VBO;
int ELEMENT_SIZE = 3;

const int BUFFER_VERTEX_TRIANGLE_POINTER = 30;
const int BUFFER_EDGES_POINTER = 100;
const int BUFFER_POINTS_POINTER = 0;
const int BUFFER_FACE_POINTER = 200;

Poligono* POLS[10];
int POLS_SIZE = 1;
int POL_INDEX = 0;
int EDGES_POINTER = 30;
int POLVERTEX_INDEXEX_IN_BUFFER[10] = { 0,0,0,0,0,0,0,0,0,0 };
int POLEDGES_INDEXEX_IN_BUFFER[10] = { EDGES_POINTER*3,0,0,0,0,0,0,0,0,0 };

int RENDER_TRIANGLE = 0;
const int BUFFERLEN = 1000;
float BUFFER_ARRAY[BUFFERLEN];
int BUFFER_IS_CREATED = 0;

int FACELEN = 0;

float V1[2];
float V2[2];


// Control Flags
int CONTROL_FLAG = 0;
int INTERACTION_CONTROL_FLAG = 0;
int INTERACTION_COUNT = 0;

void setPolygon(Poligono* pol) {
	POLS[0] = pol;
}

Poligono* getCurrentPolygon() {
	return POLS[POL_INDEX];
}

void newPolygon(Poligono* pol) {
	POL_INDEX++;
	POLS[POL_INDEX] = pol;
	POLS_SIZE++;

	if (POL_INDEX != 0) {
		POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX] = POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX - 1] + POLS[POL_INDEX - 1]->points.size() * 3;
		POLEDGES_INDEXEX_IN_BUFFER[POL_INDEX] = POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX] + EDGES_POINTER * 3;
	}
	//TODO: ATUALIZAR O BUFFER NO CASO DE HAVER ARESTAS NO POLIGONO

	if (POLS[POL_INDEX]->edges.size()>0) {
		updateEdgesBuffer(POLS[POL_INDEX]->getEdgeArray());
	}

	//printf("new pol index in buffer is: %d\n", POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX]);
}

void setPolygons(Poligono* vet[], int len) {
	POL_INDEX = -1;
	POLS_SIZE = 0;

	for (int i = 0; i < len; i++) {
		newPolygon(vet[i]);
	}
};

int getPolygonsNumber() {
	return POLS_SIZE;
}

void setControlFlag(int val) {
	CONTROL_FLAG = val;
}

void setInteractionControlFlag(int val)
{
	INTERACTION_CONTROL_FLAG = val;
}

void onClick(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		float normalizedX = (float)x / (float)WIN_WIDTH * 2 - 1;
		float normalizedY = ((float)y / (float)WIN_HEIGHT * 2 - 1) * (-1);

		if (INTERACTION_CONTROL_FLAG == 0) {
			POLS[POL_INDEX]->addVertex(normalizedX, normalizedY, 0);
			//printf("vertex adicionado no poligono %d\n", POL_INDEX);
		}


		//printf("clck x: %f, y: %f\n", normalizedX, normalizedY);
	}
}


void createVertexBuffer()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BUFFER_ARRAY), BUFFER_ARRAY, GL_STATIC_DRAW);
}

void updateBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*BUFFERLEN, BUFFER_ARRAY, GL_STATIC_DRAW);
}

void updateFaceBuffer(float x, float y)
{
}


void createVertexBuffer(float vertexArray[]) {

}

void createVertexBuffer(float vertexArray[], int bufflen) {

	for (int i = 0; i < bufflen; i++) {
		BUFFER_ARRAY[i] = vertexArray[i];
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BUFFERLEN, BUFFER_ARRAY, GL_STATIC_DRAW);
	BUFFER_IS_CREATED = 1;
}


// cada tripla identifica um ponto, duas triplas identificam uma arestas
void updateVertexBuffer(float* vertexArray) {

	if (BUFFER_IS_CREATED == 0) {
		createVertexBuffer(vertexArray, POLS[POL_INDEX]->points.size()*3);
		
	}
	else {
		for (int i = 0; i < POLS[POL_INDEX]->points.size()*3; i++) {
			BUFFER_ARRAY[i+POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX]*3] = vertexArray[i];
			//printf("//%d//\n", i + POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX]*3);
			
		}
	}

}

void updateEdgesBuffer(float* vertexArray) {

	
	for (int i = 0; i < POLS[POL_INDEX]->edges.size()*3*2; i++) {
			BUFFER_ARRAY[i + POLEDGES_INDEXEX_IN_BUFFER[POL_INDEX] * 3] = vertexArray[i];
			//printf("%f\n", BUFFER_ARRAY[i + POLEDGES_INDEXEX_IN_BUFFER[POL_INDEX] * 3]);
	}
}

Poligono* getPolygonInScreen(int index)
{
	return POLS[index];
}




void renderPoints(int vertexNumber) {

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, ELEMENT_SIZE, GL_FLOAT, GL_FALSE, ELEMENT_SIZE * sizeof(float), 0);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, vertexNumber);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void renderPolygon(int vertexNumber) {

	glVertexAttribPointer(0, ELEMENT_SIZE, GL_FLOAT, GL_FALSE, ELEMENT_SIZE * sizeof(float), 0);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_LINE_LOOP, 0, vertexNumber);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void renderTriangles(int vertexNumber) {
}

void renderTriangle() {
}

void renderPointsFromDcel()
{
}

void renderEdgesFromDcel()
{
}

void renderOpFaceFromDcel()
{
}

void printDcelEdges()
{
}

void printDcelVertices()
{
}

void drawTriangle(float p[], float q[], float r[]) {
}


//Trab 2

void renderEdges(){

}

void renderPolygonsEdges() {

	updateBuffer();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, ELEMENT_SIZE, GL_FLOAT, GL_FALSE, ELEMENT_SIZE * sizeof(float), 0);

	glEnableVertexAttribArray(0);

	for (int i = 0; i < POLS_SIZE; i += 1) {
		if (POLS[i]->points.len > 0) {
			if (areaPoligono(POLS[i]->points.list, POLS[i]->points.len) > 0){
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else {
				glColor3f(1.0f, 0.0f, 0.0f);
			}

			for(int j = 0 ; j< POLS[i]->edges.size() * 2; j+=2)
				glDrawArrays(GL_LINES, POLEDGES_INDEXEX_IN_BUFFER[i] + j, 2);
		} 
		//printf("Desenhando %d vértices, começando de %d\n", POLS[i]->getVertexNumber(), POLEDGES_INDEXEX_IN_BUFFER[i]);
	}


	//(GL_LINE_LOOP, POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX], POLS[POL_INDEX]->getVertexNumber());

	glDisableVertexAttribArray(0);

	glutSwapBuffers();

}


void renderPolygonEdges(int index) {

	updateBuffer();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, ELEMENT_SIZE, GL_FLOAT, GL_FALSE, ELEMENT_SIZE * sizeof(float), 0);

	glEnableVertexAttribArray(0);

	if (POLS[index]->edges.size() > 0) {
		if (areaPoligono(POLS[index]->points.list, POLS[index]->points.len) > 0) {
			glColor3f(0.0f, 1.0f, 0.0f);
		}
		else {
			glColor3f(1.0f, 0.0f, 0.0f);
		}
		for (int j = 0; j < POLS[index]->edges.size() * 2; j += 2) {
			glDrawArrays(GL_LINES, POLEDGES_INDEXEX_IN_BUFFER[index] + j, 2);
		}
	}


	//(GL_LINE_LOOP, POLVERTEX_INDEXEX_IN_BUFFER[POL_INDEX], POLS[POL_INDEX]->getVertexNumber());

	glDisableVertexAttribArray(0);

	glutSwapBuffers();

}

void render() {

	glClear(GL_COLOR_BUFFER_BIT);

	if (INTERACTION_CONTROL_FLAG == INT_EDGES_WITH_INTERSECTIONS) {
		renderPolygonEdges(POLS_SIZE - 1);
	}
	else {
		renderPolygonsEdges();
	}
	
}

