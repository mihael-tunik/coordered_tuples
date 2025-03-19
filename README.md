### Coordered pairs in two arrays
Given arrays _a, b_ of _n_ elements each, count number of pairs $a_i < a_j$,  $b_i < b_j$.

This is the general version of the following problem:

*Coordered elements in array problem*
- Given array _a_ of _n_ elements, count number of pairs $a_i < a_j, i < j$. 

Or (with different order operator) of the following:

*Number of inversions problem*
- Given array _a_ of _n_ elements, count number of pairs $a_i > a_j, i < j$. 

Both mentioned problems are twins to each other and can be solved in quasilinear time.
Long story short general version also can be solved for $O(n \log(n))$
