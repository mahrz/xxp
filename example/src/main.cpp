#include <xxp>
#include <iostream>

struct test
{
  int a;
  int b;
};

namespace xxp
{
  template<>
  struct extract<test>
  {
    static test value(const picojson::value& v)
    {
      test t;
      t.a = extract<int>::value(v.get("a"));
      t.b = extract<int>::value(v.get("b"));
      return t;
    }
  };
}

int main(int argc, char **argv)
{
  xxp::init(argc, argv);

  xxp::data_handle alt_logs = xxp::request_file("alternative");
  xxp::data(alt_logs) << "Hallo";
  xxp::data(alt_logs) << 1.2344;
  xxp::store_data(alt_logs);

  xxp::data(alt_logs) << "Hallo Blabla" << xxp::tab << 1.234;
  xxp::data(alt_logs) << 1.123;
  xxp::store_data(alt_logs);

  XDO_BEGIN;

  XDEC_PARAM(double, alpha);
  XDEC_PARAM(double, beta);
  std::cout << "alpha: " << alpha << " beta: " << beta << std::endl;
  test t;
  XPARAM(t);
  std::cout << "t.a: " << t.a << " t.b: " << t.b << std::endl;

  xxp::data() << alpha;
  xxp::data() << beta;
  xxp::data() << "Hallo";
  xxp::store_data();

  XEND;

}
