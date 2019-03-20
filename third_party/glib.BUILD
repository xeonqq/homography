cc_library(
    name = "glib",
    srcs = glob(["lib/x86_64-linux-gnu/libglib-2.0.so"]),
    hdrs = glob([
        "include/glib-2.0/**/*.h",
        "lib/x86_64-linux-gnu/glib-2.0/include/*.h",
    ]),
    includes = [
        "include/glib-2.0",
        "lib/x86_64-linux-gnu/glib-2.0/include/",
    ],
    visibility = ["//visibility:public"],
    #    linkstatic = 1,
)
