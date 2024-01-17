#include<iostream>
#include<vector>
#include <climits>
#include<cmath>
#include<vector>
#include <numeric>
#include<unordered_map>
#include<string>

 
using namespace std;

void createLPS(string& pattern, vector<int>& lps){
        int m = pattern.size();
        int i=1;
        int j=0;
        lps[j]=0;
        while(i<m){
            if(pattern[j]==pattern[i]){
                lps[i]=j+1;
                i++;
                j++;
            }else{
                if(j!=0){
                    j = lps[j-1];
                }else{
                    lps[i]=0;
                    i++;
                }
            }
        }
    }

vector<int> match(string& s, string& pattern)
{
    int m = pattern.size();
    int n = s.size();
    vector<int> lps(m, 0);
    createLPS(pattern, lps);
    int i=0, j=0;


    vector<int> idxs;

    while(i<n){
        if(pattern[j]==s[i]){
            j++;
            i++;
        }else{
            if(j!=0){
                j = lps[j-1];
            }else{
                i++;
            }
        }
        if(j==m){
            idxs.push_back(i-m);             
            j = lps[j-1];
        }
    }  

    return idxs;
}

int main()
{
    string hayStack = "avadhoot";
    string needle = "a";

    vector<int> matches = match(hayStack, needle);
    for(auto &el : matches)
        cout<<el<<" ";
    return 0;
}