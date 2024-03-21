#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define endl '\n'

int n, l;
vector<vector<int>> g;
vector<int> parent;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    parent[v]=p;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : g[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

vector<int> kahns(vector<int> &indeg,vector<int> values){
    // 0 is the root node, can't be leaf
    vector<int> hash=values;

    queue<vector<int>> q;
    for(int i=1;i<n;i++){
        if(indeg[i]==1)q.push({i,values[i]});
    }

    while(q.size()){
        int node=q.front()[0];
        int currSum=q.front()[1];
        q.pop();

        for(auto &it : g[node]){
            if(it==parent[node]){
                indeg[it]--;
                int newSum=values[it];
                if(currSum>0)newSum+=currSum;
                hash[it]=max(hash[it],newSum);
                if(it!=0 && indeg[it]==1){
                    // It has only upward connection
                    q.push({it,hash[it]});
                }

            }
        }
    
    }
    return hash;
}
bool isPerfectSquare(int n){
    int low=1,high=n/2;
    int ans=low;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(mid*mid<=n){
            ans=mid;
            low=mid+1;
        }else{
            high=mid-1;
        }
    }
    return (ans*ans==n);
}
int32_t main() {
	cin>>n;
    g.resize(n);
	parent.resize(n,0);
	vector<int> indeg(n);
	for(int i=0;i<n-1;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		indeg[u]++;
		indeg[v]++;
	}
	vector<int> values(n);
	for(auto &it : values){
		cin>>it;
	}
    for(auto &it : values){
        it=(isPerfectSquare(it)?1:-1);
    }
    preprocess(0);
    vector<int> ans=kahns(indeg,values);
    int q;
	cin>>q;

    while(q--){
		int u,v;
		cin>>u>>v;
        int _lca=lca(u,v);
        if(_lca==0){
            cout<<0<<endl;
        }else{
            cout<<ans[_lca]<<endl;
        }
	}
}
