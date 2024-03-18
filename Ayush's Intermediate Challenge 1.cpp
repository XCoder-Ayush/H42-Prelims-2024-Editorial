#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int N=10000001;
int spf[N+10];
int greater_than[N+10];
int lesser_than[N+10];

int coordinate_assign=0;
unordered_map<int,int> mpp;

void precompute(){
    for(int i=2;i*i<=N;i++){
        if(spf[i]==-1){
            spf[i]=i;
            mpp[i]=coordinate_assign++;
            for(int j=i*i;j<=N;j+=i){
                if(spf[j]==-1)spf[j]=i;
            }
        }
    }

    int assigned=-1;
    for(int i=2;i<=N;i++){
        if(spf[i]==-1){
            spf[i]=i;
            mpp[i]=coordinate_assign++;
        }
        
        if(spf[i]==i)assigned=i;
        lesser_than[i]=assigned;
    }
    for(int i=N;i>=1;i--){
        if(spf[i]==i)assigned=i;
        greater_than[i]=assigned;
    }
}
class SegmentTree{
    public:
    vector<int> seg;
    SegmentTree(int n)
    {
        seg.resize(4*n+1);
    }
    void build(int ind,int low,int high,vector<int> &arr)
    {
        if(low>=high){
            seg[ind]=arr[low];
            return;
        }
        int mid=low+(high-low)/2;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        // Whatever Is The Range Query
        // Here It Is RSQ
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    int query(int ind,int low,int high,int l,int r)
    {
        // No Overlap
        // [low..high] [l..r] OR  [l..r] [low..high] 
        if(high<l || r<low)return 0;
        // Complete Overlap
        if(low>=l && high<=r)return seg[ind];

        int mid=low+(high-low)/2;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(2*ind+2,mid+1,high,l,r);
        return left+right;
    }
    void pointUpdate(int ind,int low,int high,int idx,int val)
    {
        if(low==high){
            seg[ind]+=val;
            return;
        }
        // Update arr[idx] with val
        int mid=low+(high-low)/2;
        if(idx<=mid)pointUpdate(2*ind+1,low,mid,idx,val);
        else pointUpdate(2*ind+2,mid+1,high,idx,val);

        seg[ind]=seg[2*ind+1]+seg[2*ind +2];
    }
};
int main() {
    memset(spf,-1,sizeof(spf));
    memset(lesser_than,-1,sizeof(lesser_than));
    memset(greater_than,-1,sizeof(greater_than));
    precompute();

    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &it : arr)cin>>it;
    int seg_tree_size=mpp.size();
    vector<int> hash(seg_tree_size,0);

    for(auto &it : arr){
        int num=it;
        while(num>1){
            int div=spf[num];
            int cnt=0;
            while(num%div==0){
                num/=div;
                cnt++;
            }
            int coordinate=mpp[div];
            hash[coordinate]+=cnt;
        }
    }

    int q;
    cin>>q;

    SegmentTree st(seg_tree_size);
    st.build(0,0,seg_tree_size-1,hash);
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int idx,val;
            cin>>idx>>val;
            int oldValue=arr[idx];
            // Now Factorise In log(oldValue) time
            // i.e log2(5000000)

            while(oldValue>1){
                int div=spf[oldValue];
                int cnt=0;
                while(oldValue%div==0){
                    oldValue/=div;
                    cnt++;
                }
                int coordinate=mpp[div];
                // Go to coordinate'th index in segment tree and update its value by -cnt;
                // Point Update
                st.pointUpdate(0,0,seg_tree_size-1,coordinate,-1*cnt);
            }

            int newValue=val;
            // Now Factorise In log(newValue) time
            // i.e log2(5000000)
            while(newValue>1){
                int div=spf[newValue];
                int cnt=0;
                while(newValue%div==0){
                    newValue/=div;
                    cnt++;
                }
                int coordinate=mpp[div];
                // Go to coordinate'th index in segment tree and update its value by +cnt;
                // Point Update
                st.pointUpdate(0,0,seg_tree_size-1,coordinate,cnt);
            }
            arr[idx]=val;
        }else{
            int l,r;
            cin>>l>>r;
            if((l==r && l==1) || l>r){
                cout<<0<<endl;
                continue;
            }

            // Can Be Done With Binary Search But logN factor
            // Although it may pass
            // Just >=l Prime Number And Just <=r Prime Number In O(1) By Pre Computation
            int ll=greater_than[l];
            int rr=lesser_than[r];

            // ll and rr are actual prime numbers
            // But we need coordinates of them
            // consider edge case ll=1 && rr=1
            int left_coordinate=mpp[ll];
            int right_coordinate=mpp[rr];

            // Then Range Sum Query on [left_coordinate,right_coordinate]
            if(left_coordinate<=right_coordinate){
                // rsq(left_coordinate,right_coordinate)
                cout<<st.query(0,0,seg_tree_size-1,left_coordinate,right_coordinate)<<endl;
            }else{
                cout<<0<<endl;
            }

        }
    }
}
// 6
// 5 5 7 10 14 15
// 3
// 2 2 3
// 1 2 7
// 2 2 3
