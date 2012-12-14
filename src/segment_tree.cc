/**
 * ===========================================================================
 *
 *          @file  segment_tree.cc
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  12/14/2012 01:09:18 PM
 *
 * ===========================================================================
 */

#include <vector>
#include <algorithm>
#include <limits>

using std::vector;
using std::swap;
using std::numeric_limits;

/**
 * @brief A simple version of segment tree for range minium query.
 * Notice that, in this version, I don't use the indexed of values
 * as the segment tree node, but you might aware that for RMQ, the
 * indexed node is much better implementation.
 * The main purpose of this segment-tree, is to set-up the basic idea
 * or structure of segment tree, using the idea that you can store
 * whatever you want as a segment tree node, then using the basic
 * init_leaf and combine_node operation.
 */
class SegmentTree
{
    public:
        SegmentTree (): N(0) {}                             /* constructor */

        void build(const vector<int> &values)
        {
            N = values.size();
            int left_most_bit = 1;
            while ((1 << left_most_bit) <= N) ++left_most_bit;
            --left_most_bit;
            tree.resize((1 << (left_most_bit + 2)) + 1, numeric_limits<int>::max());
            recursive_build(1, 0, N-1, values);     
        }

        void update(int index, int value)
        {
            assert(index < N && index >= 0);
            recursive_update(1, 0, N-1, index, value);
        }

        int query(int i, int j)
        {
            if (i > j)  swap(i, j);
            assert(i >= 0 && j < N);
            return recursive_query(1, 0, N-1, i, j);
        }

    protected:

        void init_leaf(int node, int value)
        {
            tree[node] = value;
        }

        int combine_node(int parent, int lchild, int rchild)
        {
            return tree[parent] = tree[lchild] < tree[rchild] ? tree[lchild] : tree[rchild]; 
        }

        void recursive_build(int node, int begin, int end, const vector<int> &values)
        {
            if (begin == end)
                init_leaf(node, values[begin]);
            else
            {
                recursive_build(node << 1, begin, (begin + end) >> 1, values);
                recursive_build((node << 1) + 1, ((begin + end) >> 1) + 1, end, values);
                combine_node(node, node << 1, (node << 1) + 1);
            }
        }

        void recursive_update(int node, int begin, int end, int index, int value)
        {
            if (index < begin || index > end)       return;
            if (begin == end)
                init_leaf(node, value);
            else
            {
                update(node << 1, begin, (begin + end) >> 1, index, value);
                update((node << 1) + 1, ((begin + end) >> 1) + 1, end, index, value);
                combine_node(node, node << 1, (node << 1) + 1);
            }
        }

        int recursive_query(int node, int begin, int end, int i, int j)
        {
            if (i > end || j < begin)       return numeric_limits<int>::max();
            if (begin >= i && end <= j)     return tree[node];

            int lmin = query(node << 1, begin, (begin + end) >> 1, i, j);
            int rmin = query((node << 1) + 1, ((begin + end) >> 1 + 1), end, i, j);
            return lmin < rmin ? lmin : rmin;
        }

    private:
        int N;
        vector<int> tree;

}; /* -----  end of class SegmentTree  ----- */


