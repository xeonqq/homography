cc_library(
    name = "cairo",
    srcs = glob(["lib/x86_64-linux-gnu/libcairo.so"]),
    hdrs = glob([
        "include/cairo/**/*.h",
    ]),
    includes = [
        "include/cairo",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
