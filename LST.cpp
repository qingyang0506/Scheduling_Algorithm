// #include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<map>

using namespace std;
#define ppi pair<pii,int>
#define pii pair<int,int>
#define x first
#define y second

int n;
priority_queue<ppi,vector<ppi>,greater<ppi>> heap;
int dl[100][100000];//deadline
int cp[100][100000];//computation time 
int rc[100][3];//0:c 1:p 2:d
int curDl[100];
int curCp[100];
int cyctime;
vector<int> v;
vector<char> ans(100);
char ch[100] = {'0','A','B','C','D','E','F','G','H','I','J','K'};

int gcd(int x,int y){
	return (y==0)?x:gcd(y,x%y);
}



int lcm(int a, int b){
    return (a / gcd(a, b)) * b;
}



int lcm(vector<int>& v){
	 int ans = v[0];

	 for(int i=1;i<v.size();i++){
	 	 ans = lcm(ans,v[i]);
	 }

	 return ans;

}

int getSlackTime(int idx){
	 int ans = 0;
	 vector<ppi> v;
	 while(heap.size()){
	 	ppi p = heap.top();
	 	heap.pop();
	 	v.push_back(p);
	 	if(p.y==idx){
	 		ans = p.x.x;
	 	}
	 }

	 for(int i=0;i<v.size();i++){
	 	heap.push(v[i]);
	 }

	 return ans;
}

void print(int time, int curCp[100],char ch){

     cout << time << "\t";

     for(int i=1;i<=n;i++){
     	 int t = getSlackTime(i);
     	 if(t){
     	 	cout << curCp[i] << "\t\t";
     	    cout << getSlackTime(i) << "\t\t";
     	 }else{
     	    cout << "-" << "\t\t";
     	    cout << "-"<< "\t\t";
     	 }
     }

     cout << ch << endl;

}

int main(){

	cout << "Please enter the number of process: " << endl;

	cin >> n;

	cout << "Enter each process c,p,d in order: " << endl;

	for(int i=1;i<=n;i++){
		cout << "Process " << i << " c,p,d are(enter three values in order): " << endl;
		cin >> rc[i][0] >> rc[i][1] >> rc[i][2];
		v.push_back(rc[i][1]);
	}

	cyctime = lcm(v);


	cout << "Time\t";
	for(int i=1;i<=n;i++){
		printf("%c comp time\t",ch[i]);
		printf("%c slack time\t",ch[i]);
	}

	cout << "schedule" << endl;

	for(int i=1;i<=n;i++){

         int deadline = rc[i][2];
         int computation = rc[i][0];

         for(int j=0;j<cyctime;j+=deadline){
         	  dl[i][j] = j+deadline;
         	  cp[i][j] = computation;
         }
	}
    

	for(int i=0;i<cyctime;i++){
        
        for(int j=1;j<=n;j++){
            if(dl[j][i]){
            	curDl[j] = dl[j][i];
            }

            if(cp[j][i]){
            	curCp[j]+=cp[j][i];
            	heap.push({{rc[j][2]-curCp[j],0},j});
            }
        }
        
        if(heap.size()==0){
        	ans[i] = ch[0];
        	print(i,curCp,ans[i]);
        	continue;
        }
		ppi p = heap.top();
		int pid = p.y;
		ans[i] = ch[pid];
		print(i,curCp,ans[i]);
		heap.pop();
		curCp[pid]--;

        //当前没有执行的进程的slack time全部-1
        vector<ppi> tt;
        while(heap.size()){
        	ppi tp = heap.top();
        	heap.pop();
        	tt.push_back({{tp.x.x-1,tp.x.y},tp.y});
        }

        for(int i=0;i<tt.size();i++){
        	heap.push(tt[i]);
        }
	    if(curCp[pid]){
	    	//处理当优先级一样时，不能去抢占
	        vector<ppi> vt;
	    	while(heap.size()){
                ppi pt = heap.top();
                heap.pop();
                vt.push_back({{pt.x.x,0},pt.y});
	    	}
	    	for(int i=0;i<vt.size();i++){
	    		heap.push(vt[i]);
	    	}
	    	heap.push({{p.x.x,-1},pid});
	    }
	}

	// for(int i=0;i<cyctime;i++){
	// 	 printf("Time %d: %c\n",i,ans[i]);
	// }

	return 0;
}