#include <bits/stdc++.h>
using namespace std;

/*
  Clean implementation of:
  Euler Tour + Segment Trees + RMQ-on-Euler for LCA
  - Each tree edge appears twice in `edgeTour`.
  - We maintain two segment trees (A and B) over edgeTour indexes.
  - Query for painted edges on path u-v:
       l = LCA(u,v)
       answer = countInRange(first[u], first[v]-1, treeA) - countInRange(first[u], first[v]-1, treeB)
                applied for (l,u) and (l,v) parts as in original pattern:
       result = queryBetween(l, u) + queryBetween(l, v)
*/

using vi = vector<int>;
using vvi = vector<vi>;

int n;                      // number of nodes
vvi graphAdj;               // adjacency: neighbors
vvi graphEdgeId;            // adjacency: corresponding edge ids for each neighbor

vi vertexTour;              // dfs_list: Euler tour of vertices (push on enter and on return)
vi edgeTour;                // edges_list: sequence of edge-ids traversed (each edge appears twice)
vi depthArr;                // depth per node (root depth = 1)
vi firstOcc;                // first occurrence index of each vertex in vertexTour (index into vertexTour)

// segment tree for LCA over vertexTour (stores node id with minimal depth)
vi lcaSegTree;

// per-edge first and second occurrence indices in edgeTour
vi edgeFirstIdx, edgeSecondIdx;
// state of edges: 0 = unpainted, 1 = painted
vector<char> edgeActive;

// two segment trees (over positions of edgeTour) used as in original trick
vi segTreeA, segTreeB;

// ----------------------- DFS Euler tour -----------------------
void dfs_build(int v, int parent, int curDepth = 1) {
    depthArr[v] = curDepth;
    vertexTour.push_back(v);

    for (size_t i = 0; i < graphAdj[v].size(); ++i) {
        int to = graphAdj[v][i];
        int eid = graphEdgeId[v][i];
        if (to == parent) continue;
        edgeTour.push_back(eid);          // first time we traverse this edge (down)
        dfs_build(to, v, curDepth + 1);
        edgeTour.push_back(eid);          // second time (back up)
        vertexTour.push_back(v);          // returning visit to v
    }
}

// ----------------------- LCA segment tree (RMQ by depth) -----------------------
void buildLcaSeg(int idx, int l, int r) {
    if (l == r) {
        lcaSegTree[idx] = vertexTour[l];
        return;
    }
    int m = (l + r) >> 1;
    buildLcaSeg(idx << 1, l, m); // idx << 1   ==> 2*idx
    buildLcaSeg(idx << 1 | 1, m + 1, r); // idx << 1 | 1 ==> 2*idx + 1
    int leftNode = lcaSegTree[idx << 1];
    int rightNode = lcaSegTree[idx << 1 | 1];
    lcaSegTree[idx] = (depthArr[leftNode] < depthArr[rightNode]) ? leftNode : rightNode;
}

int queryLcaSeg(int idx, int tl, int tr, int l, int r) {
    if (l > r) return -1;
    if (tl == l && tr == r) return lcaSegTree[idx];
    int m = (tl + tr) >> 1;
    if (r <= m) return queryLcaSeg(idx << 1, tl, m, l, r);
    if (l > m)  return queryLcaSeg(idx << 1 | 1, m + 1, tr, l, r);
    int leftNode = queryLcaSeg(idx << 1, tl, m, l, m);
    int rightNode = queryLcaSeg(idx << 1 | 1, m + 1, tr, m + 1, r);
    if (leftNode == -1) return rightNode;
    if (rightNode == -1) return leftNode;
    return (depthArr[leftNode] < depthArr[rightNode]) ? leftNode : rightNode;
}

int getLCA(int a, int b) {
    if (firstOcc[a] > firstOcc[b]) swap(a, b);
    return queryLcaSeg(1, 0, (int)vertexTour.size() - 1, firstOcc[a], firstOcc[b]);
}

// ----------------------- Segment tree over edgeTour (point update, range sum) -----------------------
void segPointUpdate(vi &tree, int idx, int tl, int tr, int pos, int delta) {
    tree[idx] += delta;
    if (tl == tr) return;
    int m = (tl + tr) >> 1;
    if (pos <= m) segPointUpdate(tree, idx << 1, tl, m, pos, delta);
    else           segPointUpdate(tree, idx << 1 | 1, m + 1, tr, pos, delta);
}

