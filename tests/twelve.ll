define i32 @main() {
    %i_outer = alloca i32
    store i32 0, i32* %i_outer

    br label %outer_loop_header

outer_loop_header:
    %current_value_outer = load i32, i32* %i_outer

    %condition_outer = icmp slt i32 %current_value_outer, 3
    br i1 %condition_outer, label %outer_loop_body, label %outer_loop_end

outer_loop_body:
    %i_inner = alloca i32
    store i32 0, i32* %i_inner

    br label %inner_loop_header

inner_loop_header:
    %current_value_inner = load i32, i32* %i_inner

    %condition_inner = icmp slt i32 %current_value_inner, 2
    br i1 %condition_inner, label %inner_loop_body, label %inner_loop_end

inner_loop_body:
    %current_value_outer_print = load i32, i32* %i_outer
    %current_value_inner_print = load i32, i32* %i_inner
    call void @print(i32 %current_value_outer_print, i32 %current_value_inner_print)

    %new_value_inner = add i32 %current_value_inner, 1
    store i32 %new_value_inner, i32* %i_inner

    br label %inner_loop_header

inner_loop_end:
    %new_value_outer = add i32 %current_value_outer, 1
    store i32 %new_value_outer, i32* %i_outer

    br label %outer_loop_header

outer_loop_end:
    ret i32 0
}

declare void @print(i32, i32) {
}
