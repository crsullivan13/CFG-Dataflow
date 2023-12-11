@global_var1 = global i32 42, align 4
@global_var2 = global double 3.14, align 4

define i32 @addTwoIntegers(i32 %a, i32 %b) {
    %result = add i32 %a, %b
    ret i32 %result
}

define double @multiplyTwoDoubles(double %x, double %y) {
    %result = mul double %x, %y
    ret double %result
}

define i32 @main() {
    %sum = call i32 @addTwoIntegers(i32 5, i32 7)

    %product = call double @multiplyTwoDoubles(double 2.5, double 3.0)

    %value1 = load i32, i32* @global_var1, align 4
    %value2 = load double, double* @global_var2, align 4

    call void @printResult(i32 %sum, double %product, i32 %value1, double %value2)

    ret i32 0
}

define void @printResult(i32, double, i32, double) {
}
