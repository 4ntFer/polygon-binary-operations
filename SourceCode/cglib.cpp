#include "cglib.h"
#include "Polygon.h"
#include <stdio.h>
#include <math.h>
#include <corecrt_malloc.h>

int TRUE = 1;
int FALSE = -1;

/*OPERACOES BASICAS*/

bool pointsEquals(Point* p1, Point* p2) {
	if (p1->x == p2->x && p1->y == p2->y) {
		return true;
	}
	else {
		return false;
	}
}

float distanciaEuclidiana(Point* p1, Point* p2) {
	float d = (sqrt((p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y)* (p2->y - p1->y)));

	return d;
}

int left(float p[], float q[], float r[]) {
	float val = (
			p[0] * q[1] + p[1] * r[0] + q[0] * r[1]
			- q[1] * r[0] - p[1] * q[0] - p[0] * r[1]
		);

	if (val >= 0) {
		return 1;
	}
	else {
		return -1;
	}
}

int left(Point* p1, Point* p2, Point* p3) {
	float p[3] = {p1->x, p1->y, 0};
	float r[3] = { p2->x, p2->y, 0 };
	float q[3] = { p3->x, p3->y, 0 };

	return left(p, r, q);
}

bool verificaInterseccao(Edge* e1, Edge* e2) {
	return(
		(
			left(e1->p1, e1->p2, e2->p1) != left(e1->p1, e1->p2, e2->p2)
			)
		&&
		(
			left(e2->p1, e2->p2, e1->p1) != left(e2->p1, e2->p2, e1->p2)
			)
		);

}

bool verificaSePontoDentroPoligono(Point* p, Poligono* g) {
	Edge* linhaInf;
	Point* p1 = p;
	Point* p2 = new Point(2.0f, p->y, 0.0);
	int res = 0;
	linhaInf = new Edge(p1, p2);

	//considerando apenas intersecçÕes próprias
	for (int i = 0; i < g->edges.size(); i++) {
		if (verificaInterseccao(linhaInf, g->edges.get(i))) {
			res++;
		}
	}

	if (res % 2>0) {
		return true;
	}
	else {
		return false;
	}
}

//Retorna vetor em que cada par de inteiro identifica as arestas que se intersectam no primeiro e segundo poligono
int* encontraArestasQueIntersectam(Poligono* g1, Poligono* g2) {

	int result[100];
	int len = 0;

	//Posições vazias no resultado são iguais a -1

	for (int i = 0; i < 100; i++) {
		result[i] = -1;
	}

	EdgeeList pol1 = g1->edges;
	EdgeeList pol2 = g2->edges;

	for (int i = 0; i < pol1.size(); i++) {
		for (int j = 0; j < pol2.size(); j++) {
			if (verificaInterseccao(pol1.get(i), pol2.get(j))) {
				result[len] = i;
				len++;
				result[len] = j;
				len++;

				printf("Encontrou intersecção!\n");
			}
		}
	}
	return result;
}

