add_rules("mode.debug", "mode.release")

target("extc")
    set_kind("shared")
    set_languages("c89")
    add_includedirs("include")
    add_files("src/*.c")

target("extc-static")
    set_languages("c89")
    set_kind("static")
    add_includedirs("include")
    add_files("src/*.c")


if not has_config("not_build_examples") then

target("example1")
    set_languages("c89")
    add_deps("extc-static")
    add_includedirs("include")
    add_files("examples/example_vec.c")

end