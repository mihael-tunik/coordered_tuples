#include <cstdio>
#include <vector>
#include <set>
#include <chrono>
#include <string>
#include <climits>
#include <map>
#include <algorithm>
#include <iostream>
#include "profile.h"

using namespace std;

typedef unsigned long long ull;

class FenwickTree2D {

    public:
        int n, m;
        vector <vector <ull> > t;

    FenwickTree2D(int _n, int _m){
        this->n = _n;
        this->m = _m;

        this->t.resize(n + 1);
        for(int i = 0; i < n + 1; ++i)
           t[i].assign(m+1, 0);
    }

    void modify(int r, int c, ull d) {
        r++, c++;
        for (int i = r; i <= n; i += i & -i)
            for (int j = c; j <= m; j += j & -j) 
                t[i][j] += d;
    }

    ull prefix(int r, int c) {
        r++, c++;
        ull sum = 0;
        for (int i = r; i > 0; i -= i & -i)
            for (int j = c; j > 0; j -= j & -j) 
                sum += t[i][j];
        return sum;
    }

};

ull count_coordered_fenwick_2d(vector <int> &a, vector <int> &b){
    ull n = a.size(), cnt = 0, M = 20000;
    FenwickTree2D range_tree(M+1, M+1);
    
    vector <pair <int, int>> c(n);
    for(int i = 0; i < n; ++i)
       c[i] = {a[i], b[i]};
    sort(c.begin(), c.end());

    for(int i = 0; i < n; ++i){
        range_tree.modify(c[i].first, c[i].second, 1);
        cnt += range_tree.prefix(c[i].first-1, c[i].second-1);
    }
    return cnt;
}

class FenwickTree{
    public:
        vector <ull> t;
        int n;
        
    FenwickTree(int n){
        this->t.assign(n+1, 0);
        this->n = n;
    }
    
    void modify(int i, ull d){
        while(i < n){
            t[i] += d;
            i = i | (i + 1);
        }
    }
    
    ull prefix(int i){
        ull result = 0;
        while(i >= 0){
            result += t[i];
            i = (i & (i + 1)) - 1;
        }
        return result;
    }
};

/* count #{a[i] < a[j] && p[i] < p[j]}, p is permutation */
ull count_coordered_fenwick_p(vector <int> a, vector <int> p){
    ull n = a.size(), cnt = 0, M = 20000;
    FenwickTree range_tree(M+1);
    
    for(int i = 0; i < n; ++i){
        range_tree.modify(a[p[i]], 1);
        cnt += range_tree.prefix(a[p[i]]-1);
    }
    return cnt;
}

void compute_equal_groups(vector <pair <int, int>> &pairs, vector <pair <int, int>> &eq_groups){
    int state = pairs[0].first, n = pairs.size(), l = 0, r = 0;

    pairs.push_back({INT_MAX, -1});
    for(int i = 1; i < n + 1; ++i){
       auto [value, _] = pairs[i];
       if(value != state){
           eq_groups.push_back({l, r});
           l = i, r = i, state = value;
           continue;
       }
       ++r;
    }
}

// a.size() == b.size()
ull count_coordered_fenwick(vector <int> &a, vector <int> &b){
    ull n = a.size(), sum = 0;
    vector <pair<int, int>> b_indexed(n), eq_groups;
    vector <int> b_p(n);

    for(int i = 0; i < n; ++i)
        b_indexed[i] = {b[i], i};
    sort(b_indexed.begin(), b_indexed.end());

    for(int i = 0; i < n; ++i)
        b_p[i] = b_indexed[i].second;
        
    compute_equal_groups(b_indexed, eq_groups);

    for(auto [l, r] : eq_groups){
        int len = r - l + 1; 
        vector <int> a_group(len), range(len);
        for(int i = 0; i < len; ++i)
            a_group[i] = a[b_p[l + i]], range[i] = i;
        sum += count_coordered_fenwick_p(a_group, range);
    }
    return count_coordered_fenwick_p(a, b_p) - sum;
}

ull count_coordered(vector <int> &a, vector <int> &b){
    ull n = a.size(), cnt = 0;

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(a[i] < a[j] && b[i] < b[j])
                ++cnt;
    return cnt;
}

void print_array(vector <int> v){
    int vs = v.size();
    for(int i = 0; i < vs; ++i)
        printf("%3i ", v[i]);
    printf("\n");
}

int main(void){

    int n = 20, tests = 10, fails = 0;
    vector <int> a(n), b(n);
    
    srand(123);

    for(int k = 0; k < tests; ++k){

        for(int i = 0; i < n; ++i)
             a[i] = rand() % 100, b[i] = rand() % 100;
        
        cout << "a: ";
        print_array(a);
        cout << "b: ";
        print_array(b);

        int cnt_1 = count_coordered_fenwick(a, b);
        int cnt_2 = count_coordered(a, b);
        
        printf("count: %i, check: %i\n", cnt_1, cnt_2);
        
        if(cnt_1 != cnt_2)
            fails++;
    }

    cout << endl << "failed: " << fails << "/" << tests << endl << endl;
    /* now max test */
    /*int n_max = 20000;

    a.resize(n_max), b.resize(n_max);
    for(int i = 0; i < n_max; ++i)
        a[i] = rand() % 20000, b[i] = rand() % 20000;

    int cnt_1 = profile(&count_coordered, a, b);
    int cnt_2 = profile(&count_coordered_fenwick_2d, a, b);
    int cnt_3 = profile(&count_coordered_fenwick, a, b);

    printf("maxtest count: %i, %i, %i\n", cnt_1, cnt_2, cnt_3);*/
    return 0;
}
