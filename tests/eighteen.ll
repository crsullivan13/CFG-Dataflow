define i32 @main(i32 %argc) {
        %res = call i32 @SOURCE ()
        %valptr = alloca i32, align 4
        store i32 %res, i32* %valptr, align 4
        %noArgs = icmp eq i32 %argc, 1
        br i1 %noArgs, label %lbl_t, label %lbl_f
lbl_t:
        %varT = add i32 1, 0
        br label %end
lbl_f:
        %ouch = load i32, i32* %valptr, align 4
        call i32 @SINK (i32 %ouch)
        %varF = add i32 2, 0
        br label %end
end:
        %var = phi i32 [%varT, %lbl_t], [%varF, %lbl_f]
        ret i32 %var
}

declare dso_local i32 @SOURCE()
declare dso_local i32 @SINK(i32)