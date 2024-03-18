#include <bits/stdc++.h>
using namespace std;
#define int long long 

int32_t main() {
	int n;
	cin>>n;
	vector<int> arr(n);
	for(auto &it : arr)cin>>it;
	int i=0;
	int ans=0;
	while(i<n){
		int j=i;
		int maxi=-2e9;
		while(j<n){
			if((arr[j]<0 && arr[i]<0) ||(arr[j]>=0 && arr[i]>=0) ){
				maxi=max(maxi,arr[j]);
				j++;
			}else{
				break;
			}
		}
		ans+=maxi;
		i=j;
	}
	cout<<ans<<endl;
}
