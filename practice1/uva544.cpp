// https://vjudge.net/problem/UVA-544
// typedefs and such/-----------------
#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define for1(i, n) for (int i = 1; i <= (int)n; ++i)
#define fore(i, l, r) for (int i = (int)l; i <= (int)r; ++i)
#define ford(i, n) for (int i = (int)(n)-1; i >= 0; --i)
#define fored(i, l, r) for (int i = (int)r; i >= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout << #x << " " << x << el
#define ri(n) scanf("%d", &n)
#define vec vector
#define tiii(a, b, c) array<int, 3>({a, b, c})

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<char, int> pci;
typedef pair<string, int> psi;
typedef array<int, 3> tiii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;

const int MAXN = 1e5 + 200;
const int INF = 1 << 30;
const double PI = acos(-1);
const double EPS = 1e-10;
int dr[] = {1, -1, 0, 0, 1, -1, -1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0, 1, -1, 1, 1, -1, -1};

// Problem start------------------------

struct dsu {
  int num_sets;
  vi p, r;
  void init(int size) {
    p.assign(size, 0);
    forn(i, size) p[i] = i;
    r.assign(size, 1);
    num_sets = size;
  }
  int find_set(int i) { return (p[i] == i) ? i : (p[i] = find_set(p[i])); }
  bool same_set(int i, int j) { return find_set(i) == find_set(j); }
  void union_set(int i, int j) {
    if (find_set(i) != find_set(j)) {
      if (r[p[i]] > r[p[j]])
        p[p[j]] = p[i], r[p[i]] += r[p[j]], r[p[j]] = 0;
      else
        p[p[i]] = p[j], r[p[j]] += r[p[i]], r[p[i]] = 0;
      num_sets--;
    }
  }
};

vec<ii> tree[MAXN];
bool seen[MAXN];
vec<tiii> edges;
map<string, int> s2ind;
dsu mst;

int get_minimax(int u, int tgt, int min_e = INF) {
  seen[u] = true;
  int ret_val = INF;
  for (ii v : tree[u]) {
    if (v.se == tgt)
      return min(min_e, v.fi);
    if (!seen[v.se])
      ret_val = min(get_minimax(v.se, tgt, min(min_e, v.fi)), ret_val);
  }

  return ret_val;
}

void kruskal() {
  sort(edges.begin(), edges.end(), greater<tiii>());
  for (tiii e : edges) {
    int src = e[1], dst = e[2], w = e[0];
    if (!mst.same_set(src, dst)) {
      // d(dst), d(src);
      // cout <<"----" << el;
      mst.union_set(src, dst);
      tree[src].pb(ii(w, dst));
      tree[dst].pb(ii(w, src));
    }
  }
}

int main() {
  int cases = 0;
  int n, r;
  cin >> n >> r;
  while (n || r) {
    forn(i, n) tree[i].clear();
    memset(seen, false, sizeof seen);
    edges.clear();
    s2ind.clear();
    mst.init(n);

    int cur_ind = 0;
    string src, dst;
    forn(i, r) {
      int w;
      cin >> src >> dst >> w;
      if (!s2ind.count(src))
        s2ind[src] = cur_ind++;
      if (!s2ind.count(dst))
        s2ind[dst] = cur_ind++;
      edges.pb(tiii(w, s2ind[src], s2ind[dst]));
    }
    kruskal();
    cin >> src >> dst;
    if (!s2ind.count(src))
      s2ind[src] = cur_ind++;
    if (!s2ind.count(dst))
      s2ind[dst] = cur_ind++;

    // d(s2ind[src]), d(s2ind[dst]);

    int res = get_minimax(s2ind[src], s2ind[dst]);

    printf("Scenario #%i\n", ++cases);
    cout << res << " tons\n" << el;
    cin >> n >> r;
  }
}
