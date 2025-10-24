/******************************************************************************
 * * صندوق أدوات C++ للمسابقات البرمجية (IEEEXtreme Toolbox)
 * * هذا الملف هو مكتبتك الخاصة. عند بدء أي مسألة، انسخ "القالب الأساسي".
 * وإذا احتجت خوارزمية معينة (مثل Dijkstra أو DSU)، 
 * انسخها من قسمها في هذا الملف والصقها في ملف الحل.
 * ******************************************************************************/

// -----------------------------------------------------------------------------
//  1. القالب الأساسي (The Boilerplate)
//  ابدأ كل مسألة بنسخ هذا الجزء
// -----------------------------------------------------------------------------

// استخدام هذا الهيدر يوفر كل المكتبات القياسية (شائع في المسابقات)
#if defined(__has_include)
  #if __has_include(<bits/stdc++.h>)
    #include <bits/stdc++.h>
  #else
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <numeric>
    #include <map>
    #include <queue>
    #include <utility>
    #include <cmath>
    #include <limits>
    #include <functional>
    #include <string>
    #include <set>
    #include <stack>
  #endif
#else
  // Fallback for compilers without __has_include: include common headers
  #include <iostream>
  #include <vector>
  #include <algorithm>
  #include <numeric>
  #include <map>
  #include <queue>
  #include <utility>
  #include <cmath>
  #include <limits>
  #include <functional>
  #include <string>
  #include <set>
  #include <stack>
#endif

using namespace std;

// === تعريفات مختصرة للأنواع (Type Definitions) ===
typedef long long ll; // للتعامل مع الأرقام الكبيرة (حتى 10^18)
typedef pair<int, int> pii; // زوج من الأعداد الصحيحة (شائع في Dijkstra والأزواج)
typedef vector<int> vi; // متجه من الأعداد الصحيحة
typedef vector<ll> vll; // متجه من الأعداد الطويلة
typedef vector<pii> vpii; // متجه من الأزواج

// === ثوابت شائعة (Common Constants) ===
const ll INF = 1e18; // قيمة "لا نهائية" للأعداد الطويلة
const int MOD = 1e9 + 7; // ثابت "المود" الشائع في مسائل التوافقيات
const double PI = acos(-1.0); // ثابت باي

// === دالة تسريع الإدخال والإخراج (Fast I/O) ===
// هذه الدالة ضرورية جداً لتجنب "Time Limit Exceeded" بسبب بطء cin/cout
void setup_io() {
    ios_base::sync_with_stdio(false); // فصل stream C++ عن C
    cin.tie(NULL); // عدم مزامنة cin
    cout.tie(NULL); // عدم مزامنة cout
}

// === الدالة الرئيسية لحل المسألة (Solve Function) ===
// نضع الكود الخاص بكل حالة اختبار هنا
void solve() {
    // مثال: قراءة عددين وطباعة مجموعهما
    // ll a, b;
    // cin >> a >> b;
    // cout << (a + b) << "\n";
}

// === الدالة الرئيسية (Main Function) ===
int main() {
    // 1. تفعيل تسريع الإدخال والإخراج
    setup_io();

    // 2. التعامل مع حالات الاختبار المتعددة (Multiple Test Cases)
    int t = 1;
    cin >> t; // اقرأ عدد حالات الاختبار
    
    // إذا كانت المسألة لا تحتوي على T، قم بتعليق السطر السابق وضع t = 1
    // int t = 1; 

    while (t--) {
        solve(); // استدعاء دالة الحل لكل حالة
    }

    return 0;
}


// -----------------------------------------------------------------------------
//  2. خوارزميات الرياضيات (Math Algorithms)
//  انسخ الدوال التي تحتاجها من هنا
// -----------------------------------------------------------------------------

// === القاسم المشترك الأكبر (Greatest Common Divisor) ===
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// === المضاعف المشترك الأصغر (Least Common Multiple) ===
ll lcm(ll a, ll b) {
    return (a * b) / gcd(a, b);
}

// === الأس السريع (Fast Power / Modular Exponentiation) ===
// يحسب (base^exp) % mod بكفاءة O(log exp)
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// === غربال إراتوسثينس (Sieve of Eratosthenes) ===
// يجد كل الأعداد الأولية حتى n
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }
    return is_prime;
}


// -----------------------------------------------------------------------------
//  3. هياكل البيانات (Data Structures)
// -----------------------------------------------------------------------------

// === هيكل الاتحاد والتقسيم (Disjoint Set Union - DSU / Union-Find) ===
// يستخدم لتتبع مجموعات العناصر (مثل التحقق من الاتصال في الرسوم البيانية)
struct DSU {
    vi parent;
    vi sz; // (اختياري) لتخزين حجم كل مجموعة
    
    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        // في البداية، كل عنصر هو "الأب" لنفسه
        iota(parent.begin(), parent.end(), 0); 
    }

    // إيجاد "الأب" الأعلى (مع ضغط المسار)
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // ضغط المسار
    }

    // دمج مجموعتين (الاتحاد بالحجم)
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // دمج المجموعة الأصغر في الأكبر
            if (sz[root_i] < sz[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
    }
};


// -----------------------------------------------------------------------------
//  4. خوارزميات الرسوم البيانية (Graph Algorithms)
// -----------------------------------------------------------------------------

// (نفترض أن الرسم البياني ممثل بقائمة الجوار)
// map<int, vpii> adj; // مثال: adj[u] = {{v1, w1}, {v2, w2}, ...}

// === البحث بالعمق أولاً (Depth First Search - DFS) ===
map<int, bool> visited_dfs;
void dfs(int u, map<int, vi>& adj) {
    visited_dfs[u] = true;
    // cout << u << " "; // (للطباعة)
    for (int v : adj[u]) {
        if (!visited_dfs[v]) {
            dfs(v, adj);
        }
    }
}

// === البحث بالعرض أولاً (Breadth First Search - BFS) ===
map<int, int> dist_bfs;
void bfs(int start, map<int, vi>& adj) {
    for (auto const& [key, val] : adj) dist_bfs[key] = -1; // تهيئة المسافات
    
    queue<int> q;
    q.push(start);
    dist_bfs[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist_bfs[v] == -1) {
                dist_bfs[v] = dist_bfs[u] + 1;
                q.push(v);
            }
        }
    }
}

// === خوارزمية دكسترا (Dijkstra's Algorithm) ===
// لإيجاد أقصر مسار من مصدر واحد في الرسوم البيانية ذات الأوزان غير السالبة
map<int, ll> dijkstra(int start, map<int, vpii>& adj) {
    map<int, ll> dist;
    for (auto const& [key, val] : adj) dist[key] = INF;

    // (distance, node)
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue; // تخطي إذا وجدنا مسار أقدم وأطول

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
