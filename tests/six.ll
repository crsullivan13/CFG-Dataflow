define i32 @main(i32 %argc) {
    %val = add i32 %argc, 5
    %val1 = mul i32 0, 5
    %val2 = sub i32 %argc, %argc
    %val3 = sdiv i32 5, %argc
    %val4 = udiv i32 5, %argc
    ret i32 %val
}