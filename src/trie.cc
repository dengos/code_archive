/**
 * ===========================================================================
 *
 *          @file  trie.cc
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  12/02/2012 10:18:23 PM
 *
 * ===========================================================================
 */



#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>


using std::vector;
using std::string;



/**
 * @brief A rather simple version of TrieNode for string check.
 * Since A-B may be not the only care in string processing. I use 
 * contain std::vector for simple use. You can port whatever TrieNode
 * structure you want, under the interface:
 *      1. find the next TrieNode given by char c. If don't exist, return NULL.
 *      ---> TrieNode *find_next(char c)
 *      2. check whether they exist TrieNode associate with char c, if not, 
 *      create a new node for char c, return the pointer to such node.
 *      ---> TrieNode *insert(char c)
 */
struct TrieNode 
{ 
    typedef vector<TrieNode *> node_vector;

    char key;
    int value;
    // I use vector for simplify, you may change for performance.
    vector<TrieNode *> children;

    TrieNode(char c): key(c), value(0) {}
    ~TrieNode()
    {
        for ( vector<TrieNode *>::iterator iter = children.begin(); 
                iter != children.end(); ++iter ) 
            delete *iter;
    }

    TrieNode *find_next(char c)
    {
        for ( node_vector::iterator iter = children.begin(); 
                iter != children.end(); ++iter ) 
            if ((*iter)->key == c)
                return *iter;
        return NULL;
    }

    TrieNode *insert(char c)
    {
        TrieNode *nnode = new TrieNode(c);
        children.push_back(nnode);
        return nnode;
    }
};				/* ----------  end of struct TrieNode  ------ */


class Trie
{
    public:
        Trie(): root(0){};
        ~Trie() {};

        TrieNode *find(const string &name)
        {
            TrieNode *node = &root;

            for ( string::const_iterator iter = name.begin(); 
                    iter != name.end(); ++iter ) 
                if ((node = node->find_next(*iter)) == NULL)
                    break;
            return node;
        }

        TrieNode *insert(const string &name)
        {
            TrieNode *prev = &root;
            TrieNode *node = NULL;

            for ( string::const_iterator iter = name.begin(); 
                    iter != name.end(); ++iter ) 
            {
                if ((node = prev->find_next(*iter)) == NULL)
                    node = prev->insert(*iter);
                prev = node;
            }

            return node;
        }

    private:
        TrieNode root;
};







/**
 * @brief
 *
 * @param argc
 * @param argv[]
 *
 * @return 0 if ok.
 */
    int
main ( int argc, char *argv[] )
{
    trie t;
    TrieNode *node = NULL;
    node = t.insert(string("abc"));
    node->value = 10;
    node = t.insert(string("abdd"));
    node->value = 11;

    node = t.find(string("abc"));
    printf ( "%d\n", node->value );
    node = t.find(string("abdd"));
    printf ( "%d\n", node->value );
    node = t.find(string("abd"));
    if (node != NULL)
        printf ( "%d\n", node->value );

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */









