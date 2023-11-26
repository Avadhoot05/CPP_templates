#include<iostream>
#include<vector>
#include <climits>

using namespace std;

class SegmentTree
{
    public:
    vector<int> st;

    SegmentTree(int n)
    {
        st.resize(4*n, 0);
    }

    void Print()
    {
        for(auto &el : st)
            cout<<el<<" ";
        cout<<"\n";
    }

    void Build(int ind, int low, int high, vector<int> &arr)
    {
        if(low == high)//one element
        {
            st[ind] = arr[low];
            return;
        }

        int mid = low + (high-low)/2;
        Build(2*ind+1, low, mid, arr);
        Build(2*ind+2, mid+1, high, arr);

        //change min according to problem
        st[ind] = min(st[2*ind+1], st[2*ind+2]);
    }

    int RangeQuery(int ind, int low, int high, int l, int r)
    {
        //no overlap
        if(high < l || low > r)
        {
            return INT_MAX;
        }

        //complete overlap
        if(l <= low && r >= high)
        {
            return st[ind];
        }

        //partial overlap
        int mid = low + (high-low)/2;
        int left = RangeQuery(2*ind+1, low, mid, l, r);
        int right = RangeQuery(2*ind+2, mid+1, high, l, r);

        //IMP::min will change according to problem
        return min(left, right);
    }

    void Update(int ind, int low, int high, int i, int val)
    {
        if(low == high)
        {
            st[ind] = val;
            return;
        }

        int mid = low + (high-low)/2;

        if(i <= mid)
            Update(2*ind+1, low, mid, i, val);
        else
            Update(2*ind+2, mid+1, high, i, val);

        //IMP::min will change according to problem
        st[ind] = min(st[2*ind+1], st[2*ind+2]);
    }
};



int main() 
{
    vector<int> arr;
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(0);
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(7);

    int n = arr.size();

    SegmentTree sg = SegmentTree(arr.size());
    sg.Build(0, 0, n-1, arr);
    sg.Print();


    cout<<sg.RangeQuery(0, 0, n-1, 0, 3)<<"\n";
    sg.Update(0, 0, n-1, 2, 10);
    cout<<sg.RangeQuery(0, 0, n-1, 0, 3)<<"\n";
    cout<<sg.RangeQuery(0, 0, n-1, 3, 5)<<"\n";
    return 0;
}