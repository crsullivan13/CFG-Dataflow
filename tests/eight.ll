define i32 @main(i32 %argc) {
    %valptr = alloca i32, align 4
    store i32 12, i32* %valptr, align 4
    %res = load i32, i32* %valptr, align 4
    ret i32 %res
}