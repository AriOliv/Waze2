#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#define INFINITO 10000
#define INDEFINIDO -1
using namespace std;


void print(vector<int> vetor){
    for(auto value: vetor){
         cout << value << endl;
    }
}

template<typename T>
void print(T words){
    cout << words << endl;
}

void print(int arr[], int length){ 
    for (int i = 0; i < length; i++)
    {
        cout << i << " = " <<arr[i]<< endl;
    }
}


// referencia para este código
// https://www.geeksforgeeks.org/graph-and-its-representations/
struct Edge
{
public:
    int id_to;
    int length;
    Edge(int id_to, int length)
    {
        this->id_to = id_to;
        this->length = length;
    }
};

// struct temporaria: adiconar distancias a priority queue
struct Dist{
    public:
    int para;
    int de;
    int distancia;
    Dist(int de, int para, int distancia)
    {
        this->de = de;
        this->para = para;
        this->distancia = distancia;
    }
};

// Estrutura do Nó
struct Node
{
    // Armazenando id do nó
    int id;
    //Longitude do nó
    double x;
    // Latitude do nó
    double y;
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

// classe criada temporariamente: argumento comparativo da priority_queue
class ComparaVelocidadeRota{
    public:
    int operator() (const Dist& p1, const Dist& p2){
        return p1.distancia > p2.distancia ;
    }
};

class Graph
{
public:
    // Vector em que serão armazenados todos os nós do grafo
    vector<Node> graph_list;
    // Construtor
    Graph()
    {
        // Carregando todos os nós e grafos na estrutura
        loadNodes();
        loadEdges();
    }

    // Função que carrega todos os nós na estrutura a partir de um csv
    void loadNodes()
    {
        ifstream NodeFile;
        NodeFile.open("../arquivos_grafo/Nodes.csv");
        string line;
        string cell;
        int id;
        double x;
        double y;
        int count;
        int count_row = 0;
        while (getline(NodeFile, line))
        {
            stringstream row(line);
            count = 0;
            while (getline(row, cell, ';'))
            {
                if (count_row == 0)
                {
                }
                else if (count == 0)
                {
                    id = stoi(cell);
                }
                else if (count == 1)
                {
                    y = stod(cell);
                }
                else if (count == 2)
                {
                    x = stod(cell);
                }
                count++;
            }
            if (count_row != 0)
            {
                (this->graph_list).push_back(Node(id, x, y));
            }
            count_row++;
        }
        NodeFile.close();
    }

    // Função que adiciona uma aresta ao vector neighbours do Nó
    void addEdge(int id_from, int id_to, int length)
    {
        (this->graph_list[id_from]).neighbors.push_back(new Edge(id_to, length));
    }
    // Função que carrega várias arestas
    void loadEdges()
    {
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
        while (getline(EdgeFile, line))
        {
            stringstream row(line);
            count = 0;
            while (getline(row, cell, ';'))
            {
                if (count_row == 0)
                {
                }
                else if (count == 0)
                {
                    id_from = stoi(cell);
                }
                else if (count == 1)
                {
                    id_to = stoi(cell);
                }
                else if (count == 2)
                {
                    length = stof(cell);
                }
                count++;
            }
            if (count_row != 0)
            {
                addEdge(id_from, id_to, length);
            }
            count_row++;
        }
    }

    // Função que printa cada nó e seus vizinhos
    void printGraph()
    {
        for (auto graph : this->graph_list)
        {
            cout << graph.id;
            for (auto node : graph.neighbors)
            {
                cout << " -> " << node->id_to;
            }
            cout << endl;
        }
    }
    // função retorna o número de nós no grafo
    int size(){
        int size = 0;
        for(Node no: graph_list){
            size++;
        }
        return size;
    }

    Node *find_node_by_id(int id)
    {
        return &this->graph_list[id];
    }

    // Essa função calcula a distância euclidiana entre dois pontos
    double euclidean_distance(double y1, double x1, double y2, double x2)
    {
        return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5)*pow(10,5);
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

    // bool is_in(){}

