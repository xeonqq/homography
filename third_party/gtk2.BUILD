cc_library(
    name = "gtk2",
    srcs = [
        "lib/x86_64-linux-gnu/libgtk-x11-2.0.so",
        #        "lib/x86_64-linux-gnu/libgtk-x11-2.0.a",
    ],
    hdrs = glob([
        "include/gtk-2.0/**/*.h",
        "lib/x86_64-linux-gnu/gtk-2.0/include/*.h",
    ]),
    includes = [
        "include/gtk-2.0",
        "lib/x86_64-linux-gnu/gtk-2.0/include",
    ],
    visibility = ["//visibility:public"],
    #    linkstatic = 1,
    deps = [
        "@glib//:glib",
        "@pango//:pango",
        "@cairo//:cairo",
        "@gdk_pixbuf//:gdk-pixbuf",
        "@atk//:atk",
    ],
)
