define i32 @addTwoNumbers() {
}

define i32 @main() {
    %sum = call i32 @addTwoNumbers()
    %sum1 = call i32 @addTwoNumbers()
    %sum2 = call i32 @addTwoNumbers()

    ret i32 %sum
}
