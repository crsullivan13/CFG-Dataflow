define i32 @addTwoNumbers(i32 %a, i32 %b) {
    %result = add i32 %a, %b
    ret i32 %result
}

define i32 @main() {
    %sum = call i32 @addTwoNumbers(i32 5, i32 7)

    ret i32 %sum
}