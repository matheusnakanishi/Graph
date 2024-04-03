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
    printf("   ");
    for (int k = 1; k <= n; k++)
        printf("[%d] ", k);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] ", i+1);
        for (int j = 0; j < n; j++) {
            printf("%d   ", grafo[i][j]);
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

void adicionar_aresta(int **grafo, int i, int j, int peso) {
    grafo[i-1][j-1] = peso;
} 

void remover_aresta(int **grafo, int i, int j) {
    grafo[i-1][j-1] = 0;
} 

void verificar_existencia_aresta(int **grafo, int i, int j) {
    if (grafo[i-1][j-1] != 0)
        printf("\nA Aresta de peso %d existe\n", grafo[i-1][j-1]);
    else    
        printf("\nA Aresta nao existe\n");
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

    grafo = inicializar_grafo(n);

    adicionar_aresta(grafo, 2, 4, 8);
    adicionar_aresta(grafo, 1, 2, 2);
    adicionar_aresta(grafo, 4, 1, 4);
    //adicionar_aresta(grafo, 3, 2, 6);
    adicionar_aresta(grafo, 4, 4, 16);
    adicionar_aresta(grafo, 1, 1, 1);
    adicionar_aresta(grafo, 3, 3, 9);

    imprimir_grafo(grafo, n);

    verificar_existencia_aresta(grafo, 3, 3);

    remover_aresta(grafo, 3, 3);

    imprimir_grafo(grafo, n);

    verificar_existencia_aresta(grafo, 3, 3);

    printf("\nNumero de Arestas: %d\n", numero_arestas(grafo, n));

    printf("\nNumero de vizinhos: %d\n", verificar_vizinhos(grafo, n, 1));
    printf("\nNumero de vizinhos: %d\n", verificar_vizinhos(grafo, n, 2));
    printf("\nNumero de vizinhos: %d\n", verificar_vizinhos(grafo, n, 3));
    printf("\nNumero de vizinhos: %d\n", verificar_vizinhos(grafo, n, 4));

    printf("\nGrau do vertice %d: %d\n", 1, grau_vertice(grafo, n, 1));
    printf("\nGrau do vertice %d: %d\n", 2, grau_vertice(grafo, n, 2));
    printf("\nGrau do vertice %d: %d\n", 3, grau_vertice(grafo, n, 3));
    printf("\nGrau do vertice %d: %d\n", 4, grau_vertice(grafo, n, 4));

    printf("\nNumero de vertices: %d\n", numero_vertices(grafo, n));


    liberar_memoria(grafo, n);

    return 0;
}