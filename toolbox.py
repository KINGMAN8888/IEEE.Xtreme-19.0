"""
صندوق أدوات Python للمسابقات البرمجية (IEEEXtreme Toolbox)

هذا الملف هو مكتبتك الخاصة. عند بدء أي مسألة، انسخ "القالب الأساسي".
وإذا احتجت خوارزمية معينة (مثل Dijkstra أو DSU)، 
انسخها من قسمها في هذا الملف والصقها في ملف الحل.
"""

# -----------------------------------------------------------------------------
#  1. القالب الأساسي (The Boilerplate)
#  ابدأ كل مسألة بنسخ هذا الجزء
# -----------------------------------------------

import sys
import math
import cmath
import collections
import heapq
import bisect
import itertools
import random
import time
import functools
import operator
import string
import re
import copy
import array
import datetime
import decimal
import fractions
import json
import os
import threading
import queue

# تسريع عمليات الإدخال (مهم جداً لتجنب TLE)
input = sys.stdin.readline
# زيادة حد العودية (Recursion Limit) للمسائل التي تتطلب DFS عميق
sys.setrecursionlimit(200010)

# (اختياري) دوال مساعدة للقراءة
def ri(): 
    """قرءاة عدد صحيح"""
    return int(input())
def rl(): 
    """قراءة قائمة من الأعداد الصحيحة"""
    return list(map(int, input().split()))
def rs(): 
    """قراءة نص (string) وإزالة المسافات الزائدة"""
    return input().strip()

# ثوابت شائعة
INF = float('inf')
MOD = 10**9 + 7 # أو 1_000_000_007

def solve():
    """
    الدالة الرئيسية لحل المسألة
    """
    # مثال: قراءة عددين وطباعة مجموعهما
    # try:
    #     a, b = rl()
    #     print(a + b)
    # except (EOFError, ValueError):
    #     return
    pass

def main():
    """
    الدالة الرئيسية (Main Function)
    """
    # 2. التعامل مع حالات الاختبار المتعددة (Multiple Test Cases)
    try:
        t = ri() # اقرأ عدد حالات الاختبار
        
        # إذا كانت المسألة لا تحتوي على T، قم بتعليق السطر السابق وضع t = 1
        # t = 1
        
        for _ in range(t):
            solve()
            
    except (EOFError, ValueError):
        # التعامل مع نهاية الملف أو المدخلات الفارغة
        pass

if __name__ == "__main__":
    main()


# -----------------------------------------------------------------------------
#  2. خوارزميات الرياضيات (Math Algorithms)
#  انسخ الدوال التي تحتاجها من هنا
# -----------------------------------------------------------------------------

# === القاسم المشترك الأكبر (Greatest Common Divisor) ===
def gcd(a, b):
    """استخدام دالة بايثون المدمجة (سريعة)"""
    return math.gcd(a, b)

# === المضاعف المشترك الأصغر (Least Common Multiple) ===
def lcm(a, b):
    """(a * b) / gcd(a, b)"""
    if a == 0 or b == 0:
        return 0
    return abs(a * b) // math.gcd(a, b)

# === الأس السريع (Fast Power / Modular Exponentiation) ===
# بايثون توفر دالة مدمجة سريعة جداً لهذا
def power(base, exp, mod=MOD):
    """
    يحسب (base^exp) % mod بكفاءة
    استخدام دالة بايثون المدمجة pow(base, exp, mod)
    """
    return pow(base, exp, mod)

# === غربال إراتوسثينس (Sieve of Eratosthenes) ===
def sieve(n):
    """
    يجد كل الأعداد الأولية حتى n
    يرجع قائمة boolean
    """
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for p in range(2, int(n**0.5) + 1):
        if is_prime[p]:
            for i in range(p * p, n + 1, p):
                is_prime[i] = False
    
    # (اختياري) إرجاع قائمة الأعداد الأولية نفسها
    # primes = [i for i, prime in enumerate(is_prime) if prime]
    # return primes
    return is_prime


# -----------------------------------------------------------------------------
#  3. هياكل البيانات (Data Structures)
# -----------------------------------------------------------------------------

# === هيكل الاتحاد والتقسيم (Disjoint Set Union - DSU / Union-Find) ===
class DSU:
    """
    هيكل DSU مع ضغط المسار والاتحاد بالحجم.
    dsu = DSU(n)
    dsu.find(i)
    dsu.unite(i, j)
    """
    def __init__(self, n):
        # كل عنصر هو "الأب" لنفسه في البداية
        self.parent = list(range(n + 1))
        # حجم كل مجموعة هو 1
        self.sz = [1] * (n + 1)

    def find(self, i):
        """إيجاد "الأب" الأعلى (مع ضغط المسار)"""
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i]) # ضغط المسار
        return self.parent[i]

    def unite(self, i, j):
        """دمج مجموعتين (الاتحاد بالحجم)"""
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            # دمج المجموعة الأصغر في الأكبر
            if self.sz[root_i] < self.sz[root_j]:
                root_i, root_j = root_j, root_i
            self.parent[root_j] = root_i
            self.sz[root_i] += self.sz[root_j]
            return True # تم الدمج
        return False # لم يتم الدمج (كانوا في نفس المجموعة)


# -----------------------------------------------------------------------------
#  4. خوارزميات الرسوم البيانية (Graph Algorithms)
# -----------------------------------------------------------------------------

# (نفترض أن الرسم البياني ممثل بـ
#  adj = collections.defaultdict(list) 
#  adj[u].append((v, weight)) 
#  أو للمسارات غير الموزونة
#  adj[u].append(v) )

# === البحث بالعمق أولاً (Depth First Search - DFS) ===
# (يجب زيادة sys.setrecursionlimit في القالب الأساسي)
visited_dfs = set()
def dfs(u, adj):
    """
    adj = defaultdict(list) where adj[u] = [v1, v2, ...]
    """
    visited_dfs.add(u)
    # print(u, end=" ") # (للطباعة)
    for v in adj[u]: # (إذا كان الرسم البياني موزوناً: for v, w in adj[u])
        if v not in visited_dfs:
            dfs(v, adj)

# === البحث بالعرض أولاً (Breadth First Search - BFS) ===
def bfs(start, adj):
    """
    adj = defaultdict(list) where adj[u] = [v1, v2, ...]
    يرجع قاموس بالمسافات من 'start'
    """
    dist = collections.defaultdict(lambda: -1)
    q = collections.deque([start])
    dist[start] = 0
    
    while q:
        u = q.popleft()
        for v in adj[u]: # (إذا كان الرسم البياني موزوناً: for v, w in adj[u])
            if dist[v] == -1:
                dist[v] = dist[u] + 1
                q.append(v)
    return dist

# === خوارزمية دكسترا (Dijkstra's Algorithm) ===
# لإيجاد أقصر مسار من مصدر واحد في الرسوم البيانية ذات الأوزان غير السالبة
def dijkstra(start, adj):
    """
    adj = defaultdict(list) where adj[u] = [(v1, w1), (v2, w2), ...]
    يرجع قاموس بأقصر المسافات من 'start'
    """
    dist = collections.defaultdict(lambda: INF)
    # (distance, node)
    pq = [(0, start)] # priority queue
    dist[start] = 0
    
    while pq:
        d, u = heapq.heappop(pq)
        
        if d > dist[u]:
            continue # تخطي إذا وجدنا مسار أقدم وأطول
            
        for v, weight in adj[u]:
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                heapq.heappush(pq, (dist[v], v))
                
    return dist

