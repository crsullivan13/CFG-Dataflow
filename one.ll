define i32 @main(i32 %argc) {
        %var = add i32 2, 0
        %var2 = mul i32 2, 0
        %var3 = sdiv i32 1, 2
        %var4 = udiv i32 2, 0
        %var5 = fdiv i32 2, 0
        %var6 = sub i32 2, 0
        ret i32 %var
}