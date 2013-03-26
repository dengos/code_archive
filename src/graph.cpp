/**
 * ===========================================================================
 *
 *          @file  graph.cpp
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  03/26/2013 12:59:32 PM
 *
 * ===========================================================================
 */



#include <vector>


using std::vector;


struct edge
{
    edge(int u, int v, int w): from(u), to(v), weight(w) {}
    int from;
    int to;
    int weight;
} ;


struct link
{
    link(int v, int id): to(v), prev(id) {}
    int to;
    int prev;
} ;


/**
 * @brief 
 * This is a adjacency list implementation. [ref: CS97SI - basic graph algorithm]
 * 
 * Solution 1. using linked lists
 *      too much memory/time overhead;
 *      using dynamic allocated memory or pointeres is bad;
 *      also, in competetion, using std::list usually lead to TLE;
 * Solution 2. using a array of vectors
 *      easier to code, no bad memory issues;
 *      but very slow; // indeed, but still fast than list usually.
 * Solution 3. using arrays
 *      assuming the total number of edges is known
 *      very fast and memory-efficient
 *
 * This implementation is based on solution 3.
 */


/**
 * @brief 
 */
class adjacency_list
{
    public:
        adjacency_list (int n, vector<edge> &edges)
        {
            int m = edges.size();
            quick_table.resize(n+1);
            link_stack.resize(m+1);
            construct(edges);
        }/* constructor */

        inline void begin(int &link_id)
        {
            link_id = 0;
        }
        /**
         * @brief 
         * 1. link_id = 0 for the begin of iteration;
         * 2. return 0 if iterator reach the end;
         *
         */
        int next(int u, int &link_id)
        {
            if (link_id == 0) 
            {
                link_id = quick_table[u];
                return link_stack[link_id].to;
            }
            link_id = link_stack[link_id].prev;
            return link_stack[link_id].to;
        }

    protected:
        void construct(vector<edge> &edges)
        {
            int i, m = edges.size();
            int from, to, link_id;
            
            for ( i = 0; i < m; ++i ) 
            {
                from = edges[i].from; to = edges[i].to; 
                link_id = i+1;

                link_stack[link_id].to = to;
                link_stack[link_id].prev = quick_table[from];
                quick_table[from] = link_id;
            }
        }

    private:
        vector<int>  quick_table;
        vector<link> link_stack;
}; /* -----  end of class adjacency_list  ----- */


