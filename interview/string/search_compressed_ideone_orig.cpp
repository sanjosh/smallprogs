
    #include<iostream>
    #include<algorithm>
    #include<ctype.h>
    #include<string>
     
    using namespace std;
    typedef long long ll;
    main(){
    string str;
    cin>>str;
    int n=str.length();
    int len[n];
    len[0]=1;
    ll p;
    ll ii=0;
    p=1;
    //len[i] is the length of string till ith element
    for(int i=1;i<n;i++){
    if(!(str[i]>='0'&&str[i]<='9')){
    len[i]=len[i-1]+1;  
    ii=0;p=1;
    }
    else{
    ii=ii*10+str[i]-'0';
    if(i+1<n){
    if(!(str[i+1]>='0'&&str[i+1]<='9')){
    len[i]=len[i-1]*ii;
    ii=0;
    p=1;
    }
    else {
    len[i]=len[i-1];
    }
    }
    if(i+1==n){
    len[i]=len[i-1]*ii;
    ii=0;
    }
    }
    }
    //cout<<len[n-1]<<" "<<len[n-2]<<endl;
    ll k;
     
     
     
    int T;
    //number of times you want to test in short number of times you enter value of k
    cin>>T;
    while(T--){
    cin>>k;
    if(k>len[n-1]){
    cout<<"No answer";
    continue;
    }
    bool flag=1;
    for(int i=n-1;i>=0;i--){
    if((str[i]>='0'&&str[i]<='9')&&flag){
    {
    k=k%len[i-1];
    flag=0;
    if(k==0){
    cout<<str[i-1]<<endl;
    break;  
    }
    }
    }
    else if(!(str[i]>='0'&&str[i]<='9')){
    flag=1;
    if(k==len[i]){
    cout<<str[i]<<endl;
    }
     
    }
    }
    }
    }
