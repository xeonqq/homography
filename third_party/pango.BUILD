cc_library(
    name = "pango",
    srcs = glob(["lib/x86_64-linux-gnu/libpango-1.0.so"]),
    hdrs = glob([
        "include/pango-1.0/**/*.h",
    ]),
    includes = [
        "include/pango-1.0",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
    #    linkstatic = 1,
)
