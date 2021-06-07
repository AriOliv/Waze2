// #include <stdio.h>
// #include <bits/stdc++.h>
// #include <algorithm>

#include "graph.cpp"
#include "dijkstra.cpp"
#include "A_star.cpp"

int main()
{
    Graph GF = Graph();
    // GF.printGraph();
    // string pontos = getenv("QUERY_STRING");
    // // // cout<<"Content-type:text/html \n\n";
    // cout << "Content-Type: application/json\r\n\r\n";
    // string delimeter = ";";
    // double y1 = stod(pontos.substr(0,pontos.find(";")));
    // pontos.erase(0,pontos.find(delimeter)+delimeter.length());
    
    // double x1 = stod(pontos.substr(0,pontos.find(";")));
    // pontos.erase(0,pontos.find(delimeter)+delimeter.length());
    
    // double y2= stod(pontos.substr(0,pontos.find(";")));
    // pontos.erase(0,pontos.find(delimeter)+delimeter.length());
    // double x2 = stod(pontos.substr(0,pontos.find(";")));
    
    double y1 = -1.890491;
    double x1 =  -55.127600;
    
    double y2 = -1.889829;
    double x2 = -55.125386;
    // print(GF.find_node_by_coordinate(y2,x2)->id);
    // // print(GF.find_node_by_coordinate(y1,x1)->id);
    // print("------ Start and End Node ------");
    // print(GF.find_node_by_coordinate(y1,x1)->id);
    // print(GF.find_node_by_coordinate(y2,x2)->id);
    // print("--------------------------------");
    GF.shortest_path(y1, x1, y2, x2);
   
    
    // GF.shortest_path(y1, x1, y2, x2);

    // cout << GF.euclidean_distance(-1.892500, -55.132748, -1.8894025, -55.107615);
    //  GF.find_node_by_coordinate(-1.892055, -55.126381);
    // cout << GF.euclidean_distance_by_id(1,2);
}