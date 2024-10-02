/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T, auto M>
  requires unsigned_integral<T>
struct Mod {
  using U = conditional<is_same<T, u64>::value, u128, u64>::type;
  static T inv(T x, U m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  static T norm(T x) { return rotl(x, 1) & 1 ? x + M : x < M ? x : x - M; }
  T x;
  Mod() : x(0) {}
  Mod(i64 y) : x(norm(y % i64(M))) {}
  operator T() const { return x; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return x = norm(x + rhs.x), *this; }
  Mod &operator-=(Mod rhs) { return x = norm(x - rhs.x), *this; }
  Mod &operator*=(Mod rhs) { return x = U(x) * rhs.x % M, *this; }
  Mod &operator/=(Mod rhs) { return *this *= inv(rhs.x, M); }
  Mod pow(i64 y) const { // O(log y) / 0^(-inf,0] -> 1
    Mod ans(1), base(y < 0 ? inv(x, M) : x);
    for (y = abs(y); y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<u32, 1000000007u>;

struct Primes {
  static constexpr int N = 1 << 16;
  array<u64, 6542> magic = {}; // ~51KB
  constexpr Primes() {         // O(N*log log N) = O(2^18)
    array<bool, N> vis = {};
    for (int i = 2, cnt = 0; i < N; i++) {
      if (!vis[i]) {
        magic[cnt++] = u64(-1) / i + 1;
        for (int j = 2 * i; j < N; j += i)
          vis[j] = true;
      }
    }
  }
  vector<u32> factors(u32 n) const { // O(sqrt n/log n)
    vector<u32> ans = {1};
    auto mx = u64(-1) / u64(sqrt(n)) + 1;
    for (auto m : magic) {
      if (m * n < m) {
        ans.push_back(u64(-1) / m + 1);
      } else if (m < mx) {
        break;
      }
    }
    return ans;
  }
};

constexpr Primes primes;

int countdiv(int x, int y) {
  assert(y > 1);
  int c = 0;
  for (div_t d = {}; !d.rem && x > 1; c += !d.rem) {
    d = div(x, y);
    x = d.quot;
  }
  return c;
}

struct Str : string {
  using string::string;
  Str() { cin >> *this; }
};

void solve(int t) {
  Int n, k, d;
  vector<Mint> pref(bit_width<unsigned>(n), 1);
  for (int j = 0; j < d; j++) { // O(d*log n)
    for (int i = 1; i < pref.size(); i++) {
      pref[i] += pref[i - 1];
    }
  }
  Mint ans;
  for (int i = 1; i <= n; i++) { // O(n*log k + n*sqrt n/log n)
    Mint prod = 1;
    auto factors = primes.factors(i);
    for (auto &&factor : factors) { // O(log i)
      if (factor != 1) {
        auto c = countdiv(i, factor);
        assert(c > 0);
        prod *= pref[c];
      }
    }
    ans += prod.pow(k);
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
