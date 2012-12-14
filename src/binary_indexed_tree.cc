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
 * 1. Usally, we don't really use the index 0 in binary indexed tree. which affect the 
 * frequnces array using for construction BinaryIndexedTree too. By default, we 
 * think tree[0] = 0, and frequnces[0] = 0;
 *
 * 2. You should call the member function BinaryIndexedTree::build, right after you create
 * a binary indexed tree, which will perform the post-initializatio.
 */
class BinaryIndexedTree 
{
    public:
        BinaryIndexedTree(): size(0) { }

        /**
         * @brief The frequnces vector need based on index 1.
         *
         * @param frequnces
         * @param N
         */
        void build(const vector<int> &frequnces, int N)
        {
            int i;
            vector<int> cumulate;
            cumulate.resize(N + 1, 0);
            for ( i = 1; i <= N; ++i ) 
                cumulate[i] = cumulate[i - 1] + frequnces[i];

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

    private:
        int size;
        vector<int> tree;
};				/* ----------  end of struct BinaryIndexedTree  ------ */



/**
 * @brief Read the documation of BinaryIndexedTree first, they are basically
 * the same.
 */
class BinaryIndexedTree2D
{
    public:
        BinaryIndexedTree2D (): XMAX(0), YMAX(0) {}                             /* constructor */

        void build(const vector<int> &frequnces, int xmax, int ymax)
        {
            XMAX = xmax; YMAX = ymax;
            int i, j;
            vector<int> cumulate2d;
            cumulate2d.resize((XMAX + 1) * (YMAX + 1), 0);

            tree2d.swap(cumulate2d);
            for ( i = 1; i <= YMAX; ++i ) 
                for ( j = 1; j <= XMAX; ++j ) 
                    set(j, i, get(j-1, i) + get(j, i-1) + frequnces[i*XMAX + j] - get(j-1, i-1));
            cumulate2d.swap(tree2d);
            
            tree2d.resize(cumulate2d.size(), 0);

            int base_i, base_j;
            for ( i = 1; i <= YMAX; ++i ) 
            {
                base_i = (i & -i);
                for ( j = 1; j <= XMAX; ++j ) 
                {
                    base_j = (j & -j);
                    set(
                        j , i, 
                        cumulate2d[i*XMAX + j] + cumulate2d[(i-base_i)*XMAX + (j-base_j)]
                            - cumulate2d[(i-base_i)*XMAX + j] - cumulate2d[i*XMAX + (j-base_j)]);
                }
            }
        }

        int query(int x, int y)
        {
            assert(x > 0 && x <= XMAX && y > 0 && y<=YMAX);
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
            assert( x > 0 && x <= XMAX && y > 0 && y <= YMAX );
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

    private:
        int get(int x, int y)
        {
            return tree2d[y * XMAX + X];
        }

        void set(int x, int y, int val)
        {
            tree2d[y * XMAX + x] = val;
        }

    private:
        int XMAX;
        int YMAX;
        vector<int> tree2d;
}; /* -----  end of struct BinaryIndexedTree2D  ----- */


