#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

/*
Esse módulo cria as estruturas do Grafo 
- os nós e arestas são carregados a partir do arquivo csv
- métodos auxiliares são criados

Referência: https://www.geeksforgeeks.org/graph-and-its-representations/
*/

struct Edge{
    public:
        int id_to; // id da conexão
        int length; // tamanho da rota (considerando a velocidade)
    // construtor da Aresta
    Edge(int id_to, int length){
            this->id_to = id_to;
            this->length = length;
    }
};

struct Node{

    int id; //id
    double x; //Longitude 
    double y; // Latitude 

    // Vetor no qual estão armazenadas todas as arestas ligadas a aquele nó
    // Essa aresta armazena o nó que está ligado e o tamanho desse nó
    vector<Edge*> neighbors;

    int previous_node_id; 

    // Nessa variável será armazenada a distancia desse nó até o grafo inicial
    // Essa variável só será usada durante o cálculo do shortest path
    double f = 0;
    // Construtor do Nó
    Node(int id, double x, double y)
    {
        this->id = id;
        this->x = x;
        this->y = y;
    }
};

class Graph{
    public:
        // Vector em que serão armazenados todos os nós do grafo
        vector<Node> graph_list;

        // Métodos 
        void shortest_path(double y1, double x1, double y2, double x2);
        int find_lowest_f(vector<int> open_list);
        void dijkstra(double y1, double x1, double y2, double x2);
        
        // Construtor
        Graph(){
            // Carregando todos os nós e grafos na estrutura
            loadNodes();
            loadEdges();
        }

    // Função que carrega todos os nós na estrutura a partir de um csv
    void loadNodes(){

        ifstream NodeFile;
        NodeFile.open("../arquivos_grafo/Nodes.csv");
        string line;
        string cell;
        int id;
        double x;
        double y;
        int count;
        int count_row = 0;
        while (getline(NodeFile, line)){
            
            stringstream row(line);
            count = 0;
            while (getline(row, cell, ';')){
                if (count_row == 0){
                    // pass
                }
                else if (count == 0){
                    id = stoi(cell);
                }
                else if (count == 1){
                    y = stod(cell);
                }
                else if (count == 2){
                    x = stod(cell);
                }
                count++;
            }
            if (count_row != 0){
                (this->graph_list).push_back(Node(id, x, y));
            }
            count_row++;
        }
        NodeFile.close();
    }

    // Função que adiciona uma aresta ao vector neighbours do Nó
    void addEdge(int id_from, int id_to, int length){
        (this->graph_list[id_from]).neighbors.push_back(new Edge(id_to, length));
    }

    // Função que carrega várias arestas
    void loadEdges(){

        ifstream EdgeFile;
        EdgeFile.open("../arquivos_grafo/Edges.csv");
        string line;
        string cell;
        int id_from;
        int id_to;
        double length;
        int count = 0;
        int count_row = 0;
        vector<Node> *Edges;
        while (getline(EdgeFile, line)){

            stringstream row(line);
            count = 0;
            while (getline(row, cell, ';')){

                if (count_row == 0){
                    // pass
                }
                else if (count == 0){
                    id_from = stoi(cell);
                }
                else if (count == 1){
                    id_to = stoi(cell);
                }
                else if (count == 2){
                    length = stof(cell);
                }
                count++;
            }

            if (count_row != 0){
                addEdge(id_from, id_to, length);
            }
            count_row++;
        }
    }

    /*
                    Métodos auxiliares
    */ 

    // Função que printa cada nó e seus vizinhos
    void printGraph(){
        for (auto graph : this->graph_list){

            cout << graph.id;
            for (auto node : graph.neighbors){
                cout << " -> " << node->id_to;
            }
            cout << endl;
        }
    }

     // Função retorna o número de nós no grafo
    int size(){
        int size = 0;
        for(Node no: this->graph_list){
            size++;
        }
        return size;
    }
     // Função retorna o nó dado seu id
    Node *find_node_by_id(int id)
    {
        return &this->graph_list[id];
    }

    // Nessa função será obtido o nó que está mais próximo de uma coordenada
    // Decidi criar essa função pq nem sempre a coordenada que temos para obter um nó é exata
    Node *find_node_by_coordinate(double y, double x)
    {
        Node *nearest_node = &this->graph_list[0];
        double minimun_distance = euclidean_distance((*nearest_node).y, (*nearest_node).x, y, x);
        for (Node itr : graph_list)
        {
            if (euclidean_distance(itr.y, itr.x, y, x) <= minimun_distance)
            {
                *nearest_node = itr;
                minimun_distance = euclidean_distance((*nearest_node).y, (*nearest_node).x, y, x);
            }
        }
        // cout<< endl << nearest_node->id << endl;
        return nearest_node;
    }

    // Essa função calcula a distância euclidiana entre dois pontos
    double euclidean_distance(double y1, double x1, double y2, double x2)
    {
        return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5)*pow(10,5);
    }
    
    // bool is_in(){}

    // Dado o id de dois nós, é calculada a distancia
    double euclidean_distance_by_id(int id1, int id2)
    {
        Node *node1 = find_node_by_id(id1);
        Node *node2 = find_node_by_id(id2);
        return euclidean_distance(node1->y, node1->x, node2->y, node2->x);
    }





};

