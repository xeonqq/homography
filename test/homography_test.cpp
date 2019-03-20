//
// Created by qq on 02.03.19.
//

#include "homography_test.h"
#include "gtest/gtest.h"
#include <homography.h>

TEST_F(HomographyFixture, H_matrix) {

  Mat expected_H =
      (Mat_<double>(3, 3) << 0.2404191587670964, -0.1206453684638809,
       -15.90238487752242, -0.2165240589582301, 0.2460077572743628,
       127.5405765246745, -0.0009209712075046282, -0.0008631087540181928, 1);
  Mat calc_H = qq::FindHomography(_feature_points, _corespondent_points);
  std::cout << "calculated:" << calc_H << '\n';
  std::cout << "expected: " << expected_H << '\n';
  cv::Mat diff = calc_H != expected_H;
  //  Equal if no elements disagree
  EXPECT_EQ(cv::countNonZero(diff), 0);
}