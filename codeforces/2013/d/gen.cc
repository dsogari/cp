#include <iostream>
int main() {
  const int mx = 100000;
  std::cout << "1\n" << 2 * mx << '\n';
  for (int i = 1; i <= mx; i++) {
    std::cout << mx << ' ';
  }
  for (int i = 1; i <= mx; i++) {
    std::cout << i << ' ';
  }
}
