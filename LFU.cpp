// C++ program to illustrate
// page faults in LFU

// #include <bits/stdc++.h>
#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;

/* Counts no. of page faults */
int pageFaults(int n, int c, int pages[])
{
	// Initialise count to 0
	int count = 0;

	// To store elements in memory of size c
	vector<int> v;
	// To store frequency of pages
	unordered_map<int, int> mp;

	int i;
	for (i = 0; i <= n - 1; i++) {

		// Find if element is present in memory or not

		vector<int>::iterator it;
        bool flag  = false;
		for(it = v.begin();it!=v.end();it++){
			if(*it==pages[i]){
				flag = true;
				break;
			}
		}

		// If element is not present
		if (!flag) {

			// If memory is full
			if (v.size() == c) {

				// Decrease the frequency
				mp[v[0]]--;

				// Remove the first element as
				// It is least frequently used
				v.erase(v.begin());
			}

			// Add the element at the end of memory
			v.push_back(pages[i]);
			// Increase its frequency
			mp[pages[i]]++;

			// Increment the count
			count++;
		}
		else {

			// If element is present
			// Remove the element
			// And add it at the end
			// Increase its frequency
			mp[pages[i]]++;
			v.erase(it);
			v.push_back(pages[i]);
		}

		// Compare frequency with other pages
		// starting from the 2nd last page				
		int k = v.size() - 2;

		// Sort the pages based on their frequency
		// And time at which they arrive
		// if frequency is same
		// then, the page arriving first must be placed first
		while (mp[v[k]] > mp[v[k + 1]] && k > -1) {
			swap(v[k + 1], v[k]);
			k--;
		}
	}

	// Return total page faults
	return count;
}

/* Driver program to test pageFaults function*/
int main()
{

	// int pages[] = { 1, 3, 7, 1, 2, 4, 3, 5, 6, 4, 6, 7, 2, 1, 5, 1, 6, 4, 1, 7};
	// int n = 20, c = 4;

	int pages[1000];
	int n,c;

	cout << "Please enter the number of frames:" << endl;
	cin >> c;

	cout << "Please enter the number of processes: " << endl;
	cin >> n;

	cout << "Please enter the all process in order: " << endl;

	for(int i=0;i<n;i++){
		cin >> pages[i];
	}


	cout << "Page Faults = " << pageFaults(n, c, pages)
		<< endl;
	cout << "Page Hits = " << n - pageFaults(n, c, pages) << endl;
	return 0;
}

// This code is contributed by rajsanghavi9.
