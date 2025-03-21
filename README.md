### Coordered pairs in two arrays
Given arrays _a, b_ of _n_ elements each, count number of pairs $a_i < a_j$,  $b_i < b_j$.

This is the general version of the following problem:

*Coordered elements in array problem*
- Given array _a_ of _n_ elements, count number of pairs $a_i < a_j, i < j$. 

Or (with different order operator) of the following:

*Number of inversions problem*
- Given array _a_ of _n_ elements, count number of pairs $a_i > a_j, i < j$. 

Both mentioned problems are twins to each other.
For example, in 'distinct elements' case it's simply $\sum_{\{a_i < a_j, i < j\}} 1 = \frac{n(n-1)}{2} - \sum_{\{a_i > a_j, i < j\}} 1 $. 

Any of them can be solved in quasilinear time with divide-and-conquer or with any range-sum-point-update container.

But what if we count array elements according to elements of another array instead of indexes? This bring us back to the starting problem.
Long story short general version also can be solved in $O(n \cdot \log^2 n)$ and even in $O(n \cdot \log n)$. 

See details here:
```cpp
ull count_coordered(vector <int> a, vector <int> b); // O(n^2)
ull count_coordered_fenwick_2d(vector <int> a, vector <int> b); // O(n (log n)^2)
ull count_coordered_fenwick(vector <int> a, vector <int> b); // O(n log n)
```

### Solution $O(n \cdot \log^2 n)$
Let's start from standard inversion count algorithm:
```
for i in range(n):
   T.update(a[i], 1)
   cnt += T.prefix(a[i]-1)
```
Here, _T_ is counting array initialized by zeros, where we store counts for every value in _a_.
To perform both operations efficiently one should choose any $O(\log n)$ range query structure as _T_, let's say Fenwick tree.
It works, because updates are made in order of indexes in _a_ and so _T.prefix(a[i]-1)_ counts only _a[k] < a[i]_ with _k < i_ by default.
Every _k < i_ appears before _i_.

Let's modify our task to exploit similar idea. Main observation that given arrays _a, b_ we can take any permutation of both and that
doesn't change the number of coordered pairs. Indeed any pair _a[i] < a[j], b[i] < b[j]_ would be mapped to _a[p[i]] < a[p[j]], b[p[i]] < b[p[j]]_.
It means we can sort!

Now, one of arrays (lets say _a_) is completely ordered. Let's use the same idea, but instead of counting array we will modify entries in _matrix_.

```
sort((a, b), coordinate=0) 
for i in range(n):
   T.update((a[i], b[i]), 1)
   cnt += T.prefix((a[i]-1, b[i]-1))
```
Every _a[k] < a[i]_ appears before _a[i]_. 
This works in $O(n \cdot \log^2 n)$ time for 2D Fenwick tree.

### Build
```
g++ -O3 -march=native -ffast-math -fno-tree-vectorize -fno-exceptions count_coordered_pairs.cpp -o count
```
