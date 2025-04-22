#include<bits/stdc++.h>
using namespace std;

void fcfs(vector<int> v,int head){
    int n = v.size();
    int seek_time = 0;
    
    for(auto i:v){
        seek_time+=abs(head-i);
        head = i;
    }
    cout<<seek_time<<endl;
}

void sstf(vector<int> v,int head){
    int n = v.size();
    vector<int> visited(n,false);
    int seek_time = 0;
    for(int i=0;i<n;i++){
        int mini = INT_MAX;
        int ind = -1;
        for(int j = 0;j<n;j++){
            if(!visited[j] and abs(head-v[j])<mini){
                mini = abs(head-v[j]);
                ind = j;
            }
        }
        seek_time += mini;
        head = v[ind];
        visited[ind] = true;
        cout<<head<<" ";
    }
    cout<<endl;
    cout<<seek_time<<endl;
}

void scan(vector<int>v,int head, string direction,int disk_size){
    int seek_time = 0;
    vector<int>left , right;
    if(direction =="left") left.push_back(0);
    else right.push_back(disk_size-1);

    for(auto i:v){
        if(i<head) left.push_back(i);
        else right.push_back(i);
    }

    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    if(direction == "left"){
        for(int i =left.size()-1;i>=0 ;i--){
            seek_time+=abs(head-left[i]);
            head = left[i];
        }
        for(int i = 0;i<right.size();i++){
            seek_time+=abs(head-right[i]);
            head = right[i];
        }
    }else {
        for (int i = 0; i < right.size(); i++) {
            //cout << right[i] << " ";
            seek_time += abs(head - right[i]);
            head = right[i];
        }
        for (int i = left.size() - 1; i >= 0; i--) {
            //cout << left[i] << " ";
            seek_time += abs(head - left[i]);
            head = left[i];
        }
    }
    cout<<"Total seek time"<<seek_time<<endl;
}

void cscan(vector<int> v,int head,int disks_size){
    vector<int> left,right;
    int seek_time = 0;
    left.push_back(0);
    right.push_back(disks_size-1);

    for(int i:v){
        if(i<head) left.push_back(i);
        else right.push_back(i);
    }

    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    for(int i=0;i<right.size();i++){
        seek_time+=abs(head-right[i]);
        head = right[i];
    }
    seek_time+=abs(head-0);
    head = 0;
    for(int i=0;i<left.size();i++){
        seek_time+=abs(head-left[i]);
        head = left[i];
    }
    cout<<seek_time<<endl;
}

int main(){
    int n,disk_size;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    cout << "Enter disk size (e.g., 200): ";
    cin >> disk_size;
    int head;
    cin>>head;
    string dir;
    cout<<"Enter the direction: ";
    cin>>dir;
    fcfs(v,head);
    sstf(v,head);
    scan(v,head,dir,disk_size);
    cscan(v,head,disk_size);
}