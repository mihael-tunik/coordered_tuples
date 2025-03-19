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
Long story short general version also can be solved for $O(n \cdot \log n)$. 
See details here:
```cpp
ull count_coordered_fenwick(vector <int> a, vector <int> b);
```