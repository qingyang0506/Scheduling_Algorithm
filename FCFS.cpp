// #include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<map>


using namespace std;

int f[100];
int cnt[100];

int main(){

	int n;


	cout << "Please enter the number of the process?"<< endl;

	cin >> n;

    cout <<"Enter each process burst time: " << endl;
    for(int i=1;i<=n;i++){
    	cout << "Process "<<i << ":" ;
    	cin >> f[i];
    }


    int time = 0;
    int sum = 0;

    for(int i=1;i<n;i++){
    	
        cnt[i] = time;
        time+=f[i];
        sum+=time;
    }

    cnt[n] = time;

    cout << "the total waiting time is:" << sum << endl;
    // cout << "the average waiting time is:" << time*1.0/n*1.0 << endl;

    printf("the average waiting time is:%lf\n",sum*1.0/n);

    for(int i=1;i<=n;i++){
        cout << "Process " << i << "waiting time is: " << cnt[i] << endl;
    }

	return 0;
}