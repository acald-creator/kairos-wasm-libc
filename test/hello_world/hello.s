	.text
	.file	"hello.c"
	.section	.text.add,"",@
	.hidden	add                             # -- Begin function add
	.globl	add
	.type	add,@function
add:                                    # @add
	.functype	add (i32, i32) -> (i32)
# %bb.0:
	local.get	0
	local.get	0
	i32.mul 
	local.get	1
	i32.add 
                                        # fallthrough-return
	end_function
.Lfunc_end0:
	.size	add, .Lfunc_end0-add
                                        # -- End function
	.ident	"IsmenaOS clang version 13.0.0 (https://github.com/llvm/llvm-project 0a9d0799316c7a601a0b20a123bd99922ac6455b)"
	.section	.custom_section.producers,"",@
	.int8	1
	.int8	12
	.ascii	"processed-by"
	.int8	1
	.int8	14
	.ascii	"IsmenaOS clang"
	.int8	86
	.ascii	"13.0.0 (https://github.com/llvm/llvm-project 0a9d0799316c7a601a0b20a123bd99922ac6455b)"
	.section	.text.add,"",@
