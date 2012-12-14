code_archive
============


This code archive is major in c++. There will be some basic algorithm code, feel free to check out if you like.

1. trie  
A simple version of data structure trie.
If you interset in trie, follow the link below:   
http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=usingTries  
For more about trie and hash, the wikipedia link below is good for start:   
http://en.wikipedia.org/wiki/Trie  

2. union find
Union find is super powerfull for set query. 

3. binary indexed tree
A binary indexed tree(BIT) struct implementation based on std::vector.  
The goodie about BIT, is that it only take O(N) complexity for constructing, which cost O(N) memory too. 
The update and query operation can be done in O(logN) time.  
More specifically, my bit code is based on top-coder algorithm tutorials.
To see more about BIT:  
http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees  


4. segment tree
A simple version of segment tree. Notice that this implementation is armed for basic range minimum query, 
the main idea is from following tutorial.  
http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lowestCommonAncestor#Lowest Common Ancestor (LCA)
But with slight difference, I using the minimum value as the node of segment tree, which of cause won't be a 
optimal solution for RMQ. As describe in previous tutorial, the indexed way is much better. But the main idea
here is to illustrate that segment tree is a very powerfull data structure, you can use whatever you want as
the node of segment tree, but keep the invariance!!!

Author
============
name :   dengos  
email:   dengos.w@gmail.com  
blog :   http://dengos.me  

