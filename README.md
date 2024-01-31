<sub>Redação do ReadMe em andamento...</sub>
# Operações binárias entre polígonos

Uma implementação do algoritmos de Weiler-Atherton para fazer as operações de união, intersecção e negação.

## O programa

Ao iniciar o executavel serão abertas duas janelas, um console que aceita alguns comandos e uma tela de pintura onde o usuário pode desenhar alguns poligonos clicando com o mouse e visualizar o resultado das operações relizadas.
</br>

### Comandos
| Comando | Função |
| ------------- | ------------- |
| NEWPOL | Finaliza o desenho do ultimo polígono desenhado e inicia um novo polígono a ser desenhado pelo usuário. |
| CLIP | Faz o intersecção dos polígonos desenhados. |
| UNION | Faz a união dos polígonos desenhados. |
| NOT | Faz a inversão dos poígonos desenhados. |
| FECHAR | Encerra a execução. |

### Poligonos com buracos e orietação dos polígonos

Na Geometria Computacional, é uma convenção atribuir orientação a polígonos e arestas. Visualize cada aresta de um polígono, composta por dois pontos, como um vetor, em que o ponto desenhado inicialmente representa o início, e o ponto desenhado posteriormente representa o fim desse vetor. Dessa maneira, torna-se possível categorizar qualquer ponto não incidente sobre essa aresta como situado à esquerda ou à direita dela. Portanto, seguindo a mesma convenção, estabelece-se que a região interior de um polígono está posicionada à esquerda de suas arestas, enquanto a região exterior encontra-se à direita.

</br>
</br>

<img width= "80%" src="https://raw.githubusercontent.com/4ntFer/polygon-binary-operations/main/rmimgs/representacaoInteriorDePoligonos.JPG"/>
<sub>Representação onde a cor azul identifica a parte interior e a cor vermelhar a parte exterior do poligono.</sub>

</br>
</br>

Portanto, polígonos desenhados no sentido anti-horário são considerados sólidos, ao passo que os desenhados no sentido horário são interpretados como representando espaços vazios ou buracos. Neste programa, as arestas de polígonos horários são destacadas em vermelho, enquanto as de polígonos anti-horários o são em verde.

<img width= "40%" src="https://raw.githubusercontent.com/4ntFer/polygon-binary-operations/main/rmimgs/greenpol.gif"/>
<img width= "40%" src="https://raw.githubusercontent.com/4ntFer/polygon-binary-operations/main/rmimgs/redpol.gif"/>

Na verdade o que a implementação faz é pintar as arestas de verde caso o polígono tenha area positiva e de vermelho caso tenha area negativa. A area é calculada a partir do seguinte algorítimo:

        Sendo P um vetor de p1, p2, ..., pn pontos.
        Sendo pn + 1 = p1.
        Sendo areaDoTriangulo(px, py, pz) a metade do produto interno <pxpy,pxpz>.
        
        CalculaArea(P)

          pa <- um ponto arbitrário fora do polígono
          area <- 0

          para todo 0 < i < n + 1
            area <- area + areaDoTriangulo(pa, pn, pn+1)

          retorna area







