#include <vector>
#include <iostream>
#include <fstream>
// #include <string>
#include <sstream>
#include "graph_class.cpp"
using namespace std;


int main(){
    ifstream NodeFile;
    NodeFile.open("Nodes.csv");
    string line;
    string cell;
    int id;
    float x;
    float y;
    int count;
    int count_row=0;
    vector<Node> Nodes;
    while (getline(NodeFile, line))
    {
        stringstream row(line);
        count = 0;
        while (getline(row, cell, ';')){
            if(count_row == 0){
            }
            else if (count==0)
            {   
                id = stoi(cell);
            }
            else if (count==1)
            {
                x = stod(cell);
            }
            else if(count == 2){
                y = stod(cell);
            }   
            count++;
        }

        count_row++;
        Nodes.push_back(Node(id,x,y));
    }
    // NodeFile.close();
    cout << Nodes[69653].id << endl;

    Graph G(69652);

    ifstream EdgeFile;
    EdgeFile.open("Edges.csv");
    line;
    cell;
    int id_from;
    int id_to;
    float length;
    count = 0;
    count_row=0;
    vector<Node> *Edges;
    while (getline(EdgeFile, line))
    {
        stringstream row(line);
        count = 0;
        while (getline(row, cell, ';')){
            if(count_row == 0){
            }
            else if (count==0)
            {   
                id_from = stoi(cell);
            }
            else if (count==1)
            {
                id_to = stoi(cell);
            }
            else if(count == 2){
                length = stof(cell);
            }   
            count++;
        }

        cout << id_from << " " << id_to << " " << length << endl;

        G.addEdge(Nodes[id_from+1], Nodes[id_to+1]);

        if(count_row == 2) break;
        count_row++;
        
    }

    // G.printGraph();
    

    

}