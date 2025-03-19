from copy import deepcopy
import random
from collections import defaultdict

class FenwickTree:
    def __init__(self, n):
        self.t = [0] * n
        self.N = n
        
    def modify(self, i, d):
        while i < self.N:
            self.t[i] += d
            i = i | (i + 1)
    
    def prefix_sum(self, i):
        result = 0
        while i >= 0:
            result += self.t[i]
            i = (i & (i + 1)) - 1
        return result

    def query(self, i, j):
        return self.prefix_sum(j) - self.prefix_sum(i - 1)
        
def coordered_pairs(a, b):
    n, cnt = len(a), 0
    for i in range(0, n):
        for j in range(0, n):
            if a[i] < a[j] and b[i] < b[j]:
                #print((i, j))
                cnt += 1
    return cnt
    
def coordered_fenwick(a, p):
    n, cnt, M = len(a), 0, 200
    T = FenwickTree(M+1)
        
    for i in range(0, n):
        T.modify(a[p[i]], 1)
        q = T.query(0, a[p[i]] - 1)
        cnt += q

    return cnt
    
# permutation based count
def coordered_with_permutation(a, p):
    n, cnt = len(a), 0
    for i in range(0, n):
        for j in range(0, n):
            if a[p[i]] < a[p[j]] and i < j:
                cnt += 1
    return cnt

def count_coordered_pairs_with_fenwick(a, b):
    b_indexed = [(b[i], i) for i in range(len(b))]
    b_indexed_sorted = sorted(b_indexed, key=lambda x: x[0])

    b_ord, pb = [0] * len(b), [0] * len(b)
    for i in range(len(b_indexed_sorted)):
        b_ord[b_indexed_sorted[i][1]] = i
    for i in range(len(b)):
        pb[b_ord[i]] = i

    state, parts, part = b_indexed_sorted[0][0], [], [b_indexed_sorted[0][1]]
    for i in range(1, len(b)):
        val, idx = b_indexed_sorted[i]
        if val != state:
            state = val
            parts.append(deepcopy(part))
            part.clear()
            part.append(idx)
        else:
            part.append(idx)
    parts.append(deepcopy(part))

    sum_co_inv = 0
    for prt in parts:
        p_size = len(prt)
        if p_size > 1:
            sum_co_inv += coordered_fenwick([a[x] for x in prt], list(range(p_size)))

    return coordered_fenwick(a, pb) - sum_co_inv 

if __name__ == '__main__':
    for test in range(10):
        max_num, size = 25, 50
        a = [random.randint(0, max_num) for i in range(size)]
        b = [random.randint(0, max_num) for i in range(size)]
   
        print(a)
        print(b)
    
        print(coordered_pairs(a, b))
        print(count_coordered_pairs_with_fenwick(a, b))
    
        print('---')
