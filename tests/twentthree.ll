define i32 @main(i32 %0, i8** %1) {
    %res = call i32 @SOURCE ()
    %loop_count = icmp slt i32 %res, 10
    br i1 %loop_count, label %loop_header, label %no_leak_block

loop_header:
    %leak_value = phi i32 [ 0, %entry ], [ %leak_result, %loop_body ]
    call i32 @SINK (i32 %loop_count)
    %new_value = add i32 %leak_value, 1
    %loop_condition = icmp slt i32 %new_value, 10
    br i1 %loop_condition, label %loop_body, label %no_leak_block

loop_body:
    %leak_result = add i32 %res, 2
    br label %loop_header

no_leak_block:
    ret i32 0
}
declare dso_local i32 @SOURCE()
declare dso_local i32 @SINK(i32)
