#pragma once


using namespace std;

const int BUFFLEN = 100;

class Point {
public:
	float x;
	float y;
	class Edge* edge = nullptr;

	Point(float x, float y, float z);
};

class Edge {
public:
	class Point* p1;
	class Point* p2;
	
	Edge() {};
	Edge(Point* p1, Point* p2);
};

class PointsList {
public:
	Point* list[100];
	int len = 0;

	void pushBack(Point* point);
	Point* get(int index);
	int size();
};

class EdgeeList {
private:
	Edge* list[100];
	int len = 0;
public:

	void pushBack(Edge* edge);
	Edge* get(int index);
	int size();

	float* getCoordArray();

};

class Poligono
{

	public:
		float vertexArray[BUFFLEN];
		int len = 0;
		int vertexNumber = 0;
		PointsList points;
		EdgeeList edges;

		Poligono() {};
		void printVertices();
		void addVertex(float x, float y, float z);
		void addEdge(Point* p1, Point* p2);
		float* getVertexArray();
		float* getEdgeArray();
		int getLen();
		int getVertexNumber();

};
