#include "OpenGLControl.h"
#include "Polygon.h"
#include <stdio.h>
#include <iostream>
#include "cglib.h"

void Poligono::addVertex(float x, float y, float z)
{   
    vertexNumber++;
    points.pushBack(new Point(x, y, 0));
    updateVertexBuffer(vertexArray);

    if (points.size() > 1) {
        edges.pushBack(
            new Edge(
                points.get(points.size() - 2),
                points.get(points.size() - 1)
            )
        );
        updateEdgesBuffer(getEdgeArray());
    }
}

void Poligono::printVertices() {
    printf("\\\\\\\\\\\\\\\n\n");
    for (int i = 0; i < vertexNumber; i++) {

        printf("%f, %f, %f\n", vertexArray[i * 3], vertexArray[i * 3 + 1], vertexArray[i * 3 + 2]);

    }
}

void Poligono::addEdge(Point* p1, Point* p2)
{

    Edge* edge = new Edge(p1, p2);

    points.pushBack(p1);
    points.pushBack(p1);

    edges.pushBack(edge);

}

float* Poligono::getVertexArray()
{
    return vertexArray;
}

int Poligono::getLen()
{
    return len;
}

int Poligono::getVertexNumber()
{
    return vertexNumber;
}

float* Poligono::getEdgeArray()
{   
    float* edgesVertexArray = (float*)malloc(edges.size() * sizeof(float) * 2 * 3);
    for (int i = 0; i < edges.size(); i++) {
        edgesVertexArray[(i * 6)] = edges.get(i)->p1->x;
        edgesVertexArray[(i * 6) + 1] = edges.get(i)->p1->y;
        edgesVertexArray[(i * 6) + 2] = 0;


        edgesVertexArray[(i * 6) + 3] = edges.get(i)->p2->x;
        edgesVertexArray[(i * 6) + 4] = edges.get(i)->p2->y;
        edgesVertexArray[(i * 6) + 5] = 0;

    }

    return edgesVertexArray;
}

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
}

float* EdgeeList::getCoordArray() {
    float* array = (float*)malloc(size() * 6 * sizeof(float));

    for (int i = 0; i < len; i++) {
        array[i*6] = list[i]->p1->x;
        array[i*6 + 1] = list[i]->p1->y;
        array[i*6 + 2] = 0;

        array[i*6+3] = list[i]->p2->x;
        array[i*6 + 4] = list[i]->p2->y;
        array[i*6 + 5] = 0;
    }

    return array;
}

int EdgeeList::size() {
    return len;
}

void EdgeeList::pushBack(Edge* edge) {
    list[len] = edge;
    len++;
}

Edge* EdgeeList::get(int index)
{
    return list[index];
}

void PointsList::pushBack(Point* point)
{
    list[len] = point;
    len++;
}

Point* PointsList::get(int index)
{
    return list[index];
}

int PointsList::size()
{
    return len;
}

Edge::Edge(Point* p1, Point* p2)
{
    this->p1 = p1;
    this->p2 = p2;
}
