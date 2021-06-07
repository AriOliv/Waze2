// #include "graph.cpp"
#include <bits/stdc++.h>


int Graph::find_lowest_f(vector<int> open_list){

    int id_minimum = open_list[0];
    int minimum_f=find_node_by_id(open_list[0])->f;
    int temp_f;

    for(int id: open_list){
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
void Graph::shortest_path(double y1, double x1, double y2, double x2){

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
        while (current_node.id != end_node.id){

            // print("Vizinhos:");
            // Iterando todos os vizinhos do Nó
            for (auto neighbor : current_node.neighbors){   
    
                // print(neighbor->id_to);
                // cout << "Length ";
                // Veirificando se um item pertence a open list
                bool is_in_close_open = find(open_list.begin(), open_list.end(), neighbor->id_to) != open_list.end();
                is_in_close_open = is_in_close_open || find(closed_list.begin(), closed_list.end(), neighbor->id_to) != closed_list.end();

                if (!is_in_close_open){

                    // Adicionando o vector a open list
                    open_list.push_back(neighbor->id_to);
                    // ditancia de no anterior ate o seu no adjacente
                    g = neighbor->length+current_node.f;
                    h = euclidean_distance_by_id(end_node.id, neighbor->id_to);
                    f = g + h;
                    Node* adjacent_node = find_node_by_id(neighbor->id_to);
                    
                    if (adjacent_node->f < f){

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
        };



