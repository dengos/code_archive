/**
 * ===========================================================================
 *
 *          @file  frequnces.cc
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  12/09/2012 11:23:22 AM
 *
 * ===========================================================================
 */




#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>


using std::vector;


/**
 * @brief The const int number for poj used. Not need such large integer in any
 * other application rather then poj.
 */
static const int MAXN = 100000;

/**
 * @brief Notice that there is a machine dependent operation, which is to find the 
 * 2 to the left of the first set bit: (idx & -idx).
 * To see more explantion:
 * http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
 * 
 * As boba5551 explain in this tutorial, by using binary indexed tree, we achieve
 * <O(N), O(logN)> for range sum query, the update operation in particular node is O(logN)
 * too.
 *
 * Important!!!
 * usally, we don't really use the index 0 in binary indexed tree. which affect the 
 * frequnces array using for construction BinaryIndexedTree too. By default, we 
 * think tree[0] = 0, and frequnces[0] = 0;
 */
struct BinaryIndexedTree 
{
    int size;
    vector<int> tree;

    BinaryIndexedTree(): size(0) 
    {
        tree.reserve(MAXN + 1);
    }

    /**
     * @brief The frequnces vector need based on index 1.
     *
     * @param frequnces
     * @param N
     */
    void build_tree(const vector<int> &frequnces, int N)
    {
        int i;
        vector<int> cumulate;
        cumulate.reserve(N + 1);
        cumulate[0] = 0;
        for ( i = 1; i <= N; ++i ) 
            cumulate[i] = frequnces[i] ? cumulate[i-1] + 1 : cumulate[i-1];

        tree.resize(N + 1);
        tree[0] = 0;
        for ( i = 1; i <= N; ++i ) 
            tree[i] = cumulate[i] - cumulate[i - (i & -i)];
        size = N;
    }

    int query(int idx)
    {
        assert(idx <= size);
        int sum = 0;
        while (idx > 0)
        {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    void update(int idx, int val)
    {
        assert(idx <= size);
        while (idx <= size)
        {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

};				/* ----------  end of struct BinaryIndexedTree  ------ */



/**
 * @brief 
 */
struct BinaryIndexedTree2D
{
    int XMAX;
    int YMAX;
    vector<int> tree2d;

    BinaryIndexedTree2D (): XMAX(0), YMAX(0) {}                             /* constructor */

    int &at(int x, int y)
    {
        return tree2d[y * XMAX + x];
    }

    int get(int x, int y)
    {
        return tree2d[y * XMAX + X];
    }

    void set(int x, int y, int val)
    {
        tree2d[y * XMAX + x] = val;
    }

    int query(int x, int y)
    {
        int sum = 0;
        int idx;
        while (y > 0)
        {
            idx = x;
            while (idx > 0)
            {
                sum += get(idx, y);
                idx -= (idx & -idx);
            }
            y -= (y & -y);
        }
    }

    void update(int x, int y, int val)
    {
        int idx;
        while (y <= YMAX)
        {
            idx = x;
            while (idx <= XMAX)
            {
                set(idx, y, get(idx, y) + val); 
                idx += (idx & -idx);
            }
            y += (y & -y);
        }
    }

}; /* -----  end of struct BinaryIndexedTree2D  ----- */


