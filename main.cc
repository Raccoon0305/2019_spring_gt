/*
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include <vector>
#include <map>
#include <stack>
#include <string>
using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
NetworkManager *bicli = new NetworkManager();

int main(int argc, char** argv){

    nm->interpret("graph_in.txt");
   // nm->print_all_e();
   // nm->print_all_v();


    /*check every nodes, whether their in_degree=out_degree or not*/
    Vertex *node = nm->get_all_nodes();
    vector<int> in_degree,out_degree;
    Vertex *current=node;
    int num_to_match=0;
    vector<string> trace;
    vector<Vertex *> node_vlist;

    while(current!=0){
       node_vlist.push_back(current);
       current=current->next;
       
    }
    int c_in_d=0, c_out_d=0;
    for(int i=0;i<node_vlist.size();i++){
       for(int j=0;j<node_vlist.size();j++){
          if(i!=j){
             if(nm->connected_d(node_vlist[i]->name,node_vlist[j]->name)){c_out_d++;}
             if(nm->connected_d(node_vlist[j]->name,node_vlist[i]->name)){c_in_d++;}   
          }
       }
       in_degree.push_back(c_in_d);
       out_degree.push_back(c_out_d);
       c_in_d=0;
       c_out_d=0;
    }
    vector<string> outer,inter;
    for(int i=0;i!=in_degree.size();i++){
       if(in_degree.at(i)>out_degree.at(i)){
            inter.push_back(node_vlist.at(i)->name);
            num_to_match++; 
       }
       else if(in_degree.at(i)<out_degree.at(i)){
            outer.push_back(node_vlist.at(i)->name);
            num_to_match++;
       }
    }
 
//Build a biclique graph which all the edges of it present the minimun length from a inter(in_degree>out_degree) to an 
//outer(out_degree>in_degree).
    
    Path *cur_path=new Path();
    cur_path->append(nm->elist);
    vector<vector<Edge *>> cur_paths;
    map<Edge *,vector<Edge *>> choosed_paths;
    int min_path;
    float  cur_length=0;
    float  min_len=10000;
       
    if(inter.size()!=outer.size()){
         cout<<"Can't find answer on this graph";
         return 0;//checker,the answer can be found only if inter number= outer number.
    }
    else if(!outer.empty() && !inter.empty()){
//find the shortest path from each inter to each outer.
      for(int i=0;i<inter.size();i++){
         for(int j=0;j<outer.size();j++){
           cur_paths= cur_path->find_paths(outer.at(j),inter.at(i));
           cur_path->debug();
           if(cur_paths.at(0).size()==0){
              cout<<"This graph is not strongly connected"<<endl;
              return 0; //checker
           } 
           for(int k=0;k<cur_paths.size();k++){
              for(int l=0;l<cur_paths.at(k).size();l++){
                 cur_length=cur_length +(cur_paths.at(k).at(l))->cap;
              }
              if(cur_length<min_len){
                 min_len=cur_length;
                 min_path=k;
              }
           }
           
           //as find the shortest path, add an edge which its weight(flowval)=the sum of the edges' weight
           bicli->add_switch(inter.at(i));
           bicli->add_switch(outer.at(j));
           bicli->connect(outer.at(j),inter.at(i));
           bicli->setlink(outer.at(j),inter.at(i),0,min_len);
           bicli->setlink(outer.at(j),inter.at(i),1,1);
           Edge *e= bicli->get_edge(outer.at(j),inter.at(i));
           
           choosed_paths.insert(pair<Edge *,vector<Edge *>>(e,cur_paths.at(min_path)));//record the relationship between edge in biclique and the orinal path
           cur_length=0;
           min_len=10000;
             
         }   
      }   
   in_degree.clear();
   out_degree.clear();
     
//   bicli->print_all_e();
   
 // Matching 
    
   Edge *c_edge = bicli-> elist;
   Edge *min_edge = c_edge;   
   vector<Edge *> choosed_edges;
   vector<string> matched_v;
   while(num_to_match!=0){
    while(c_edge!=NULL){
       if((c_edge->cap < min_edge->cap)&&(find(matched_v.begin(),matched_v.end(),c_edge->head->name)==matched_v.end())&&(find(matched_v.begin(),matched_v.end(),c_edge->tail->name)==matched_v.end()))
        {
            min_edge=c_edge;//greedy,find the edge with smallest value and connect 2 unmatched vertices.
        }
        c_edge=c_edge->next; 
    }
    choosed_edges.push_back(min_edge);
    min_edge->flowval=0;
    matched_v.push_back(min_edge->head->name);
    matched_v.push_back(min_edge->tail->name);//Record matched vertex in the matched_v
    num_to_match=num_to_match-2;
   }
   
   for(int i=0;i<choosed_edges.size();i++){
	      for(int j=0;j<choosed_paths[choosed_edges.at(i)].size();j++){
		 nm->setlink(choosed_paths[choosed_edges.at(i)].at(j)->head->name,choosed_paths[choosed_edges.at(i)].at(j)->tail->name,1,choosed_paths[choosed_edges.at(i)].at(j)->flowval+1);//copy edges which will be walked twice to nm
      }
   }
   
  choosed_edges.clear();
  matched_v.clear();


  }//end if  
   
  nm->print_all_e();  
  /* 
  Gplot *plot = new Gplot();
  plot->gp_add(nm->elist);
  plot->gp_dump(true);
  plot->gp_export("plot");  
  */
  inter.clear();
  outer.clear();
    
  
    //Use Heirholzer algorithm to solve
   
  Edge *el = nm->elist;
  string start = el->head->name;
  
   
  
  Vertex *v_start = node;
  string c_v;
  stack<string> S;
  S.push(start);
  Vertex *current_v = v_start;
  Edge *e_c;
  bool dead = 1;  
 //////////////////////////////////////////////////////////////////////////////////////////////////

  while(!S.empty()){
        
	c_v = S.top();
	while(current_v!=NULL){
          if((c_v != current_v->name)&&(e_c = nm->get_edge(c_v,current_v->name))&&(e_c->flowval>0)){           
              
              
            
                nm->setlink(c_v,current_v->name,1,e_c->flowval-1);
                S.push(current_v->name);
                dead = 0;                   
                break;
              
           }
                       
           current_v = current_v->next;
         }
         if(dead){
           trace.push_back(S.top());
           S.pop();
           
         }
         else
           dead = 1; 
         current_v = v_start ;  
 }    
  
   
  //print out the result 
  ofstream outfile;
  outfile.open("output.txt");
  bool check_it = 1;
  if(trace.back()==start){check_it = 0;}
  string last_node=trace.back();
  trace.pop_back();
  
  while(!trace.empty()){
    outfile<<last_node<<"->"<<trace.back()<<endl;
    last_node = trace.back();
    trace.pop_back();
    
  }
  if(check_it){outfile<<last_node<<"->"<<start<<endl;}
  outfile.close(); 
  
  
    
    
  return 0;
}



