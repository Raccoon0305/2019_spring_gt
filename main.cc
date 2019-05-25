/* 
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include <vector>
using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
NetworkManager #bicli = new NetworlManager();
int main(int argc, char** argv){

    nm.intrepret(fin);
    /*check every nodes, whether their in_degree=out_degree or not*/
    Vertex *node = nm.get_all_nodes();
    vector<*Vertex> node_vlist;
    vector<int> in_degree,out_degree;
    Vertex *current=node;
    Vertex *next = node->next;
    while(next!=0){
       node_vlist.pushback(current);
       current=next;
       next=current->next; 
    }
    int c_in_d=0, c_out_d=0;
    for(int i=0;i<node_vlist.size();i++){
       for(int j=0;j<node_vlist.size();j++){
          if(i!=j){
             if(nm.connected_d(node_vlist[i]->name,node_vlist[j]->name){c_out_d++;}
             if(nm.connected_d(node_vlist[j]->name,node_vlist[i]->name){c_in_d++;}   
          }
       }
       in_degree.pushback(c_in_d);
       out_degree.pushback(c_out_d);
       c_in_d=0;
       c_out_d=0;
    }  
    return 0;
}
