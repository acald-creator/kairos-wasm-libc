; ModuleID = 'hello.c'
source_filename = "hello.c"
target datalayout = "e-m:e-p:32:32-i64:64-n32:64-S128-ni:1"
target triple = "wasm32"

; Function Attrs: noinline nounwind optnone
define hidden i32 @add(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %3, align 4
  %7 = mul nsw i32 %5, %6
  %8 = load i32, i32* %4, align 4
  %9 = add nsw i32 %7, %8
  ret i32 %9
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"IsmenaOS clang version 13.0.0 (https://github.com/llvm/llvm-project 0a9d0799316c7a601a0b20a123bd99922ac6455b)"}
