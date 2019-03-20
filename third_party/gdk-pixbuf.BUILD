cc_library(
    name = "gdk-pixbuf",
    srcs = glob(["lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so"]),
    hdrs = glob([
        "include/gdk-pixbuf-2.0/**/*.h",
    ]),
    includes = [
        "include/gdk-pixbuf-2.0",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
