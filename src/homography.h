//
// Created by qq on 02.03.19.
//

#ifndef HOMOGRAPHY_HOMOGRAPKY_H
#define HOMOGRAPHY_HOMOGRAPKY_H

#include <algorithm>
#include <opencv2/opencv.hpp>
#include <vector>
namespace qq {

template <typename T>
cv::Mat ConstructSystemMatrix(const std::vector<T> &srcPoints,
                              const std::vector<T> &dstPoints);
template <typename T>
cv::Mat FindHomography(const std::vector<T> &srcPoints,
                       const std::vector<T> &dstPoints) {
  /*
   * find the H such that
   * dstPoints = H * srcPoints
   */
  cv::Mat A = ConstructSystemMatrix(srcPoints, dstPoints);

  // std::cout << A.size() << std::endl;
  //  std::cout << srcPoints.size() << std::endl;
  cv::Mat H;

  int ret = cv::solve(A(cv::Range::all(), cv::Range(0, 8)), -A.col(8), H,
                      cv::DECOMP_NORMAL);
  //  std::cout << "solve: " << ret << '\n';
  cv::Mat one = (cv::Mat_<double>(1, 1) << 1);
  H.push_back(std::move(one));
  std::cout << H << std::endl;
  return H.reshape(0, 3);
}

template <typename T>
cv::Mat ConstructSystemMatrix(const std::vector<T> &srcPoints,
                              const std::vector<T> &dstPoints) {
  cv::Mat A;
  for (size_t i = 0; i < srcPoints.size(); ++i) {
    auto src_point =
        cv::Point3_<typename T::value_type>(srcPoints[i].x, srcPoints[i].y, 1);
    auto dst_point =
        cv::Point3_<typename T::value_type>(dstPoints[i].x, dstPoints[i].y, 1);

    auto coeff1 = -dst_point.z * src_point;
    auto coeff2 = dst_point.y * src_point;
    cv::Mat coeff_row0 = (cv::Mat_<double>(1, 9) << 0, 0, 0, coeff1.x, coeff1.y,
                          coeff1.z, coeff2.x, coeff2.y, coeff2.z);
    auto coeff3 = dst_point.z * src_point;
    auto coeff4 = -dst_point.x * src_point;
    cv::Mat coeff_row1 = (cv::Mat_<double>(1, 9) << coeff3.x, coeff3.y,
                          coeff3.z, 0, 0, 0, coeff4.x, coeff4.y, coeff4.z);
    A.push_back(coeff_row0);
    A.push_back(coeff_row1);
  }
  return A;
}
}
#endif // HOMOGRAPHY_HOMOGRAPKY_H
