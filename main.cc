/* 
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include <vector>
#include <string>
using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
NetworkManager *bicli = new NetworlManager();
int main(int argc, char** argv){

    nm.intrepret(fin);
    /*check every nodes, whether their in_degree=out_degree or not*/
    Vertex *node = nm.get_all_nodes();
    vector<Vertex *> node_vlist;
    vector<int> in_degree,out_degree;
    Vertex *current=node;
   
    while(current!=0){
       node_vlist.pushback(current);
       current=current->next;
       
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
    vector<string> outer,inter;
    for(int i=0;i!=in_degree.size();i++){
       if(in_degree.at(i)>out_degree.at(i)){inter.pushback(node_vlist.at(i)->name);}
       else if(in_degree.at(i)<out_degree.at(i)){outer.pushback(node_vlist.at(i)->name);}
    }
 
//Build a biclique graph which all the edges of it present the minimun length from a inter(in_degree>out_degree) to an 
//outer(out_degree>in_degree).
    
    Path *cur_path=new Path();
    vector<vector<Edge *>> cur_paths;
    map<string,vector<Edge *>> choosed_paths;
    vector<Edge *>::iterator min_path;
    float  cur_lentgh=0;
    float  min_len=10000;
    

    if(!outer.empty() && !inter.empty()){
      for(int i=0;i<inter.size();i++){
         for(int j=0;j<outer.size();j++){
           cur_paths= cur_path.find_path(inter.at(i),outer.at(j));
           for(vector<vector<Edge *>>::iterator it_i=cur_paths.begin();it_i!=cur_paths.end();it_i++){
              for(vector<Edge *>::iterator i=it_i.begin();i!=it_i.end();i++){
                 cur_length=cur_length+i->flowval;
              }
              if(cur_length<min_len){
                 min_len=cur_length;
                 min_path=it_i
              }
           }
           choosed_paths.insert(pair<string,vector<Edge *>>(inter.at(i),*min_path))
           bicli.add_switch(inter.at(i));
           blcli.add_switch(outer.at(j));
           bicli.connect(inter.at(i),outer.at(j));
           bicli.setlink(inter.at(i),outer.at(j),1,min_len);
           cur_length=0;
           min_len=10000;
             
         }   
      }
    }
  
    return 0;
}
