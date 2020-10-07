<h1 align="center">Design and Analysis of Algorithm</h1>

<h4 align="center">
  Implementation of classic problems for a course on Analysis and Design of Algorithms.
</h4>

<p align="center">
  <a href="https://github.com/marismarcosta/algorithm-design-and-analysis/blob/master/LICENSE" target="_blank">
    <img alt="license: MIT" src="https://img.shields.io/badge/license-MIT-yellow.svg?style=flat-square" />
  </a>
  <img alt="last commit" src="https://img.shields.io/github/last-commit/marismarcosta/algorithm-design-and-analysis?color=0f0&style=flat-square"/>
  <img alt="repo size" src="https://img.shields.io/github/repo-size/marismarcosta/algorithm-design-and-analysis?color=ffa07a&style=flat-square" />
  <a href="https://github.com/marismarcosta" target="_blank">
    <img src="https://img.shields.io/badge/marismarcosta-8B008B?logo=GitHub&style=flat-square"/>
  </a>
  <a href="https://www.linkedin.com/in/marismarcosta/" target="_blank">
    <img src="https://img.shields.io/badge/marismarcosta-blue?logo=linkedin&style=flat-square"/>
  </a>
</p>

## Insertion sort

Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands. The array is virtually split into a sorted and an unsorted part. Values from the unsorted part are picked and placed at the correct position in the sorted part.

#### To sort an array of size n in ascending order:
  1. Iterate from arr[1] to arr[n] over the array.
  2. Compare the current element (key) to its predecessor.
  3. If the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.

## Selection sort

The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning. The algorithm maintains two subarrays in a given array.

1. The subarray which is already sorted.
2. Remaining subarray which is unsorted.

In every iteration of selection sort, the minimum element (considering ascending order) from the unsorted subarray is picked and moved to the sorted subarray.

## Merge sort

Merge Sort is a divide and conquer algorithm. It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves. The merge() function is used for merging two halves. The merge(arr, l, m, r) is key process that assumes that arr[l..m] and arr[m+1..r] are sorted and merges the two sorted sub-arrays into one.

    mergesort(arr[], l,  r)
      if r > l:
        1. Find the middle point to divide the array into two halves:  
                middle m = (l+r)/2
        2. Call mergeSort for first half:   
                Call mergeSort(arr, l, m)
        3. Call mergeSort for second half:
                Call mergeSort(arr, m+1, r)
        4. Merge the two halves sorted in step 2 and 3:
                Call merge(arr, l, m, r)

## Counting sort

Counting sort is a sorting technique based on keys between a specific range. It works by counting the number of objects having distinct key values (kind of hashing). Then doing some arithmetic to calculate the position of each object in the output sequence.

## Knapsack problem

Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items respectively. Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item or don’t pick it (0-1 property).

## Prim's algorithm

Prim’s algorithm is a greedy algorithm. It starts with an empty spanning tree. The idea is to maintain two sets of vertices. The first set contains the vertices already included in the MST, the other set contains the vertices not yet included. At every step, it considers all the edges that connect the two sets, and picks the minimum weight edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing MST. 
A group of edges that connects two set of vertices in a graph is called cut in graph theory. So, at every step of Prim’s algorithm, we find a cut (of two sets, one contains the vertices already included in MST and other contains rest of the vertices), pick the minimum weight edge from the cut and include this vertex to MST Set (the set that contains already included vertices).
The idea behind Prim’s algorithm is simple, a spanning tree means all vertices must be connected. So the two disjoint subsets (discussed above) of vertices must be connected to make a Spanning Tree. And they must be connected with the minimum weight edge to make it a Minimum Spanning Tree.
#### Algorithm 
1) Create a set mstSet that keeps track of vertices already included in MST. 
2) Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. Assign key value as 0 for the first vertex so that it is picked first. 
3) While mstSet doesn’t include all vertices: 
    - Pick a vertex u which is not there in mstSet and has minimum key value. 
    - Include u to mstSet. 
    - Update key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. For every adjacent vertex v, if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v.

The idea of using key values is to pick the minimum weight edge from cut. The key values are used only for vertices which are not yet included in MST, the key value for these vertices indicate the minimum weight edges connecting them to the set of vertices included in MST. 


## Dijkstra's algorithm

Dijkstra’s algorithm is very similar to Prim’s algorithm for minimum spanning tree. Like Prim’s MST, we generate a SPT (shortest path tree) with given source as root. We maintain two sets, one set contains vertices included in shortest path tree, other set includes vertices not yet included in shortest path tree. At every step of the algorithm, we find a vertex which is in the other set (set of not yet included) and has a minimum distance from the source.
