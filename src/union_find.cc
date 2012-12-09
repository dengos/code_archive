/**
 * ===========================================================================
 *
 *          @file  find_catch.cc
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  12/08/2012 10:13:19 AM
 *
 * ===========================================================================
 */



#include <cstdio>
#include <cstdlib>
#include <vector>

using std::vector;

static int MAXN = 100000;


/**
 * @brief The basic version of union_find data structure, with 
 * path compression.
 * Do remember, union-find is a very powerfull data structure.
 * Sometime, you need to modify the data-structure a lit bit, and
 * keep the find operation with path compression and data update.
 *
 * Notice that, for simplity, I use the std::vector for basic union
 * trace. And before use, you need init the whole data structure with
 * parameter N.
 */
struct union_find 
{
    int size;
    vector<int> tree;
    union_find(): size(0) { tree.reserve(MAXN + 1); }

    void init(int N)
    {
        if (N > MAXN)   tree.reserve(N);
        size = N;
        for ( int i = 0; i < N; ++i ) 
            tree[i] = i;
    }

    int find(int a)
    {
        return tree[a] == a ? a : tree[a] = find(tree[a]);
    }

    bool is_connected(int a, int b)
    {
        return find(a) == find(b);
    }

    void connect(int a, int b)
    {
        if (is_connected(a, b))     return;
        tree[find(a)] = find(b);
    }

};				/* ----------  end of struct union_find  ------ */



