cc_binary(
    name = "homography_main",
    srcs = glob([
        "src/homography_main.cpp",
        "src/homography.h",
    ]),
    data = glob(["pics/**"]),
    includes = ["src"],
    deps = [
        "@opencv_3_4_3_linux_x86_64_precompiled//:core",
        #        "@jpeg//:libjpeg.so.62",
        #        "@opencv_local",
    ],
    #        "@opencv//:nonfree",
    #        "@opencv//:calib3d",
    #        "@opencv//:highgui",
)

cc_library(
    name = "find_homography",
    srcs = [
        "src/homography.cpp",
    ],
    hdrs = ["src/homography.h"],
    includes = ["src"],
    deps = [
        "@opencv_3_4_3_linux_x86_64_precompiled//:core",
    ],
)

cc_test(
    name = "hompgraphy_unittest",
    srcs = glob(["test/**"]),
    deps = [
        ":find_homography",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "@opencv_3_4_3_linux_x86_64_precompiled//:core",
    ],
)
