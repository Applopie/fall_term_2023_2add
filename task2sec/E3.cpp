#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
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
    
    for (int i = 0; i < k; i++) {
        string query;
        cin >> query;
        int len = query.length();
        
        if (!words.count(len)) {
            cout << "NO\n";
            continue;
        }
        
        bool found = false;
        const auto& bucket = words[len];
        
        if (bucket.size() <= 1000) {
            for (const string& w : bucket) {
                int diff = 0;
                for (int j = 0; j < len; j++) {
                    if (w[j] != query[j]) {
                        diff++;
                        if (diff > 1) break;
                    }
                }
                if (diff == 1) {
                    found = true;
                    break;
                }
            }
        } 
        else {
            string temp = query;
            for (int pos = 0; pos < len && !found; pos++) {
                char original = query[pos];
                for (char c : {'a', 'b', 'c'}) {
                    if (c == original) continue;
                    temp[pos] = c;
                    if (bucket.count(temp)) {
                        found = true;
                        break;
                    }
                }
                temp[pos] = original;
            }
        }
        
        cout << (found ? "YES\n" : "NO\n");
    }
    
    return 0;
}
