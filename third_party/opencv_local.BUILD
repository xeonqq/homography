cc_library(
    name = "opencv_local",
    srcs = glob(["lib/x86_64-linux-gnu/libopencv*.so*"]),
    hdrs = glob([
        "include/opencv/**",
        "include/opencv2/**",
    ]),
    includes = ["include"],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)
