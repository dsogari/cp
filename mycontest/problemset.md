# My Contest

## A. Absecutive

- Category: Math Teaser
- Expected difficulty: 500
- Expected time complexity: $O(1)$

### Setting

Su is preparing a lesson on integer numbers for her students. She will give each student a **consecutive** number starting from $l$ and ending at $r$. Then, she will ask students to form **pairs** according to the following rule:

- two students can form a pair only if the **magnitudes** of their numbers differ by **one**.

In anticipation of the class, she wants to know how many (possibly **non-disjoint**) pairs could be formed.

### Summary

Given an interval $[l, r]$, determine the number of pairs of integers within it, such that their magnitudes differ by one.

### Input

The first line of input contains one integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The only line of each test case contains two integers $l$ and $r$ ($-10^9 \le l \le r \le 10^9$) - the lower and upper bounds of the interval, respectively.

### Output

For each test case, output one integer - the number of pairs of integers within the interval, such that their magnitudes differ by one.

### Note

In the first test case, there can be no pairs.

In the second test case, only one pair can be formed, namely, $(0,1)$. Note that the pair $(1,0)$ is equivalent.

In the third test case, two pairs can be formed: $(-1,0)$ and $(0,1)$.

### Solution

First, notice that the result will have at least $r - l$ good pairs. Then, if $l < 0$ and $r > 0$, there will be additional pairs: one for each negative value whose magnitude is one less than a positive value; and another for each positive value that is one less than the magnitude of a negative value.

### Code

```cpp
int ans = r - l;
if (l < 0 && r > 0) {
  ans += min(-l, r - 1) + min(-l - 1, r);
}
```

Complexity: $O(1)$

## C1. Bookcase (Easy)

Su has a collection of books of different sizes, each with an integer width and height $(w,h)$, and wants to build a bookcase to accomodate all of them. However, Su is very capricious: she wants books on a shelf to be ordered by size (i.e., either non-decreasing or non-increasing), such that no book is at the same time wider and shorter than its neighbour (or vice-versa). Su also wants to save on materials, so she wants to know the minimum number of shelves, $k_{min}$, that the bookcase can have.

### Solution

If we sort all books by width then height, we can safely ignore the width and see that the heights form a sawtooth pattern. When we take a book from this series, we can add it to the shelf whose top book has the closest height that is less than or equal to the current one. Once the height becomes less than the smaller height among all shelves so far, we need to create another shelf. This is known as the longest decreasing subsequence (reciprocal of LIS).

Complexity: $O(n \log n)$

### Code

```cpp
ranges::sort(a);
greater<int> gt;
vector<int> heights = {INT_MAX};
for (auto [w, h] : a) {
  if (heights.back() > h) {
    heights.push_back(h);
  } else {
    *ranges::lower_bound(heights, h, gt) = h;
  }
}
cout << heights.size() - 1 << endl;
```

## C2. Bookcase (Hard)

Su is eager to build her bookcase, but she wants to save even more on materials. Since she has so many books of different sizes, she is taking the average book thickness and considering all books to have this same thickness. For simplicity, assume that it is $1$. For the minimum number of shelves that the bookcase can have, $k_{min}$, Su wants to minimize the maximum number of books that a shelf can have, so that the bookcase will have the minimum possible lenght, $l_{min}$.

### Solution

### Code