int segRangeQuery(const vi &tree, int idx, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (tl == l && tr == r) return tree[idx];
    int m = (tl + tr) >> 1;
    if (r <= m) return segRangeQuery(tree, idx << 1, tl, m, l, r);
    if (l > m)  return segRangeQuery(tree, idx << 1 | 1, m + 1, tr, l, r);
    return segRangeQuery(tree, idx << 1, tl, m, l, m) + segRangeQuery(tree, idx << 1 | 1, m + 1, tr, m + 1, r);
}

// Query counts on a contiguous section of edgeTour:
// note: edges on path between nodes a and b correspond to interval [first[a], first[b]-1] on edgeTour (assuming first[a] <= first[b])
int queryEdgeIntervalCount(int leftNodeFirstIdx, int rightNodeFirstIdxMinusOne) {
    if (leftNodeFirstIdx > rightNodeFirstIdxMinusOne) return 0;
    int L = leftNodeFirstIdx;
    int R = rightNodeFirstIdxMinusOne;
    int aCount = segRangeQuery(segTreeA, 1, 0, (int)edgeTour.size() - 1, L, R);
    int bCount = segRangeQuery(segTreeB, 1, 0, (int)edgeTour.size() - 1, L, R);
    return aCount - bCount;
}

// Query painted edges on path from ancestor `anc` to `desc` (exclusive anc, inclusive desc)
// This uses original trick: interval on edgeTour is [ firstOcc[anc], firstOcc[desc]-1 ]
int queryPathFromAncestorToNode(int anc, int desc) {
    if (anc == desc) return 0;
    int l = firstOcc[anc];
    int r = firstOcc[desc] - 1;
    if (l > r) swap(l, r);
    return queryEdgeIntervalCount(l, r);
}

// Overall path query between u and v: split by LCA
int queryPaintedEdgesOnPath(int u, int v) {
    int l = getLCA(u, v);
    return queryPathFromAncestorToNode(l, u) + queryPathFromAncestorToNode(l, v);
}

// ----------------------- Main -----------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    graphAdj.assign(n, vi());
    graphEdgeId.assign(n, vi());

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        graphAdj[u].push_back(v);
        graphAdj[v].push_back(u);
        graphEdgeId[u].push_back(i);
        graphEdgeId[v].push_back(i);
    }

    // prepare containers
    depthArr.assign(n, -1);
    vertexTour.clear();
    edgeTour.clear();

    // root at 0 and run Euler DFS
    dfs_build(0, -1, 1);

    // build LCA RMQ structure
    lcaSegTree.assign(max(1, (int)vertexTour.size()) * 4, -1);
    buildLcaSeg(1, 0, (int)vertexTour.size() - 1);

    // first occurrence of each vertex in vertexTour
    firstOcc.assign(n, -1);
    for (int i = 0; i < (int)vertexTour.size(); ++i) {
        int v = vertexTour[i];
        if (firstOcc[v] == -1) firstOcc[v] = i;
    }

    // prepare edge occurrence indices (each edge has two positions in edgeTour)
    int m = (int)edgeTour.size();         // should be 2*(n-1)
    edgeFirstIdx.assign(n - 1, -1); // total number of edges in a tree = n-1
    edgeSecondIdx.assign(n - 1, -1);
    for (int i = 0; i < m; ++i) {
        int e = edgeTour[i];
        if (edgeFirstIdx[e] == -1) edgeFirstIdx[e] = i;
        else                       edgeSecondIdx[e] = i;
    }

    // sanity check (optional in contest)
    // for (int e = 0; e < n-1; ++e) if (edgeFirstIdx[e] == -1 || edgeSecondIdx[e] == -1) cerr << "edge missing occurrence\n";

    // init segment trees for edges
    segTreeA.assign(max(1, m) * 4, 0);
    segTreeB.assign(max(1, m) * 4, 0);
    edgeActive.assign(n - 1, 0); // which state edge is in

    // queries
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            // update: paint/unpaint edge x (1-based), state s (0 or 1)
            int x, s;
            cin >> x >> s;
            --x; // to 0-based edge-id
            if (x < 0 || x >= n - 1) continue;
            if (edgeActive[x] == s) continue; // no-op (already in same state)

            int delta = s ? +1 : -1;  // delta is the value by which we change the segment tree counts.
            // update segment trees at both occurrences
            segPointUpdate(segTreeA, 1, 0, m - 1, edgeFirstIdx[x], delta);
            segPointUpdate(segTreeB, 1, 0, m - 1, edgeSecondIdx[x], delta);
            edgeActive[x] = (char)s;
        } else if (type == 2) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            int answer = queryPaintedEdgesOnPath(u, v);
            cout << answer << '\n';
        } else {
            // unknown type — ignore or handle as needed
        }
    }

    return 0;
}





// To understand this ask chatgpt to dry run with one example