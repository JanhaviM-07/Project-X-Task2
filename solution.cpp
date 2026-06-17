#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
#include<fstream>
#include<sstream>

using namespace std;

class cache{
public:
    string name;
    int capacity;
    int latency;
    vector<string>slots;

    cache(string n,int c,int l){
        name=n;
        capacity=c;
        latency=l;
    }
    

    bool ispresent(string block) {
       auto it=find(slots.begin(),slots.end(),block);
       if(it==slots.end())return false;
        return true;
    }

    void insert(string block) {
        if (ispresent(block)) return;
        if (slots.size()>= capacity) {
            slots.erase(slots.begin());
        }
        slots.push_back(block);
    }
    
    void display(){
        cout<<name<<":  [";
        int i,n=slots.size();

        for(i=0;i<n;i++){
            cout<<slots[i];
            if(i<n-1)cout<<",";
            else cout<<"";
        }
        cout<<"]";
    }
};

class cacheHierarchy{
    cache l1,l2,l3;
    int ramLatency;
    public:
    int ramAccessCount;
    cacheHierarchy():l1("L1", 32, 4),l2("L2", 128, 12), l3("L3", 512, 40),ramLatency(200),ramAccessCount(0){}

    int blockAccess(string block){
        if(l1.ispresent(block)){
         cout<<"-> HIT L1";
          return l1.latency;
        }

        cout<<">>MISS L1";

        if(l2.ispresent(block)){
         cout<<">> HIT L2";
          l1.insert(block);
          return l2.latency;
        }

        cout<<">>MISS L2";

        if(l3.ispresent(block)){
          cout<<">> HIT L3";
          l1.insert(block);
          return l3.latency;
        }
        

        cout<<">>MISS L3>> Fetching from RAM";
        l1.insert(block);
        ramAccessCount++;
        return ramLatency;
    }

    void cacheStates(){
        cout<<"\n";
        l1.display();cout<<endl;
        cout<<" ";
        l2.display();cout<<endl;
        cout<<" ";
        l3.display();cout<<endl;
    }
};

struct task{
    string name;
    int burstTime,remainTime;
    vector<string>memReq;
    int idx=0;

  string  memoryRequest(){
    if(memReq.empty())return "NONE";
    return memReq[idx%memReq.size()];
  }
};

class simulator{
    vector<task>tasks;
    cacheHierarchy cache;
    int quantum,totalCycles=0;

    public:
    simulator(int q):quantum(q){}

    void loadTask(string filename){
         ifstream file(filename);
         if(!file.is_open()){
            cout<<"Error, could not open file.."<<filename<<endl;
             return;
         }

         string line;
         while(getline(file,line)){
            if(line.empty())continue;
            stringstream ss(line);
            string token,block;

            task t;
             ss>>token>>t.name>>token>>t.burstTime>>token;
             t.remainTime=t.burstTime;

             while(ss>>block) {
                t.memReq.push_back(block);
             }
            tasks.push_back(t);
         }
     }


     void roundRobin(){
        queue<task>ready;
        for(auto t :tasks)ready.push(t);
          int completedTasks=0;

          while(!ready.empty()){
            task currTask=ready.front();
            ready.pop();
           int time=min(quantum,currTask.remainTime);
           int i;

           for(i=0;i<time;i++){
            totalCycles++;
             string target=currTask.memoryRequest();

             cout<<"cycle "<<totalCycles<<"-Running:"<<currTask.name<<" requesting: "<<target<<endl;
             int penalty=cache.blockAccess(target);
             totalCycles+=penalty-1;
             
              cache.cacheStates();

              currTask.idx++;
              currTask.remainTime--;
           }
           if(currTask.remainTime>0)ready.push(currTask);
           else completedTasks++;
        }

        cout<<"\n=== Final Results === Total Cycles: "<<totalCycles<<" Tasks Completed:"<<completedTasks<<" Scheduler: Round Robin (quantum = "<<quantum<<") RAM Accesses:"<<cache.ramAccessCount<<endl;
     }
};

int main(){
    simulator s(3);
    s.loadTask("input_task2.txt");
    s.roundRobin();

    return 0;
}

