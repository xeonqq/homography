#include "homography.h"

#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/nonfree/nonfree.hpp>

using namespace cv;

int main(int argc, char **argv) {
  Mat img_scene1_in = imread("pics/DJI_0002.JPG", CV_LOAD_IMAGE_GRAYSCALE);
  Mat img_scene2_in = imread("pics/DJI_0003.JPG", CV_LOAD_IMAGE_GRAYSCALE);
  Mat img_scene1;
  Mat img_scene2;
  int width = 512;

  int height = 368;
  cv::resize(img_scene1_in, img_scene1, cv::Size(width, height));
  cv::resize(img_scene2_in, img_scene2, cv::Size(width, height));
  if (!img_scene1.data || !img_scene2.data) {
    std::cout << " --(!) Error reading images " << std::endl;
    return -1;
  }

  Ptr<ORB> detector = ORB::create();
  //
  //  //-- Step 1: Detect the keypoints using SURF Detector
  //  int minHessian = 400;
  //
  //  SurfFeatureDetector detector( minHessian );
  std::vector<KeyPoint> keypoints_scene1, keypoints_scene2;

  detector->detect(img_scene1, keypoints_scene1);
  detector->detect(img_scene2, keypoints_scene2);
  //
  //  //-- Step 2: Calculate descriptors (feature vectors)
  Ptr<DescriptorExtractor> extractor = ORB::create();

  //  SurfDescriptorExtractor extractor;
  //
  Mat descriptors_scene1, descriptors_scene2;
  extractor->compute(img_scene1, keypoints_scene1, descriptors_scene1);
  extractor->compute(img_scene2, keypoints_scene2, descriptors_scene2);
  std::cout << keypoints_scene1.size() << " " << descriptors_scene1.size()
            << '\n';
  if (descriptors_scene1.empty())
    cvError(0, "MatchFinder", "1st descriptor empty", __FILE__, __LINE__);

  if (descriptors_scene2.empty())
    cvError(0, "MatchFinder", "2nd descriptor empty", __FILE__, __LINE__);
  if (descriptors_scene1.type() != CV_32F) {
    descriptors_scene1.convertTo(descriptors_scene1, CV_32F);
  }

  if (descriptors_scene2.type() != CV_32F) {
    descriptors_scene2.convertTo(descriptors_scene2, CV_32F);
  }
  ////
  ////  //-- Step 3: Matching descriptor vectors using FLANN matcher
  FlannBasedMatcher matcher;
  std::vector<DMatch> matches;
  matcher.match(descriptors_scene1, descriptors_scene2, matches);
  //
  double max_dist = 0;
  double min_dist = 100;

  //-- Quick calculation of max and min distances between keypoints
  for (int i = 0; i < descriptors_scene1.rows; i++) {
    double dist = matches[i].distance;
    if (dist < min_dist)
      min_dist = dist;
    if (dist > max_dist)
      max_dist = dist;
  }

  printf("-- Max dist : %f \n", max_dist);
  printf("-- Min dist : %f \n", min_dist);

  //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
  std::vector<DMatch> good_matches;

  for (int i = 0; i < descriptors_scene1.rows; i++) {
    if (matches[i].distance < 2 * min_dist) {
      good_matches.push_back(matches[i]);
    }
  }

  Mat img_keypoints;
  drawKeypoints(img_scene1, keypoints_scene1, img_keypoints);
  Mat img_matches;
  drawMatches(img_scene1, keypoints_scene1, img_scene2, keypoints_scene2,
              good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
              std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

  //-- Localize the object
  std::vector<Point2f> obj;
  std::vector<Point2f> scene;

  for (int i = 0; i < good_matches.size(); i++) {
    //-- Get the keypoints from the good matches
    obj.push_back(keypoints_scene1[good_matches[i].queryIdx].pt);
    scene.push_back(keypoints_scene2[good_matches[i].trainIdx].pt);
  }
  std::cout << obj.size() << "\n";
  std::cout << "obj_keypoints: " << obj << "\n";
  std::cout << "scene_keypoints: " << scene << "\n";
  Mat H_cv = findHomography(obj, scene, 0);
  //  Mat H = findHomography(obj, scene, CV_RANSAC);
  Mat H = qq::FindHomography(obj, scene);
  std::cout << "homography cv mat:" << H_cv << "\n";
  std::cout << "homography qq mat:" << H << "\n";

  std::vector<KeyPoint> transformed_points;
  std::transform(obj.begin(), obj.end(), std::back_inserter(transformed_points),
                 [&H, &H_cv](const Point2f &point) {
                   cv::Mat_<double> src(3 /*rows*/, 1 /* cols */);
                   src(0, 0) = point.x;
                   src(1, 0) = point.y;
                   src(2, 0) = 1.0;
                   cv::Mat_<double> transformed = H * src;

                   return cv::KeyPoint(
                       cv::Point2f(transformed(0, 0), transformed(1, 0)) /
                           transformed(2, 0),
                       2);
                 });
  Mat img_trans_keypoints;

  drawKeypoints(img_scene2, transformed_points, img_trans_keypoints);
  imshow("Keypoints", img_trans_keypoints);

  //  //-- Get the corners from the image_1 ( the object to be "detected" )
  //  std::vector<Point2f> obj_corners(4);
  //  obj_corners[0] = cvPoint(0, 0);
  //  obj_corners[1] = cvPoint(img_scene1.cols, 0);
  //  obj_corners[2] = cvPoint(img_scene1.cols, img_scene1.rows);
  //  obj_corners[3] = cvPoint(0, img_scene1.rows);
  //  std::vector<Point2f> scene_corners(4);

  //  if (!H.empty()) {
  //    perspectiveTransform(obj_corners, scene_corners, H);
  //    //    -- Draw lines between the corners (the mapped object in the scene
  //    -
  //    //    image_2 )
  //    line(img_matches, scene_corners[0] + Point2f(img_scene1.cols, 0),
  //         scene_corners[1] + Point2f(img_scene1.cols, 0), Scalar(0, 255, 0),
  //         4);
  //    line(img_matches, scene_corners[1] + Point2f(img_scene1.cols, 0),
  //         scene_corners[2] + Point2f(img_scene1.cols, 0), Scalar(0, 255, 0),
  //         4);
  //    line(img_matches, scene_corners[2] + Point2f(img_scene1.cols, 0),
  //         scene_corners[3] + Point2f(img_scene1.cols, 0), Scalar(0, 255, 0),
  //         4);
  //    line(img_matches, scene_corners[3] + Point2f(img_scene1.cols, 0),
  //         scene_corners[0] + Point2f(img_scene1.cols, 0), Scalar(0, 255, 0),
  //         4);
  //  }

  //-- Show detected matches
  imshow("Good Matches & Object detection", img_matches);
  //  imshow("Keypoints", img_keypoints);

  waitKey(0);
  return 0;
}
