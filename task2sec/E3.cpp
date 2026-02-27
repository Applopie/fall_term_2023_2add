#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    unordered_map<int, unordered_set<string>> words;
    
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        words[word.length()].insert(word);
    }
    
    string result;
    result.reserve(k * 4);
    
    for (int i = 0; i < k; i++) {
        string query;
        cin >> query;
        int len = query.length();
        
        if (!words.count(len)) {
            result += "NO\n";
            continue;
        }
        
        bool found = false;
        const auto& wordsOfLen = words[len];
        
        string temp = query;
        for (int pos = 0; pos < len && !found; pos++) {
            char original = query[pos];
            
            for (char c : {'a', 'b', 'c'}) {
                if (c == original) continue;
                
                temp[pos] = c;
                if (wordsOfLen.count(temp) && temp != query) {
                    found = true;
                    break;
                }
            }
            temp[pos] = original;
        }
        
        result += found ? "YES\n" : "NO\n";
    }
    
    cout << result;
    return 0;
}
