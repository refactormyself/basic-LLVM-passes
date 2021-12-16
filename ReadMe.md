# TO BUILD
Pass in the installation directory of LLVM: 

`$ run-all.sh /path/to/llvm/install`


# Collection of Simple LLVM Compile-Time Optimisation Passes
### What do those worlds mean ?1

## LLVM
Start as a sort of baby JVM but hatched into something else entirely. 
That is why (IMHO) only a dragon logo fits it.

It is now a collection of tools for systems level development. 
It also includes within it some compiler which are built with its tools, notably *Clang*. But its not the only compiler ofspring of LLVM.

## Optimisation
In the compiler domain this word refer to any operation that happens after the semantic analysis which does not involve code generation. This can either be a
- "Transformation" which changes the structural form of the code
- "Analysis" which gathers some information about the current state of the code


## Compile-Time
No it's not a mistake. Remember those days when we used to a box called the CPU and you can open it and change the CPU inside it ;). It's a computing thing naming is hard!

- There is the "Compile-Time" before the machine code (almost assembly) of the code is generated.
- There is the "(machine) Code Generation Time" after which we have a binary which can either be run directly or linked to.
- There is the "Link Time" when more than one binaries are being linked together to form a single one which we can run.
- There is the "Run Time" when we finally have a single binary and we are now running/executing it

In all of the above **"times"** it is possible to perform some degree of optimisation. Though the ease of doing it vary.

## Passes
The plural of **pass**. "Pass" as in passing though a session of one or more operations. In this case, this session is an Optimisation. The major characteristic of a pass is that the entity that goes though it comes out of it, though it may have been restructured internally, it must still conform with the generic definition of that entity. In our case the "entity" we are passing though the Optimisation is our code but at this stage it is now expressed in an Intermediate Representation language (IR).

For the Compile-Time passes LLVM uses the "LLVM IR". Yes there are other IRs within LLVM with some variations to express granular construct which are necessary has the code mode closer and closer to the bits. So a pass at compile-time will accept any code written in LLVM IR and produce a code written in LLVM IR. This is the big deal about LLVM, because it is the first to do this nicely (at the right place & at the right time).

The implication of this is that you can have as much optimiation has you want. You can mismatch them in any way you want. Of course a pass is implemented as a code and you can simply call a pass's implementation from another, however this couples both passes together. The fuzz about LLVM comes from the fact that you can implement 1000 optimisations seperately and then decide if, when, how or which of them you want to use. This modularity is the power of LLVM.

LLVM IR is a language. A *strongly typed* one! It this language everything exist inside a **Module**. A Module contains one or more **Functions** which represents methods/functions in real code. A function contains one or more **Basic Blocks**. A Basic Block contains one or more **Instructions**. An instruction is a single atomic code operation (e.g mov, add etc). They design as RISC-like instruction and use similar terminologies except that in this case the number of registers is inifinite. You can think of a Basic Block as a set of instruction which are "expected" to execute sequentially without branching.

## Collection of Simple Passes
I don't like the work trivial. These are simple passes just to introduce what is possible. I don't regards them as trivial because running these simple passes in the compilation of a trivial application like pacman will give serious insight e.g how many instructions are run after applying O1, O2 or O3 flags. I think this is non trivial but LLVM makes it so simple it can be done with few lines of code.

The following are my simple passes:
- 

## References:
I have use the following resources in puting these together.
- https://llvm.org/docs/WritingAnLLVMNewPMPass.html
- A. Warzynski “Writing an LLVM Pass: 101” https://www.youtube.com/watch?v=ar7cJl2aBuU 
- https://www.cs.cornell.edu/~asampson/blog/llvm.html
