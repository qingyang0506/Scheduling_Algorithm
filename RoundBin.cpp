// #include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<cstring>
#include<vector>


using namespace std;
#define pii pair<int,int>
#define x first
#define y second

int n,m;
queue<pii> q;
int f[100];
int cnt[100];

int main(){

	cout << "Please enter the total process:" << endl;

    cin >> n;

    cout << "Please enter the time slice:" << endl;

    cin >> m;

    cout <<"Enter each process burst time: " << endl;
    for(int i=1;i<=n;i++){
    	cout << "Process " << i << ":";
    	cin >> f[i];
    	q.push({i,0});
    }


    int sum = 0;
    int time = 0;


    while(q.size()){
    	pii p = q.front();
    	q.pop();

        int val = f[p.x];
        
        if(val>m){
        	f[p.x]-=m;
        	time += m;
        	if(time-p.y!=m){
        		sum+=(time-p.y-m);
                cnt[p.x]+=(time-p.y-m);
        	}
        	q.push({p.x,time});

        }else{
        	int tp = f[p.x];
        	f[p.x] = 0;
        	time += tp;
        	if(time-p.y!=tp){
        	     sum+=(time-p.y-tp);
                 cnt[p.x]+=(time-p.y-tp);
        	}
        }
    }


    cout << "the total waiting time is:" << sum << endl;
    printf("the average waiting time is:%lf\n",sum*1.0/n);

    for(int i=1;i<=n;i++){
        cout << "process " << i  << " waiting time is: " << cnt[i] << endl; 
    }

	return 0;
}