#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin>>n;
	vector<int> arr(n);
	for(auto &it : arr)cin>>it;

	vector<vector<int>> pref(n,vector<int>(n+1,0));
	for(int i=0;i<n;i++){
		pref[i][arr[i]]=1;
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=n;j++){
			pref[i][j]+=pref[i-1][j];
		}
	}
	int ans=0;
	for(int i=1;i<n-1;i++){
		for(int j=i+1;j<n-1;j++){
			int c1=pref[i-1][arr[j]];
			int c2=pref[n-1][arr[i]]-pref[j][arr[i]];
			// Find count of arr[j] leftside, arr[i] rightside
			ans+=(c1*c2);
		}
	}
	cout<<ans<<endl;
}
