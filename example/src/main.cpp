#define XXP_EIGEN_SUPPORT

#include <xxp>
#include <iostream>
#include <unistd.h>

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

  XDEC_PARAM_PATH(int, test, data.config.test);

  std::cout << "test=" << test << std::endl;

  XDO_BEGIN;

  while(true)
  {
    std::cout << "Wating for block to be released" << std::endl;
    xxp::block("data_sink");
    if(xxp::eof("data_sink"))
    {
      xxp::unblock("data_sink");
      break;
    }
    std::cout << "Getting stuff" << std::endl;
    std::vector<int> l = xxp::request<int>("data_sink", 2);
    srand(l[0]);
    for(int i : l)
      std::cout << i << " ";
    sleep(rand()%2);  
    std::vector<int> k = xxp::request<int>("data_sink", 2);
    for(int i : k)
      std::cout << i << " ";
    std::cout << std::endl;
    xxp::unblock("data_sink");
    sleep(rand()%5);  
  }
  std::cout << "Going to end now" << std::endl;
  XEND;
  
  xxp::finalize(0);
/*
  xxp::data_handle alt_logs = xxp::request_file("alternative");
  xxp::data(alt_logs) << "Hallo";
  xxp::data(alt_logs) << 1.2344;
  xxp::store_data(alt_logs);

  std::vector<std::vector<int>> x{{1,2},{3,4}};

  Eigen::VectorXd v(4);
  v.setRandom();

  Eigen::RowVectorXd w(4);
  w.setRandom();

  Eigen::MatrixXd z(4,4);
  z.setRandom();

  xxp::data(alt_logs) << xxp::format(v);
  xxp::store_data(alt_logs);
  xxp::data(alt_logs) << xxp::format(w);
  xxp::store_data(alt_logs);
  xxp::data(alt_logs) << xxp::format(z);
  xxp::store_data(alt_logs);
  xxp::data(alt_logs) << 1.123;
  xxp::store_data(alt_logs);

  XDO_BEGIN;

  xxp::measure_time();

  XDEC_PARAM(Eigen::VectorXd,vec);
  XDEC_PARAM(Eigen::MatrixXd,mat);
  xxp::data() << xxp::format(vec);
  xxp::store_data();
  xxp::data() << xxp::format(mat, xxp::matrix);
  xxp::store_data();

  XDEC_PARAM(double, alpha);
  XDEC_PARAM(double, beta);

  if(alpha > 0.5 && beta > 0.5)
    sleep(1);

  test t;
  XPARAM(t);

  //sleep(1);

  xxp::data() << alpha;
  xxp::data() << beta;
  xxp::data() << "Hallo";
  xxp::store_data();

  xxp::measure_time();
  for(int i=0;i<1000;i++)
    alpha *= 1.3;
  xxp::measure_time();
  xxp::store_timing();

  XEND;
*/

}
