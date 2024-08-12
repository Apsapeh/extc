add_rules("mode.debug", "mode.release")

option("build_examples")
option_end()

function example_template(files) 
    set_enabled(has_config("build_examples") == true)
    set_languages("c89")
    add_deps("extc-static")
    add_includedirs("include")
    add_files(files)
end

target("extc")
    set_kind("shared")
    set_languages("c89")
    set_warnings("pedantic")
    add_includedirs("include")
    add_files("src/*.c")

target("extc-static")
    set_kind("static")
    set_languages("c89")
    set_warnings("pedantic")
    add_includedirs("include")
    add_files("src/*.c")




target("vec_example")
    example_template("examples/example_vec.c")

target("stack_example")
    example_template("examples/example_stack.c")

target("string_example")
    example_template("examples/example_string.c")