    // Dado o id de dois nós, é calculada a distancia
    double euclidean_distance_by_id(int id1, int id2)
    {
        Node *node1 = find_node_by_id(id1);
        Node *node2 = find_node_by_id(id2);
        return euclidean_distance(node1->y, node1->x, node2->y, node2->x);
    }


    int find_lowest_f(vector<int> open_list){
        int id_minimum = open_list[0];
        int minimum_f=find_node_by_id(open_list[0])->f;
        int temp_f;
        for(int id: open_list){
            // print(id);
            temp_f = find_node_by_id(id)->f;
            if(temp_f<=minimum_f){
                minimum_f=temp_f;
                id_minimum = id;
            };
        }
        return id_minimum;
    }
    
    // Nessa função será executao o algoritmo principal
    // O shortest path com A*
    void shortest_path(double y1, double x1, double y2, double x2)
    {
        // Aqui, desejei inserir somente o id de cada no
        // Talvez de outra froma seja menos eficiente
        vector<int> open_list;
        vector<int> closed_list;
        Node start_node = *find_node_by_coordinate(y1, x1);
        Node end_node = *find_node_by_coordinate(y2, x2);
        Node current_node = start_node;
        // cout << "No incial: " << start_node.id << endl;
        double h = euclidean_distance(y1, x1, y2, x2);
        double g = 0;
        double f = h + g;
        start_node.f = f;
        int count = 0;

        // Iterando todos os nós

        while (current_node.id != end_node.id)
        {
            // print("Vizinhos:");
            // Iterando todos os vizinhos do Nó
            for (auto neighbor : current_node.neighbors)
            {   
                // print(neighbor->id_to);
                // cout << "Length ";
                // Veirificando se um item pertence a open list
                bool is_in_close_open = find(open_list.begin(), open_list.end(), neighbor->id_to) != open_list.end();
                is_in_close_open = is_in_close_open || find(closed_list.begin(), closed_list.end(), neighbor->id_to) != closed_list.end();

                if (!is_in_close_open)
                {
                    // Adicionando o vector a open list
                    open_list.push_back(neighbor->id_to);
                    // ditancia de no anterior ate o seu no adjacente
                    g = neighbor->length+current_node.f;
                    h = euclidean_distance_by_id(end_node.id, neighbor->id_to);
                    f = g + h;
                    Node* adjacent_node = find_node_by_id(neighbor->id_to);
                    
                    if (adjacent_node->f < f)
                    {
                    adjacent_node->f = f; 
                    adjacent_node->previous_node_id = current_node.id;
                    // Set parent to be the current vertex
                    }
                    // cout << adjacent_node->f << endl;
                }
            };
            closed_list.push_back(current_node.id);
            int previous_node_id = current_node.id;
            current_node = *find_node_by_id(find_lowest_f(open_list));
            remove(open_list.begin(), open_list.end(), find_lowest_f(open_list));
            count ++;
            
            // if (count == 100){
            //     break;
            // }
        };
        // Reconstruindo o shortest path
        // cout << start_node  .id << endl;
        // cout << current_node.id << endl;
        // cout << end_node.id << endl;
        // if(current_node.id == end_node.id){
            int current_id = current_node.id;
            count = 1;
            current_node = *find_node_by_id(current_id);
            // cout << "Content-type:text/html \n\n";
            cout << "[";
            // cout << "{x:"<< current_node.x <<",y:"<< current_node.y << "}";
            cout << "{x:"<< current_node.x <<",y:"<< current_node.y << "}";
            while (current_node.id != start_node.id)
            {
                current_node = *find_node_by_id(current_node.previous_node_id);
                cout <<","<< "{x:" << current_node.x << ",y:"<<current_node.y<< "}";
                // cout << current_node.id << endl;
                count ++;
            }
            cout << "]";
        }

