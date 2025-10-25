import sys
from bisect import bisect_left, bisect_right

def solve():

    input = sys.stdin.readline

    try:
        n, q = map(int, input().split())
        arr = list(map(int, input().split()))
        results = []

      
        for _ in range(q):
            
            x = int(input())

           
            first_idx = bisect_left(arr, x)

            
            if first_idx == n or arr[first_idx] != x:
                results.append("-1 -1")
                continue

            
            last_idx = bisect_right(arr, x) - 1
            
            
            results.append(f"{first_idx + 1} {last_idx + 1}")

       
        print("\n".join(results))

    except (EOFError, ValueError):
    
        pass
solve()
