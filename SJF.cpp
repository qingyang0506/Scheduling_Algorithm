// #include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<map>

using namespace std;
#define pii pair<int,int>
#define x first
#define y second

int n;
priority_queue<pii,vector<pii>,greater<pii>> heap;
int f[100];
int last[100];
map<int,vector<int>> mp;
int cnt[100];


int main(){

	cout << "Please enter the number of process:"<< endl;

	cin >> n;

     cout << "Enter each process arrival time and burst time below: " << endl;
    for(int i=1;i<=n;i++){
    	int a,b;
    	cout << "Process "<<i << ":" << endl;
    	cout << "arrival time:" ;
    	cin >> a;
    	cout << "burst time:";
    	cin >> b;
    	f[i] = b;
    	mp[a].push_back(i);
    	last[i] = a;
    }

    int ans = 0;
    int lastTime = -1;
    for(auto& p:mp){
    	int time = p.x;
    	vector<int> v = p.y;
    	if(lastTime==-1){
    		for(int i=0;i<v.size();i++){
    			int k = v[i];
    			heap.push({f[k],k});
    		}
    	    lastTime = time;
    	}else{

         int diff = time-lastTime;

         while(diff && heap.size()){
            pii p = heap.top();
            heap.pop();
            ans += (lastTime-last[p.y]);
            cnt[p.y]+=(lastTime-last[p.y]);
            if(f[p.y]<=diff){
               lastTime += f[p.y];
               diff -= f[p.y];
               f[p.y] = 0;
            }else{
               f[p.y]-=diff;
               diff = 0;
               lastTime = time;
               last[p.y] = lastTime;
               heap.push({f[p.y],p.y});
            }
         }

         lastTime =  time;

            //放入新的点
         for(int i=0;i<v.size();i++){
    			int k = v[i];
    			heap.push({f[k],k});
    		}
    	}
    }

    // cout << heap.size() << endl;

    while(heap.size()){

    	pii p = heap.top();
    	heap.pop();

    	int idx = p.y;
    	ans += (lastTime-last[idx]);
    	cnt[p.y]+=(lastTime-last[idx]);
    	lastTime+= p.x;
    }
    

    cout << "the total waiting time:" << ans << endl;
    printf("the average waiting time is: %lf\n",ans*1.0/n);

    for(int i=1;i<=n;i++){
    	cout << "process " << i  << " waiting time is: " << cnt[i] << endl; 
    }
    
	return 0;
}