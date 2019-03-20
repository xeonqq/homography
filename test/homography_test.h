//
// Created by qq on 02.03.19.
//
#ifndef HOMOGRAPHY_HOMOGRAPHY_TEST_H
#define HOMOGRAPHY_HOMOGRAPHY_TEST_H

#include <include/gtest/gtest.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class HomographyFixture : public testing::Test {
public:
  HomographyFixture() {
    _feature_points = {Point2d(415, 169),
                       Point2d(413, 172),
                       Point2d(413, 177),
                       Point2d(440, 232),
                       Point2d(415, 238),
                       Point2d(418, 167),
                       Point2d(406.80002, 254.40001),
                       Point2d(424.80002, 174.24001),
                       Point2d(427.68002, 178.56001),
                       Point2d(414.72003, 169.34401),
                       Point2d(404.35205, 254.01602),
                       Point2d(404.35205, 252.97923),
                       Point2d(420.52618, 174.18243)};
    _corespondent_points = {Point2d(134, 168),
                            Point2d(133, 170),
                            Point2d(133, 175),
                            Point2d(157, 226),
                            Point2d(134, 234),
                            Point2d(134, 168),
                            Point2d(125.28001, 250.56001),
                            Point2d(142.56001, 172.8),
                            Point2d(145.44, 177.12001),
                            Point2d(134.78401, 167.61601),
                            Point2d(124.41602, 250.56003),
                            Point2d(124.41602, 250.90564),
                            Point2d(138.24002, 171.07202)};
  }

  std::vector<Point2f> _feature_points;
  std::vector<Point2f> _corespondent_points;
};
#endif // HOMOGRAPHY_HOMOGRAPHY_TEST_H
