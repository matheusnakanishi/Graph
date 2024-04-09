#include <stdio.h>
#include <stdlib.h>

int **inicializar_grafo(int n) {
    int **grafo;

    grafo = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) 
        grafo[i] = calloc(n, sizeof(int));
    
    return grafo;
}

void imprimir_grafo(int **grafo, int n) {
    printf("\n   ");
    for (int k = 1; k <= n; k++)
        printf(" [%d]", k);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] ", i+1);
        for (int j = 0; j < n; j++) {
            printf("%2d  ", grafo[i][j]);
        }
        printf("\n");
    }
}

void liberar_memoria(int **grafo, int n) {
    for (int i = 0; i < n; i++) {
        free(grafo[i]);
    }
    free(grafo);
}

void adicionar_aresta(int **grafo, int n, int i, int j, int peso) {
    if (i > 0 && j > 0 && i <= n && j <= n) {
        grafo[i-1][j-1] = peso;
        printf("\nAresta [%d -> %d] adicionada\n", i, j);
    }
    else
        printf("\nVertices invalidos\n");

} 

void remover_aresta(int **grafo, int n, int i, int j) {
    if (i > 0 && j > 0 && i <= n && j <= n) {
        grafo[i-1][j-1] = 0;
        printf("\nAresta [%d -> %d] removida\n", i, j);
    }
    else
        printf("\nVertices invalidos\n");

} 

void verificar_existencia_aresta(int **grafo, int n, int i, int j) {
    if ((i > 0 && j > 0 && i <= n && j <= n) && grafo[i-1][j-1] != 0)
        printf("\nAresta [%d -> %d] de peso %d existente\n", i, j, grafo[i-1][j-1]);
    else    
        printf("\nAresta [%d -> %d] nao existente\n", i, j);
}

int numero_arestas(int **grafo, int n) {
    int num_arestas = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grafo[i][j] != 0) {
                num_arestas++;
            }
        }
    }
    
    return num_arestas;
}

int verificar_vizinhos(int **grafo, int n, int vertice) {
    if (vertice > n)
        return 0;
    
    int num_vizinhos = 0;

    printf("\nVizinhos de V%d: ", vertice);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != vertice-1 && j == vertice-1 && grafo[i][j] != 0) {
                printf("(V%d) ", i+1);
                num_vizinhos++;
            }
        }
    }
    
    return num_vizinhos;
}

int grau_vertice(int **grafo, int n, int vertice) {
    if (vertice > n)
        return 0;

    int grau = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == vertice-1 || j == vertice-1) && (grafo[i][j] != 0))
                grau++;
        }
    }

    return grau;
}

int numero_vertices(int **grafo, int n) {
    int num_vertices = 0;

    printf("\nVertices: ");
    for (int i = 1; i <= n; i++) {
        if (grau_vertice(grafo, n, i) != 0) {
            num_vertices++;
            printf("(V%d) ", i);
        }
    }
    
    return num_vertices;
}


int main() {
    int **grafo;
    int n;

    printf("Dimensao do Grafo: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Dimensao invalida\n");
        exit(1);
    }

    grafo = inicializar_grafo(n);

    adicionar_aresta(grafo, n, 1, 2, 2);
    adicionar_aresta(grafo, n, 2, 3, 4);
    adicionar_aresta(grafo, n, 3, 1, 12);
    adicionar_aresta(grafo, n, 4, 2, 3);
    adicionar_aresta(grafo, n, 5, 4, 8);
    adicionar_aresta(grafo, n, 3, 5, 40);

    imprimir_grafo(grafo, n);

    verificar_existencia_aresta(grafo, n, 5, 3);

    remover_aresta(grafo, n, 3, 5);
    remover_aresta(grafo, n, 3, 1);

    imprimir_grafo(grafo, n);

    verificar_existencia_aresta(grafo, n, 3, 3);

    printf("\nNumero de Arestas: %d\n", numero_arestas(grafo, n));

    for (int i = 1; i <= n; i++) {
        printf("\nNumero de vizinhos: %d\n", verificar_vizinhos(grafo, n, i));
    }

    for (int i = 1; i <= n; i++) {
        printf("\nGrau do vertice %d: %d\n", i, grau_vertice(grafo, n, i));
    }
    
    printf("\nNumero de vertices: %d\n", numero_vertices(grafo, n));

    liberar_memoria(grafo, n);

    return 0;
}