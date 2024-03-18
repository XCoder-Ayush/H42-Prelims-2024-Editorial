#include <bits/stdc++.h>
using namespace std;
#define int long long
const int P=31;
const int MOD=1e9+7;

int modexp(int a, int b, int m) {a %= m;int res = 1LL;while (b > 0) {if (b & 1)res = (res%m *1LL* a%m) % m;a = (a%m *1LL* a%m) % m;b >>= 1;}return res%m;}
int modadd(int a,int b,int m){return (a%m+b%m)%m;}
int modsub(int a,int b,int m){return (a%m-b%m+m)%m;}
int modmul(int a,int b,int m){return (a%m*1LL*b%m)%m;}
int modinv(int a,int m){return modexp(a,m-2,m);}
int moddiv(int a,int b,int m){return (a%m*1LL*modinv(b,m)%m)%m;}

int32_t main() {
    int n;
    cin>>n;
    string s;
    cin>>s;
    int q;
    cin>>q;
    vector<int> hash(n+1,0),rhash(n+1,0);
    for(int i=1;i<=n;i++){
        hash[i]=s[i-1]-'a'+1;
    }
    rhash=hash;
    reverse(rhash.begin()+1,rhash.end());

    for(int i=1;i<=n;i++){
        hash[i]=modmul(hash[i],modexp(P,i-1,MOD),MOD);
        rhash[i]=modmul(rhash[i],modexp(P,i-1,MOD),MOD);
    }
    
    for(int i=1;i<=n;i++){
        hash[i]=modadd(hash[i-1],hash[i],MOD);
        rhash[i]=modadd(rhash[i-1],rhash[i],MOD);
    }

    vector<int> queries(q);
    for(auto &it : queries)cin>>it;

    vector<int> res;

    for(auto &it : queries){
        int ind=it;
        int left=ind-1;
        int right=n-ind;
        int mini=min(left,right);
    
        int low=1 , high=mini;
        int ans=0;

        while(low<=high){
            int mid=low+(high-low)/2;
            // [ind-mid,ind-1] [ind+1,ind+mid]
            int hashValue1=modsub(hash[ind+mid],hash[ind],MOD);
            hashValue1=moddiv(hashValue1,modexp(P,ind,MOD),MOD);
            int idx=n-ind+1;            
            int hashValue2=modsub(rhash[idx+mid],rhash[idx],MOD);
            hashValue2=moddiv(hashValue2,modexp(P,idx,MOD),MOD);
            if(hashValue1==hashValue2){
                ans=mid;
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        res.push_back(2*ans+1);
    }
    for(auto &it : res)cout<<it<<endl;
}
