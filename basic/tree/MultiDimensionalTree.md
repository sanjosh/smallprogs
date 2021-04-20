

http://stackoverflow.com/questions/17466218/what-are-the-differences-between-segment-trees-interval-trees-binary-indexed-t?rq=1

http://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/


    * Segment tree stores intervals, and optimized for "which of these intervals contains a given point" queries.
    * Interval tree stores intervals as well, but optimized for "which of these intervals overlap with a given interval" queries. It can also be used for point queries - similar to segment tree.
    * Range tree stores points, and optimized for "which points fall within a given interval" queries.
    * Binary indexed tree stores items-count per index, and optimized for "how many items are there between index m and n" queries.

    QuadTree : for spatial index, collision detection

    OctTree : 3D analog

Performance / Space consumption for one dimension:

    * Segment tree - O(n logn) preprocessing time, O(k+logn) query time, O(n logn) space
    * Interval tree - O(n logn) preprocessing time, O(k+logn) query time, O(n) space
    * Range tree - O(n logn) preprocessing time, O(k+logn) query time, O(n) space
    * Binary Indexed tree - O(n logn) preprocessing time, O(logn) query time, O(n) space

(k is the number of reported results).

All data structures can be dynamic, in the sense that the usage scenario includes both data changes and queries:

    * Segment tree - interval can be added/deleted in O(logn) time (see here)
    * Interval tree - interval can be added/deleted in O(logn) time
    * Range tree - new points can be added/deleted in O(logn) time (see here)
    * Binary Indexed tree - the items-count per index can be increased in O(logn) time

Higher dimensions (d>1):

    * Segment tree - O(n(logn)^d) preprocessing time, O(k+(logn)^d) query time, O(n(logn)^(d-1)) space
    * Interval tree - O(n logn) preprocessing time, O(k+(logn)^d) query time, O(n logn) space
    * Range tree - O(n(logn)^d) preprocessing time, O(k+(logn)^d) query time, O(n(logn)^(d-1))) space
    * Binary Indexed tree - O(n(logn)^d) preprocessing time, O((logn)^d) query time, O(n(logn)^d) space

