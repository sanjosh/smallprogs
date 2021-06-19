
/*

https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/

Construct a suffix trie and return total number of edges. 
Total number of edges will give distinct substrings. To understand the reason, draw a suffix trie and it will be evident.

https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/discuss/1134832/Suffix-trie

https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/discuss/1100464/C%2B%2B-suffix-array-%2B-longest-common-prefix-array-solution-beats-96-speed

number of unique rolling hashes 
rolling hash(K) computed from rolling hash(K-1)

*/

int comp(const string &a,const string &b){
        int i=0;
        while(i<a.length() && i<b.length() && a[i]==b[i]){
            ++i;
        }
        return i;
    }

    int countDistinct(string s) {
        int len=1;
        int str_len=s.length();
        vector<pair<string,int>> suffix_array(str_len);
        for(int i=str_len-1;i>=0;i--){
            suffix_array[i]={s.substr(i,len),i};
            ++len;
        }
        sort(suffix_array.begin(),suffix_array.end(),[](const pair<string,int> &a,const pair<string,int> &b){return a.first<b.first;});
        vector<int> lcp(str_len);
        int total_lcp=0;
        for(int i=1;i<str_len;i++){
            lcp[i]=comp(suffix_array[i].first,suffix_array[i-1].first);
            total_lcp+=lcp[i];
        }
        return (str_len*(str_len+1))/2-total_lcp;
