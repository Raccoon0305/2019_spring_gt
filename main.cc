/* 
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include <vector>
#include <string>
#include <queue>
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
    cur_path.append(nm->elist);
    vector<vector<Edge *>> cur_paths;
    map<Edge *,vector<Edge *>> choosed_paths;
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
          
           bicli.add_switch(inter.at(i));
           blcli.add_switch(outer.at(j));
           bicli.connect(inter.at(i),outer.at(j));
           bicli.setlink(inter.at(i),outer.at(j),1,min_len);
           Edge *e= bicli.get_edge(inter.at(i),outer(j));
           e->tag="notused";
           choosed_paths.insert(pair<Edge *,vector<Edge *>>(e,*min_path))
           cur_length=0;
           min_len=10000;
             
         }   
      }
    
 // Matching 
   Edge *c_edge = bicli->elist;
   Edge *min_edge = c_edge;
   vector<Edge *> choosed_edges;
  // vector<Vertex *> matched_v;
   while(!inter.empty&& !outer.empty){
    while(c_edge!=0){
       if((c_edge->flowval < min_edge->flowval)&&(c_edge->tag=="notused")&&(find(inter.begin(),inter.end(),c_edge->head->name)!=inter.end())&&(find(outer.begin(),outer.end(),c_edge->tail->name)!=inter.end()))
        {
            min_edge=c_edge;
        } 
    }
    choosed_edges.pushback(min_edge);
    inter.erase(min_edge->head->name);
    outer.erase(min_edge->tail->name);
   }
   
   for(vecter<Edge *>::iterator it_e=choosed_edges.begin();it_e!=choosed_edges.end();it_e++){
      for(vector<Edge *>::iterater p_it = choosed_paths[it_e].begin();p_it != choosed_paths[it_e].end();p_it++){
         //copy every edges on the path in nm
      }
   }
   

  }//end if  
   
    
   return 0;
}