    // }

void dijkstra(double y1, double x1, double y2, double x2, bool caminhos=false){
        priority_queue <Dist, vector<Dist>, ComparaVelocidadeRota > priorityqueue;
    
        vector<int> short_path;
        Node start_node = *find_node_by_coordinate(y1, x1);
        Node end_node = *find_node_by_coordinate(y2, x2);
        Node current_node = start_node;

        int size = this->size();
        vector<int> dist; // armazena as distancias
        vector<int> prev;  // armazena os nós visitados 
        vector<int> dist2;
        int alt;
        vector<bool> done;
        int contador = 0; 
   
        for (Node vertice: this->graph_list){

            if (vertice.id != start_node.id){
                dist.push_back(INFINITO); // todos os nós recebem distancia infinito
                prev.push_back(INDEFINIDO); // todos os nós recebem prev indefinido
                done.push_back(false);
                dist2.push_back(0);
            }
            else{
                dist.push_back(0);
                done.push_back(false);
                dist2.push_back(0);
                prev.push_back(-1);
            }
            
            if(dist[vertice.id] < 0){
                // print("Achei o bug");
                // print(start_node.id);
                // print(vertice.id);
                priorityqueue.push(Dist(vertice.id,start_node.id, INFINITO));
            }else{
                
                priorityqueue.push(Dist(vertice.id,start_node.id, dist[vertice.id]));
            }
        }
         dist[start_node.id] = 0; // a dist do nó inicial para ele mesmo é zero
         done[start_node.id] = true;
        
        int count =0;
        while(!priorityqueue.empty()){
            // if(count==100) break;
            // count++;
            Dist u = priorityqueue.top();
            // cout << "Priority:" << " " << u.de<< " "<< u.para << endl;
            // print(u.distancia);
            current_node = *find_node_by_id(u.para);
            priorityqueue.pop();
            
            // cout << "a ";
            // print("-----------");
            for (auto neighbor : current_node.neighbors){
                // print(neighbor->id_to);
              alt = dist[current_node.id] + neighbor->length;
                

              if (!done[neighbor->id_to]  && alt < dist[neighbor->id_to]){
                //   print("Executou aqui dentro");
                //   print(alt);
                // cout <<"Vendo o vizinho: " << neighbor->id_to << endl;
                  dist[neighbor->id_to] = alt;
                  prev[neighbor->id_to] = current_node.id;
                  priorityqueue.push(Dist(current_node.id,neighbor->id_to,alt));
                //   print("oi");
                  if(neighbor->id_to == 72){
                    //   print("Piu");
                  }
              }    
            }
            done[current_node.id] = true;
            // print("");
        }
        // cout << "Aqui: " << current_node.id << " " << end_node.id << endl;
        // print(dist, size);
        // print(prev[end_node.id]); 
        // if (prev[end_node.id] != INDEFINIDO){
        //     current_node = end_node;
        //     while(current_node.id != start_node.id){
        //         short_path.push_back(current_node.id);
        //         current_node = *find_node_by_id(prev[current_node.id]);
        //         cout << ",{y:"<< current_node.y <<",x:"<< current_node.x << "}";
        //     }
        // }

        if (prev[end_node.id] != INDEFINIDO){
            current_node = end_node;
            while(current_node.id != start_node.id){
                short_path.push_back(current_node.id);
                current_node = *find_node_by_id(prev[current_node.id]);
                cout << ","<< current_node.id;
            }
            
        }

    }    
};


int main()
{
    Graph GF = Graph();
    // GF.printGraph();
    string pontos = getenv("QUERY_STRING");
    // // cout<<"Content-type:text/html \n\n";
    cout << "Content-Type: application/json\r\n\r\n";
    string delimeter = ";";
    double y1 = stod(pontos.substr(0,pontos.find(";")));
    pontos.erase(0,pontos.find(delimeter)+delimeter.length());
    
    double x1 = stod(pontos.substr(0,pontos.find(";")));
    pontos.erase(0,pontos.find(delimeter)+delimeter.length());
    
    double y2= stod(pontos.substr(0,pontos.find(";")));
    pontos.erase(0,pontos.find(delimeter)+delimeter.length());
    double x2 = stod(pontos.substr(0,pontos.find(";")));
    // GF.shortest_path(y1, x1, y2, x2);
    cout << "[";
    // cout <<"{y:" << y2 << ",x:" << x2 <<"}";
    cout << GF.find_node_by_coordinate(y2,x2)->id;
    GF.dijkstra(y1, x1, y2, x2);
    cout << "]";
}
