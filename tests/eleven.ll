define i32 @main() {
    %i = alloca i32
    store i32 0, i32* %i

    br label %loop_header

loop_header:
    %current_value = load i32, i32* %i

    %condition = icmp slt i32 %current_value, 5
    br i1 %condition, label %loop_body, label %loop_end

loop_body:
    %current_value_print = load i32, i32* %i
    call void @print(i32 %current_value_print)

    %new_value = add i32 %current_value, 1
    store i32 %new_value, i32* %i

    br label %loop_header

loop_end:
    ret i32 0
}