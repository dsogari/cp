## E. Tarzan

- Category: Trees, Graphs
- Expected difficulty: 2500
- Expected time complexity: $O(n \log n)$

### Statement

Tarzan is swinging trhough trees in a forest, when suddenly he hears a cry from his friend Ape in a distant tree. He wants to reach that tree as quickly as possible, whilst avoiding the ground. Trusting in his skills, Tarzan is able to perform the following move:

- swing from a tree to any other tree within a distance equal to the height of the **current** tree.

Help him determine a sequence of moves which minimizes the (Euclidean plane) distance required to travel from his starting tree to Ape's.

### Input

The first line of the input contains a single integer, $t$ ($1 \le t \le 10^4$) — the number of test cases.

The first line of each test case contains a single integer, $n$ ($2 \le n \le 2 \cdot 10^5$) — the number of trees in the forest.

Then follow $n$ lines of each test case, each with three integers, $x_i$, $y_i$ and $h_i$ ($-10^9 \le x_i,y_i \le 10^9$, $1 \le h_i \le 10^9$) — the coordinates of the $i$-th tree, and its height. The first line denotes Tarzan's starting tree, while the last one denotes Ape's.

### Output

For each test case, first output a single integer, $m$ — the number moves made by Tarzan on his way to Ape; or $0$ if it's impossible.

Then, on the next line, output $m$ integers — the indices of the trees visited by Tarzan on his way to Ape's (inclusive). If there are many possible sequences, output any of them.

### Note

### Solution

### Code

## F1. Bookcase (Easy)

- Category: Sorting & Searching
- Expected difficulty: 1500
- Expected time complexity: $O(n \log n)$

### Statement

Li has a collection of books of various sizes (width and height), and wants to build a bookcase to store them. However, Li is very capricious: she wants books on any shelf to be ordered by size. I.e.:

- there **cannot** be two adjacent books such that one is larger in width **and** smaller in height than the other (or _vice versa_).

In order to save on materials, she wants to know the smallest number of shelves the bookcase can have.

### Input

The first line of the input contains a single integer, $t$ ($1 \le t \le 10^4$) — the number of test cases.

The first line of each test case contains a single integer, $n$ ($1 \le n \le 2 \cdot 10^5$) — the number of books.

Then follow $n$ lines of each test case, each with two integers, $w_i$ and $h_i$ ($1 \le w_i,h_i \le 10^9$) — the width and height of the $i$-th book.

### Output

For each test case, output a single integer — the minimum number of shelves the bookcase can have, so as to accommodate all of the books and satisfy Li's whim.

### Note

### Solution

If we sort the books by width, then by height, we can safely ignore the width and see that the heights form a sawtooth pattern. When we take a book from this series, we can add it to the shelf whose top book has the closest height that is less than or equal to the current one. Once the height becomes less than the smallest height among all shelves so far, we need to create another shelf. This algorithm is also known as the longest (de/in)creasing subsequence (LIS).

### Code

```cpp
ranges::sort(a);
greater<int> gt;
vector<int> heights = {INT_MAX};
for (auto [w, h] : a) {
  if (h < heights.back()) {
    heights.push_back(h);
  } else {
    *ranges::lower_bound(heights, h, gt) = h;
  }
}
cout << heights.size() - 1 << endl;
```

## F2. Bookcase (Hard)

- Category: Combinatorial Optimization
- Expected difficulty: 3000
- Expected time complexity: $O(?)$

### Statement

Now that Li has determined the minimum number of shelves for her bookcase, she is eager to build it. However, she wants to save even more on materials, by minimizing the bookcase length. In order to do so, she needs to know the minimum length (in number of books) that the longest shelf can have.

### Input

The first line of the input contains a single integer, $t$ ($1 \le t \le 10^4$) — the number of test cases.

The first line of each test case contains two integers, $n$ and $k$ ($1 \le n \le ?$, $1 \le k \le ?$) — the number of books and the number of shelves.

Then follow $n$ lines of each test case, each with two integers, $w_i$ and $h_i$ ($1 \le w_i,h_i \le 10^9$) — the width and height of the $i$-th book.

### Output

For each test case, output a single integer — the minimum length that the longest shelf can have, so as to accommodate all of the books and satisfy Li's whim.

### Note

### Solution

### Code
