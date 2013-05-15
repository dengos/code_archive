/**
 * ===========================================================================
 *
 *          @file  tree_travel.cc
 *         @brief  
 *
 *        @author  dengos (w), dengos.w@gmail.com, scut
 *       @version  1.0
 *          @date  05/15/2013 02:31:01 PM
 *
 * ===========================================================================
 */

#include <cstdlib>
#include <cassert>
#include <stack>
#include <bitset>
#include <iostream>

using std::stack;
using std::bitset;
using std::cout;
using std::endl;


template <typename T>
struct binary_tree 
{
    binary_tree(): lchild(NULL), rchild(NULL) {}
    binary_tree(T v): value(v), lchild(NULL), rchild(NULL) {}

    T value;
    binary_tree<T> *lchild;
    binary_tree<T> *rchild;
};				/* ----------  end of struct binary_tree  ------ */




template <typename T>
void
preorder_recur ( binary_tree<T> *node, void (*tfunc)(binary_tree<T> *node) )
{
    if (node == NULL)   return;
    tfunc(node);
    preorder_recur(node->lchild, tfunc);
    preorder_recur(node->rchild, tfunc);
}		/* -----  end of function preorder_recur  ----- */


template <typename T>

void
preorder ( binary_tree<T> *root, void (*tfunc)(binary_tree<T> *node) )
{
    if (root == NULL)   return;

    stack<binary_tree<T> *> history; 
    binary_tree<T> *node = NULL;
    
    tfunc(root);
    history.push(root);
    node = root->lchild;
    while (!history.empty() || node != NULL)
    {
        while (node != NULL)
        {
            tfunc(node);
            history.push(node);
            node = node->lchild;
        }

        if (!history.empty())
        {
            node = history.top();
            history.pop();
            node = node->rchild;
        }
    }


}		/* -----  end of function preorder  ----- */


template <typename T>
void
inorder_recur ( binary_tree<T> *node, void (*tfunc)(binary_tree<T> *node) )
{
    if (node == NULL) return;
    inorder_recur(node->lchild, tfunc);
    tfunc(node);
    inorder_recur(node->rchild, tfunc);
}		/* -----  end of function inorder_recur  ----- */


template <typename T>
void
inorder ( binary_tree<T> *root, void(*tfunc)(binary_tree<T> *node) )
{
    if (root == NULL)   return;

    stack<binary_tree<T> *> history;
    binary_tree<T> *node = NULL;
    history.push(root);
    node = root->lchild;

    while (!history.empty() || node != NULL)
    {
        while (node != NULL)
        {
            history.push(node);
            node = node->lchild;
        }

        if (!history.empty())
        {
            node = history.top();
            history.pop();
            tfunc(node);
            node = node->rchild;
        }
    }

}		/* -----  end of function inorder  ----- */


template <typename T>
void
postorder_recur ( binary_tree<T> *node, void (*tfunc)(binary_tree<T> *node) )
{
    if (node == NULL)   return;
    postorder_recur(node->lchild, tfunc);
    postorder_recur(node->rchild, tfunc);
    tfunc(node);
}		/* -----  end of function postorder_recur  ----- */


template <typename T>
void
postorder ( binary_tree<T> *root, void (*tfunc)(binary_tree<T> *node) )
{
    if (root == NULL)   return;
    
    typedef char tstate;
    enum
    {
        TSTATE_EMPTY = 0,
        TSTATE_LVISIT = 1,
        TSTATE_RVISIT = 2
    };

    stack<binary_tree<T> *> history;
    stack<tstate> hist_state;
    tstate state;
    binary_tree<T> *node = NULL;

    history.push(root);
    hist_state.push(TSTATE_EMPTY);
    while (!history.empty())
    {
        node = history.top();
        state = hist_state.top();
        if (node == NULL)
        {
            history.pop();
            hist_state.pop();
            continue;
        }

        switch ( state ) 
        {
            case TSTATE_EMPTY:	
                history.push(node->lchild);
                hist_state.pop();
                hist_state.push(TSTATE_LVISIT);
                hist_state.push(TSTATE_EMPTY);
                break;

            case TSTATE_LVISIT:	
                history.push(node->rchild);
                hist_state.pop();
                hist_state.push(TSTATE_RVISIT);
                hist_state.push(TSTATE_EMPTY);
                break;

            case TSTATE_RVISIT:	
                tfunc(node);
                history.pop();
                hist_state.pop();
                break;

            default:	
                assert(false);
                break;
        }				/* -----  end switch  ----- */
    }

}		/* -----  end of function postorder  ----- */



template <typename T>
void
print_node ( binary_tree<T> *node )
{
    cout << node->value << " ";
}		/* -----  end of function print_node  ----- */

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
    typedef binary_tree<int> ibinary_tree;
    ibinary_tree *root = new ibinary_tree(10);
    root->lchild = new ibinary_tree(3);
    root->rchild = new ibinary_tree(15);

    cout << "pre order" << endl;
    preorder_recur(root, print_node);
    cout << endl;
    preorder(root, print_node);
    cout << endl;
    cout << "in order" << endl;
    inorder_recur(root, print_node);
    cout << endl;
    inorder(root, print_node);
    cout << endl;
    cout << "post order" << endl;
    postorder_recur(root, print_node);
    cout << endl;
    postorder(root, print_node);
    cout << endl;

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


