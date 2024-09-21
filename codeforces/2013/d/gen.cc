#include <iostream>
int main() {
  const int mx = 100000;
  for (int i = 1; i <= mx; i++) {
    std::cout << mx << ' ';
  }
  for (int i = 1; i <= mx; i++) {
    std::cout << i << ' ';
  }
}
