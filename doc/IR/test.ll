; ModuleID = 'test'
source_filename = "test"

define i32 @Fact(i32 %K) {
prepare_arg:
  %0 = alloca i32, align 4
  store i32 %K, ptr %0, align 4
  br label %entry

entry:                                            ; preds = %prepare_arg
  br label %if.cond

if.cond:                                          ; preds = %entry
  %1 = load i32, ptr %0, align 4
  %2 = icmp ne i32 %1, 0
  br i1 %2, label %if.body, label %if.merge

if.body:                                          ; preds = %if.cond
  %3 = load i32, ptr %0, align 4
  %4 = sub i32 %3, 1
  %5 = call i32 @Fact(i32 %4)
  %6 = load i32, ptr %0, align 4
  %7 = mul i32 %5, %6
  ret i32 %7

if.merge:                                         ; preds = %if.cond
  ret i32 1
}

define i32 @main() {
prepare_arg:
  br label %entry

entry:                                            ; preds = %prepare_arg
  %0 = alloca i32, align 4
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, ptr %0, align 4
  br label %if.cond

if.cond:                                          ; preds = %entry
  %4 = load i32, ptr %0, align 4
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %if.body, label %if.merge

if.body:                                          ; preds = %if.cond
  %6 = call i32 @Fact(i32 4)
  store i32 %6, ptr %1, align 4
  %7 = load i32, ptr %1, align 4
  ret i32 %7

if.merge:                                         ; preds = %if.cond
  store i32 5, ptr %2, align 4
  store i32 1, ptr %3, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %if.merge
  %8 = load i32, ptr %2, align 4
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %while.body, label %while.next

while.body:                                       ; preds = %while.cond
  %10 = load i32, ptr %3, align 4
  %11 = load i32, ptr %2, align 4
  %12 = mul i32 %10, %11
  store i32 %12, ptr %3, align 4
  %13 = load i32, ptr %2, align 4
  %14 = sub i32 %13, 1
  store i32 %14, ptr %2, align 4
  br label %while.cond

while.next:                                       ; preds = %while.cond
  %15 = load i32, ptr %3, align 4
  ret i32 %15
}
