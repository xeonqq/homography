cc_library(
    name = "gtk3",
    srcs = glob(["lib/x86_64-linux-gnu/libgtk-3.so"]),
    hdrs = glob(["include/gtk-3.0/**/*.h"]),
    strip_include_prefix = "include/gtk-3.0",
    visibility = ["//visibility:public"],
    #    linkstatic = 1,
    linkstatic = 1,
    deps = [
        "@glib//:glib",
        "@pango//:pango",
        "@cairo//:cairo",
        "@gdk_pixbuf//:gdk-pixbuf",
        "@atk//:atk",
    ],
)