int** matrizDeInterseccao(Poligono* g1, Poligono* g2) {
	int** matriz = (int**)malloc(sizeof(int*) * g1->edges.size());

	for (int i = 0; i < g1->edges.size(); i++) {
		matriz[i] = (int*)malloc(sizeof(int) * g2->edges.size());
		
		for (int j = 0; j < g2->edges.size(); j++) {
			matriz[i][j] = 0;
		}
	}

	for (int i = 0; i < g1->edges.size(); i++) {
		for (int j = 0; j < g2->edges.size(); j++) {
			if (verificaInterseccao(g1->edges.get(i), g2->edges.get(j))) {
				matriz[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < g1->edges.size(); i++) {
		printf("\n");
		for (int j = 0; j < g2->edges.size(); j++) {
			printf("%d ", matriz[i][j]);
		}
	}

	return matriz;
}

Point* encontraPontoDeInterseccao(Edge* e1, Edge* e2) {
	//TODO: tratar restas coincidentes ou colineares

	Point* result = new Point(0.0,0.0,0.0);

	Point v1_1 = *(e1->p1);
	Point v1_2 = *(e1->p2);

	Point v2_1 = *(e2->p1);
	Point v2_2 = *(e2->p2);

	float xres;
	float yres;
	float zres = 0.0;


	xres = ((v1_1.x * v1_2.y - v1_1.y * v1_2.x) * (v2_1.x - v2_2.x) - (v1_1.x - v1_2.x) * (v2_1.x * v2_2.y - v2_1.y * v2_2.x)) /
		((v1_1.x - v1_2.x) * (v2_1.y - v2_2.y) - (v1_1.y - v1_2.y) * (v2_1.x - v2_2.x));
	yres = ((v1_1.x * v1_2.y - v1_1.y * v1_2.x) * (v2_1.y - v2_2.y) - (v1_1.y - v1_2.y) * (v2_1.x * v2_2.y - v2_1.y * v2_2.x)) /
		((v1_1.x - v1_2.x) * (v2_1.y - v2_2.y) - (v1_1.y - v1_2.y) * (v2_1.x - v2_2.x));

	result->x = xres;
	result->y = yres;


	return result;
}

float areaTriangulo(float p[], float q[], float r[]) {
	float val = (
		p[0] * q[1] + p[1] * r[0] + q[0] * r[1]
		- q[1] * r[0] - p[1] * q[0] - p[0] * r[1]
		);

	return val;
}

float areaTriangulo(Point* p1, Point* p2, Point* p3) {

	float p[3] = { p1->x, p1->y, 0 };
	float r[3] = { p2->x, p2->y, 0 };
	float q[3] = { p3->x, p3->y, 0 };

	return areaTriangulo(p, r, q);
}

float areaPoligono(Point* vertices[], int len) {
	Point* externalDot = new Point(0, -2, 0);
	float area = 0;

	if (len >= 1) {

		for (int i = 0; i < len - 1; i++) {
			area += areaTriangulo(externalDot, vertices[i], vertices[i + 1]);
		}


		return area + areaTriangulo(externalDot, vertices[len - 1], vertices[0]);
	}

	return 0;
}



/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*DEPRECATED*/

const int ENTRANDO = 1;
const int SAINDO = -1;


/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/

/*FINAL*/

Poligono* clipping(Poligono* g1, Poligono* g2) {
	int** interseccoes = matrizDeInterseccao(g1, g2);
	Point* clipped[100]; //g1
	Point* clipping[100]; //g2
	int clippedLen = 0;
	int clippingLen = 0;

	int label;
	int clippedLabel[100]; // 0 = vertice do poligono, 1 = intersecção entrand0, -1 = intersecção saindo
	int clippingLabel[100];
	int numeroVerticesEntrando = 0; //No poligono original

	for (int i = 0; i < 100; i++) {
		clippedLabel[i] = 0;
		clippingLabel[i] = 0;
	}

	



		//Construindo lista do poligo A, considerando intersecções

	clipped[clippedLen] = g1->edges.get(0)->p1;
	clippedLabel[0] = 0;
	clippedLen++;
	for (int i = 0; i < g1->edges.size(); i++) {
		//verifica se p1 está dentro ou fora do poligono e a cada intersecção depois disso troca
		//se essa está entrando ou saindo


		//TODO: reavaliar se as intersecçÕes aparecem na ordem correta
		for (int j = 0; j < g2->edges.size(); j++) {
			//As intersecções devem estar ordenadas em ordem temporal


			if (interseccoes[i][j] == 1) {
				clipped[clippedLen] = encontraPontoDeInterseccao(g1->edges.get(i), g2->edges.get(j));

				//inserindo de forma ordenada
				int index = clippedLen;
				for (index = clippedLen; index > 0 &&
					(distanciaEuclidiana(g1->edges.get(i)->p1, clipped[index]) < distanciaEuclidiana(g1->edges.get(i)->p1, clipped[index - 1]))
					; index--
					) {
					Point* aux = clipped[index - 1];
					int auxLabel = clippedLabel[index - 1];

					clipped[index - 1] = clipped[index];
					clippedLabel[index - 1] = clippedLabel[index];
					clipped[index] = aux;
					clippedLabel[index] = auxLabel;
				}

				clippedLabel[index] = 10;
				clippedLen++;
			}
		}


		clippedLabel[clippedLen] = 0;
		clipped[clippedLen] = g1->edges.get(i)->p2;
		clippedLen++;
	}



	//Construindo lista do poligo B, considerando intersecções

	clipping[clippingLen] = g2->edges.get(0)->p1;
	clippingLabel[0] = 0;
	clippingLen++;
	for (int i = 0; i < g2->edges.size(); i++) {




		//TODO: reavaliar se as intersecçÕes aparecem na ordem correta
		for (int j = 0; j < g1->edges.size(); j++) {

			//As intersecções devem estar ordenadas em ordem temporal

			if (interseccoes[j][i] == 1) {
				clipping[clippingLen] = encontraPontoDeInterseccao(g1->edges.get(j), g2->edges.get(i));

				//inserindo de forma ordenada
				int index = clippingLen;
				for (index = clippingLen; index > 0 &&
					(distanciaEuclidiana(g2->edges.get(i)->p1, clipping[index]) < distanciaEuclidiana(g2->edges.get(i)->p1, clipping[index - 1]))
					; index--
					) {
					Point* aux = clipping[index - 1];
					int auxLabel = clippingLabel[index - 1];

					clipping[index - 1] = clipping[index];
					clippingLabel[index - 1] = clippingLabel[index];
					clipping[index] = aux;
					clippingLabel[index] = auxLabel;
				}

				clippingLabel[index] = 10;
				clippingLen++;
			}
		}

		clippingLabel[clippingLen] = 0;
		clipping[clippingLen] = g2->edges.get(i)->p2;
		clippingLen++;
	}

	//Classificando labels como entrada ou saída na lista de A

	for (int i = 1; i < clippedLen; i++) {
		if (clippedLabel[i] != 0) {
			if (clippedLabel[i - 1] == 0) {
				if (verificaSePontoDentroPoligono(clipped[i - 1], g2)) {
					label = SAINDO;
				}
				else {
					label = ENTRANDO;
					numeroVerticesEntrando++;
				}
			}
			else {
				if (clippedLabel[i - 1] == ENTRANDO) {
					label = SAINDO;
				}
				else {
					label = ENTRANDO;
					numeroVerticesEntrando++;
				}
			}
		}
		else
			label = 0;

		clippedLabel[i] = label;
	}


	//Classificando labels como entrada ou saída na lista de B

	for (int i = 1; i < clippingLen; i++) {
		if (clippingLabel[i] != 0) {
			if (clippingLabel[i - 1] == 0) {
				if (verificaSePontoDentroPoligono(clipping[i - 1], g1)) {
					label = SAINDO;
				}
				else {
					label = ENTRANDO;
				}
			}
			else {
				if (clippingLabel[i - 1] == ENTRANDO) {
					label = SAINDO;
				}
				else {
					label = ENTRANDO;
				}
			}
		}
		else
			label = 0;

		clippingLabel[i] = label;
	}

	if (numeroVerticesEntrando != 0) {
		//Operação de intersecção
		Point* result[100];
		int resultLen = 0;
		//busca a primeira intersecção entrando
		int polygonHead; // point index in clipped LIST
		for (int i = 0; i < clippedLen; i++) {
			if (clippedLabel[i] == ENTRANDO) {
				polygonHead = i;
				break;
			}
		}

		//Faz enquanto ainda existir nós de entrada que ainda não foram inseridos

		int currentPoint = polygonHead + 1;
		int currentList = 0;
		Point** list[2] = { clipped, clipping };
		int listLen[2] = { clippedLen, clippingLen };
		int* labelList[2] = { clippedLabel, clippingLabel };
		int numeroVerticesEntrandoResult = 0;

		bool inserido[100]; //dicionario de vertices se inserido ou não

		for (int i = 0; i < 100; i++) {
			inserido[i] = false;
		}


		Poligono* returned = new Poligono();

		do {
			resultLen = 0;
			//busca por intersecção entrando ainda não inserida no resultado
			for (int i = 0; i < clippedLen; i++) {
				if (clippedLabel[i] == ENTRANDO && !inserido[i]) {
					polygonHead = i;
					inserido[i] = true;
					numeroVerticesEntrandoResult++;
					break;
				}
			}

			currentPoint = polygonHead + 1;
			currentList = 0;


			result[resultLen] = list[currentList][polygonHead];
			resultLen++;


			//Enquanto cabeça do poligono for diferente do ponto da interação atual
			while (!pointsEquals(clipped[polygonHead], list[currentList][currentPoint])) {


				//coloca o pornto no resultado
				result[resultLen] = list[currentList][currentPoint];
				resultLen++;


				//Se encontrou uma intersecção saindo, então troca para o outro poligono e continua
				//da mesma intersecção
				if (labelList[currentList][currentPoint] == SAINDO) {


					//troca de lista
					Point* intersectionPoint = list[currentList][currentPoint];
					if (currentList == 0) {
						currentList = 1;
					}
					else {
						currentList = 0;
					}

					//buscando o ponto de intersecção na nova lista
					for (int i = 0; i < listLen[currentList]; i++) {
						if (pointsEquals(list[currentList][i], intersectionPoint)) {
							currentPoint = i;
							break;
						}
					}

					if (currentList == 0 && !inserido[currentPoint]) {
						numeroVerticesEntrandoResult++;
						inserido[currentPoint] = true;
					}
				}


				if (currentPoint == listLen[currentList] - 1) {
					currentPoint = 0;
				}
				else {
					currentPoint++;
				}

			}


			for (int i = 0; i < resultLen - 1; i++) {
				Edge* e = new Edge(result[i], result[i + 1]);

				returned->points.pushBack(result[i]);
				returned->edges.pushBack(e);
			}

			returned->points.pushBack(result[resultLen - 1]);
			returned->edges.pushBack(new Edge(result[resultLen - 1], result[0]));


		} while (numeroVerticesEntrando != numeroVerticesEntrandoResult);


		return returned;
	}
	else {
		Poligono* returned = new Poligono;

		for (int i = 0; i < g1->edges.size(); i++) {
			returned->edges.pushBack(g1->edges.get(i));
			returned->points.pushBack(g1->edges.get(i)->p1);
		}


		for (int i = 0; i < g2->edges.size(); i++) {
			returned->edges.pushBack(g2->edges.get(i));
			returned->points.pushBack(g2->edges.get(i)->p1);
		}


		return returned;
	}
}

Poligono** unionn(Poligono* g1, Poligono* g2) {
	int** interseccoes = matrizDeInterseccao(g1, g2);
	Point* clipped[100]; //g1
	Point* clipping[100]; //g2
	int clippedLen = 0;
	int clippingLen = 0;

	int label;
	int clippedLabel[100]; // 0 = vertice do poligono, 1 = intersecção entrand0, -1 = intersecção saindo
	int clippingLabel[100];

	for (int i = 0; i < 100; i++) {
		clippedLabel[i] = 0;
		clippingLabel[i] = 0;
	}

	int numerodeVerticesSaindo = 0;
	//TODO: admitir buraco



		//Construindo lista do poligo A, considerando intersecções

	clipped[clippedLen] = g1->edges.get(0)->p1;
	clippedLabel[0] = 0;
	clippedLen++;
	for (int i = 0; i < g1->edges.size(); i++) {
		//verifica se p1 está dentro ou fora do poligono e a cada intersecção depois disso troca
		//se essa está entrando ou saindo


		//TODO: reavaliar se as intersecçÕes aparecem na ordem correta
		for (int j = 0; j < g2->edges.size(); j++) {
			//As intersecções devem estar ordenadas em ordem temporal


			if (interseccoes[i][j] == 1) {
				clipped[clippedLen] = encontraPontoDeInterseccao(g1->edges.get(i), g2->edges.get(j));

				//inserindo de forma ordenada
				int index = clippedLen;
				for (index = clippedLen; index > 0 &&
					(distanciaEuclidiana(g1->edges.get(i)->p1, clipped[index]) < distanciaEuclidiana(g1->edges.get(i)->p1, clipped[index - 1]))
					; index--
					) {
					Point* aux = clipped[index - 1];
					int auxLabel = clippedLabel[index - 1];

					clipped[index - 1] = clipped[index];
					clippedLabel[index - 1] = clippedLabel[index];
					clipped[index] = aux;
					clippedLabel[index] = auxLabel;
				}

				clippedLabel[index] = 10;
				clippedLen++;
			}
		}


		clippedLabel[clippedLen] = 0;
		clipped[clippedLen] = g1->edges.get(i)->p2;
		clippedLen++;
	}



	//Construindo lista do poligo B, considerando intersecções

	clipping[clippingLen] = g2->edges.get(0)->p1;
	clippingLabel[0] = 0;
	clippingLen++;
	for (int i = 0; i < g2->edges.size(); i++) {




		//TODO: reavaliar se as intersecçÕes aparecem na ordem correta
		for (int j = 0; j < g1->edges.size(); j++) {

			//As intersecções devem estar ordenadas em ordem temporal

			if (interseccoes[j][i] == 1) {
				clipping[clippingLen] = encontraPontoDeInterseccao(g1->edges.get(j), g2->edges.get(i));

				//inserindo de forma ordenada
				int index = clippingLen;
				for (index = clippingLen; index > 0 &&
					(distanciaEuclidiana(g2->edges.get(i)->p1, clipping[index]) < distanciaEuclidiana(g2->edges.get(i)->p1, clipping[index - 1]))
					; index--
					) {
					Point* aux = clipping[index - 1];
					int auxLabel = clippingLabel[index - 1];

					clipping[index - 1] = clipping[index];
					clippingLabel[index - 1] = clippingLabel[index];
					clipping[index] = aux;
					clippingLabel[index] = auxLabel;
				}

				clippingLabel[index] = 10;
				clippingLen++;
			}
		}

		clippingLabel[clippingLen] = 0;
		clipping[clippingLen] = g2->edges.get(i)->p2;
		clippingLen++;
	}

	//Classificando labels como entrada ou saída na lista de A

	for (int i = 1; i < clippedLen; i++) {
		if (clippedLabel[i] != 0) {
			if (clippedLabel[i - 1] == 0) {
				if (verificaSePontoDentroPoligono(clipped[i - 1], g2)) {
					label = SAINDO;
					numerodeVerticesSaindo++;
				}
				else {
					label = ENTRANDO;
				}
			}
			else {
				if (clippedLabel[i - 1] == ENTRANDO) {
					label = SAINDO;
					numerodeVerticesSaindo++;
				}
				else {
					label = ENTRANDO;
				}
			}
		}
		else
			label = 0;

		clippedLabel[i] = label;
	}


	//Classificando labels como entrada ou saída na lista de B

	for (int i = 1; i < clippingLen; i++) {
		if (clippingLabel[i] != 0) {
			if (clippingLabel[i - 1] == 0) {
				if (verificaSePontoDentroPoligono(clipping[i - 1], g1)) {
					label = SAINDO;
				}
				else {
					label = ENTRANDO;
				}
			}
			else {
				if (clippingLabel[i - 1] == ENTRANDO) {
					label = SAINDO;
				}
				else {
					label = ENTRANDO;
				}
			}
		}
		else
			label = 0;

		clippingLabel[i] = label;
	}

	//Operação de intersecção
	Point* result[100];
	int resultLen = 0;
	//busca a primeira intersecção entrando
	int polygonHead; // point index in clipped LIST
	for (int i = 0; i < clippedLen; i++) {
		if (clippedLabel[i] == SAINDO) {
			polygonHead = i;
			break;
		}
	}

	int currentPoint = polygonHead + 1;
	int currentList = 0;
	Point** list[2] = { clipped, clipping };
	int listLen[2] = { clippedLen, clippingLen };
	int* labelList[2] = { clippedLabel, clippingLabel };

	int numeroDeVerticesSaindoResult = 0;
	bool inserido[100];

	for (int i = 0; i < 100; i++) {
		inserido[i] = false;
	}

	Poligono* returnedPoligono = new Poligono;
	Poligono* returnedBuraco = new Poligono;

	do {
		resultLen = 0;

		for (int i = 0; i < clippedLen; i++) {
			if (clippedLabel[i] == SAINDO && !inserido[i]) {
				polygonHead = i;
				inserido[i] = true;
				numeroDeVerticesSaindoResult++;
				break;
			}
		}

		currentPoint = polygonHead + 1;
		currentList = 0;

		result[0] = list[currentList][polygonHead];
		resultLen++;

		//Enquanto cabeça do poligono for diferente do ponto da interação atual
		while (!pointsEquals(clipped[polygonHead], list[currentList][currentPoint])) {


			//coloca o pornto no resultado
			result[resultLen] = list[currentList][currentPoint];
			resultLen++;

			//Se encontrou uma intersecção entrando, então troca para o outro poligono e continua
			//da mesma intersecção
			if (labelList[currentList][currentPoint] == ENTRANDO) {

				//troca de lista
				Point* intersectionPoint = list[currentList][currentPoint];
				if (currentList == 0) {
					currentList = 1;
				}
				else {
					currentList = 0;
				}

				//buscando o ponto de intersecção na nova lista
				for (int i = 0; i < listLen[currentList]; i++) {
					if (pointsEquals(list[currentList][i], intersectionPoint)) {
						currentPoint = i;
						break;
					}
				}

				if (currentList == 0 && !inserido[currentPoint]) {
					numeroDeVerticesSaindoResult++;
					inserido[currentPoint] = true;
				}
			}

			if (currentPoint == listLen[currentList] - 1) {
				currentPoint = 0;
			}
			else {
				currentPoint++;
			}

		}

		if (areaPoligono(result, resultLen) > 0) {

			for (int i = 0; i < resultLen - 1; i++) {
				Edge* e = new Edge(result[i], result[i + 1]);


				returnedPoligono->points.pushBack(result[i]);
				returnedPoligono->edges.pushBack(e);
			}


			returnedPoligono->points.pushBack(result[resultLen - 1]);
			returnedPoligono->edges.pushBack(new Edge(result[resultLen - 1], result[0]));
		}
		else {
			for (int i = 0; i < resultLen - 1; i++) {
				Edge* e = new Edge(result[i], result[i + 1]);

				returnedBuraco->points.pushBack(result[i]);
				returnedBuraco->edges.pushBack(e);
			}

			returnedBuraco->points.pushBack(result[resultLen-1]);
			returnedBuraco->edges.pushBack(new Edge(result[resultLen - 1], result[0]));
		}
	} while (numerodeVerticesSaindo != numeroDeVerticesSaindoResult);

	Poligono** returns = (Poligono**)malloc(2 * sizeof(Poligono*));
	
	returns[0] = returnedPoligono;
	returns[1] = returnedBuraco;

	return returns;
}

Poligono* nott(Poligono* g1)
{
	Poligono* returned = new Poligono;

	for (int i = g1->edges.size() - 1; i >=0; i--) {
		Edge* e = new Edge();

		e->p1 = g1->edges.get(i)->p2;
		e->p2 = g1->edges.get(i)->p1;
		
		returned->edges.pushBack(e);
	}

	for (int i = g1->points.size() - 1; i >= 0; i--) {
		returned->points.pushBack(g1->points.get(i));
	}

	return returned;
}