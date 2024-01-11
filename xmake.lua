add_rules("mode.debug", "mode.release")

option("build_examples")
option_end()

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

target("vec_example")
    set_enabled(has_config("build_examples") == true)
    set_languages("c89")
    add_deps("extc-static")
    add_includedirs("include")
    add_files("examples/example_vec.c")

target("stack_example")
    set_enabled(has_config("build_examples") == true)
    set_languages("c89")
    add_deps("extc-static")
    add_includedirs("include")
    add_files("examples/example_stack.c")
end