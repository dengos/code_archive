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
 * @brief A rather simple version of trie_node for string check.
 * Since A-B may be not the only care in string processing. I use 
 * contain std::vector for simple use. You can port whatever trie_node
 * structure you want, under the interface:
 *      1. find the next trie_node given by char c. If don't exist, return NULL.
 *      ---> trie_node *find_next(char c)
 *      2. check whether they exist trie_node associate with char c, if not, 
 *      create a new node for char c, return the pointer to such node.
 *      ---> trie_node *insert(char c)
 */
struct trie_node 
{ 
    typedef vector<trie_node *> node_vector;

    char key;
    int value;
    // I use vector for simplify, you may change for performance.
    vector<trie_node *> children;

    trie_node(char c): key(c), value(0) {}
    ~trie_node()
    {
        for ( vector<trie_node *>::iterator iter = children.begin(); 
                iter != children.end(); ++iter ) 
            delete *iter;
    }

    trie_node *find_next(char c)
    {
        for ( node_vector::iterator iter = children.begin(); 
                iter != children.end(); ++iter ) 
            if ((*iter)->key == c)
                return *iter;
        return NULL;
    }

    trie_node *insert(char c)
    {
        trie_node *nnode = new trie_node(c);
        children.push_back(nnode);
        return nnode;
    }
};				/* ----------  end of struct trie_node  ------ */


class trie
{
public:
    trie(): root(0){};
    ~trie() {};

    trie_node *find(const string &name)
    {
        trie_node *node = &root;

        for ( string::const_iterator iter = name.begin(); 
                iter != name.end(); ++iter ) 
            if ((node = node->find_next(*iter)) == NULL)
                break;
        return node;
    }

    trie_node *insert(const string &name)
    {
        trie_node *prev = &root;
        trie_node *node = NULL;

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
    trie_node root;
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
    trie_node *node = NULL;
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









