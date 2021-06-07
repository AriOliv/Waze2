// #include "graph.cpp"
#include "auxiliares.cpp"
#include <queue>

#define INFINITO 10000
#define INDEFINIDO -1


// struct temporaria: adiconar distancias a priority queue
struct Dist{
    public:
        int para;
        int de;
        int distancia;
    Dist(int de, int para, int distancia){
        this->de = de;
        this->para = para;
        this->distancia = distancia;
    }
};


// classe criada temporariamente: argumento comparativo da priority_queue
class ComparaVelocidadeRota{
    public:
        int operator() (const Dist& p1, const Dist& p2){
            return p1.distancia > p2.distancia ;
    }
};

   

void Graph::dijkstra(double y1, double x1, double y2, double x2){

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

        // Adicionando uma vez a amis para dar bug
        // dist.push_back(INFINITO); // todos os nós recebem distancia infinito
        // prev.push_back(INDEFINIDO); // todos os nós recebem prev indefinido
        // done.push_back(false);
        // dist2.push_back(0);      
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
                print("Achei o bug");
                print(start_node.id);
                print(vertice.id);
                priorityqueue.push(Dist(vertice.id,start_node.id, INFINITO));
            }else{
                
                priorityqueue.push(Dist(vertice.id,start_node.id, dist[vertice.id]));
            }
        }
         dist[start_node.id] = 0; // a dist do nó inicial para ele mesmo é zero
         done[start_node.id] = true;
        
        int count =0;
        while(!priorityqueue.empty()){
            if(count==100) break;
            count++;
            Dist u = priorityqueue.top();
            cout << "Priority:" << " " << u.de<< " "<< u.para << endl;
            print(u.distancia);
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
                cout <<"Vendo o vizinho: " << neighbor->id_to << endl;
                  dist[neighbor->id_to] = alt;
                  prev[neighbor->id_to] = current_node.id;
                  priorityqueue.push(Dist(current_node.id,neighbor->id_to,alt));
                //   print("oi");
                  if(neighbor->id_to == 72){
                      print("Piu");
                  }
              }    
            }
            done[current_node.id] = true;
            print("");
        }
        // cout << "Aqui: " << current_node.id << " " << end_node.id << endl;
        // print(dist, size);
        // print(prev[end_node.id]);
        
        if (prev[end_node.id] != INDEFINIDO){
            current_node = end_node;
            print("Entrou");
            print(current_node.id);
            print(start_node.id);
            while(current_node.id != start_node.id){
                print("E executou o while");
                short_path.push_back(current_node.id);
                current_node = *find_node_by_id(prev[current_node.id]);
                cout << "{x:"<< current_node.x <<",y:"<< current_node.y << "}";
            }

        }
};

