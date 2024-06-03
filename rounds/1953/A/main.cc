#include "utils.h"

IO(__FILE__);

template <typename T>
string algo(const vector<T> &v, char type)
{
  stringstream result;
  result << "{" << type << ":";
  for (const auto &e : v)
    result << e << ',';
  auto r = result.str();
  r.back() = '}';
  return r;
}

template <typename T>
void redu(vector<string> &res, vector<T> &v16, vector<T> &v32, vector<T> &v64)
{
  if (v16.size() == 1)
    v32.push_back(v16.back());
  else if (v16.size())
    res.push_back(algo(v16, 'h'));

  if (v32.size() == 1)
    v64.push_back(v32.back());
  else if (v32.size())
    res.push_back(algo(v32, 's'));

  if (v64.size() == 1)
    res.push_back(to_string(v64.back()));
  else if (v64.size())
    res.push_back(algo(v64, 'd'));

  v16.clear();
  v32.clear();
  v64.clear();
}

const auto l16 = ldexp(1, -15), u16 = ldexp(1, 0), uu16 = ldexp(1, 10);
const auto l32 = ldexp(1, -126), u32 = ldexp(1, 14), uu32 = ldexp(1, 100);
const auto m16 = (1L << (52 - 10)) - 1, m32 = (1L << (52 - 23)) - 1;

inline bool is16(double x)
{
  return (x > l16 && x <= u16) || (x <= uu16 && *reinterpret_cast<i64 *>(&x) & m16 == 0);
}

inline bool is32(double x)
{
  return (x > l32 && x <= u32) || (x <= uu32 && *reinterpret_cast<i64 *>(&x) & m32 == 0);
}

int main()
{
  int n;
  in >> n;
  vector<int> fp16, fp32, fp64;
  vector<string> bl16, bl32, bl64;
  double s = 0;
  for (int i = 1; i <= n; ++i)
  {
    double x;
    in >> x;
    s += x;
    const auto a = fabs(x);
    auto &list = is16(a) ? fp16 : (is32(a) ? fp32 : fp64);
    list.push_back(i);
    if (i % 16 == 0 || i == n)
    {
      const auto b = fabs(s);
      s = 0;
      auto &list = is16(b) ? bl16 : (is32(b) ? bl32 : bl64);
      redu(list, fp16, fp32, fp64);
    }
  }
  vector<string> res;
  redu(res, bl16, bl32, bl64);
  cout << (res.size() == 1 ? res.back() : algo(res, 'd')) << endl;
}