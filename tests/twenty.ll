define i32 @main(i32 %0, i8** %1) {
    %res = call i32 @SOURCE ()
    %condition = icmp ne i32 %0, 0
    br i1 %condition, label %leak_block, label %no_leak_block

leak_block:
    call i32 @SINK (i32 %res)
    ret i32 0

no_leak_block:
    ret i32 0
}
declare dso_local i32 @SOURCE()
declare dso_local i32 @SINK(i32)
