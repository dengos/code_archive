/**
 * ===========================================================================
 *
 *          @file  heap.cc
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  12/14/2012 02:33:19 PM
 *
 * ===========================================================================
 */

#include <vector>
#include <algorithm>

using std::vector;
using std::swap;



struct HeapNode 
{
    int key;
    // you may want to keep other extra information about the heap node.
};				/* ----------  end of struct HeapNode  ------ */



bool operator > (const HeapNode &a, const HeapNode &b)
{
    return a.key > b.key;
}



/**
 * @brief This is a restricted implementation of advance heap. You may
 * expected O(1) top operation, O(logN) pop_front operation, O(logN)
 * update operation.
 *
 * Important:
 * Notice, we don't expected any new HeapNode after the first construction, 
 * which by calling the build function. More over, node that have leave the
 * heap by pop_front function, will not be welcome any more.
 * The update function only take care of the node that current in the heap,
 * no more else.
 */
class HeapWithUpdate
{
    public:
        HeapWithUpdate (): N(0) {}                             /* constructor */


        /**
         * @brief Not O(N) efficent as you may expected from common heapify 
         * operation. This simple build function iterater call O(logN) push
         * back function to construct the heap.
         *
         * @param values
         */
        void build(const vector<HeapNode> &values)
        {
            N = values.size();
            heap.reserve(N + 1);
            idx_map_heap.resize(N, 0);
            heap_map_idx.resize(N + 1, -1);
            
            for ( int i = 0; i < N; ++i ) 
            {
                idx_map_heap[i] = i+1;
                heap_map_idx[i+1] = i;
            }

            for ( int i = 0; i < N; ++i ) 
                push_back(i, values[i]);
        }

        const HeapNode &top()
        {
            return heap[1];
        }
        
        void pop_front()
        {
            heap[1] = heap[heap.size() - 1];
            idx_map_heap[heap_map_idx[1]] = 0;
            idx_map_heap[heap_map_idx[heap.size() - 1]] = 1;
            heap_map_idx[1] = heap_map_idx[heap.size() - 1];
            heap_map_idx[heap.size() - 1] = -1;
            heap.pop_back();
            bubble_down(1);
        }

        void update(int index, const HeapNode &value)
        {
            assert(index < N);
            if (idx_map_heap[index] == 0)   return; // have been remove from the heap
            if (value > heap[idx_map_heap[index]])
            {
                heap[idx_map_heap[index]] = value;
                bubble_up(idx_map_heap[index] >> 1);
            }
        }

    protected:


        /**
         * @brief Close the push_back interface from public. Since we assume
         * that they won't have any more new node after the first build.
         *
         * @param index
         * @param value
         */
        void push_back(int index, const HeapNode &value)
        {
            heap.push_back(value);
            idx_map_heap[index] = heap.size() - 1;
            bubble_up((heap.size() - 1) >> 1);
        }

        int bubble_swap(int parent)
        {
            int lchild = parent << 1;
            int rchild = (parent << 1) + 1;
            int mchild;
            
            if (rchild <= heap.size())
                mchild = heap[lchild] > heap[rchild] ? lchild : rchild;
            else
                mchild = lchild;

            if (mchild <= heap.size() && heap[mchild] > heap[parent])
            {
                swap(heap[mchild], heap[parent]);
                swap(heap_map_idx[mchild], heap_map_idx[parent]);
                idx_map_heap[heap_map_idx[mchild]] = mchild;
                idx_map_heap[heap_map_idx[parent]] = parent;
            }
            else
                mchild = parent;
            return mchild;
        }

        void bubble_up(int parent)
        {
            if (parent == 0)    return;
            int child = buble_swap(parent);
            if (child != parent)  buble_up(parent >> 1);
        }

        void bubble_down(int parent)
        {
            if (parent >= heap.size())  return;
            int child = bubble_swap(parent);
            if (child != parent)        bubble_down(child);
        }

    private:
        int N;
        vector<HeapNode> heap;
        vector<int> idx_map_heap;
        vector<int> heap_map_idx;
}; /* -----  end of class HeapWithUpdate  ----- */


