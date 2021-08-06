# 模拟高精度

最朴素而直接的思路，便是在计算机中模拟竖式算数，即，用数组记录一个十进制数中的各个位数。

为了方便，一般会将各个数位倒序存在数组中，比如十进制数 12345，可以存储为 `[5, 4, 3, 2, 1]`。如此，高位的增长，只需要在数组的末尾增加就好，更为高效。

不过我们很快发现，如果只用一个 `int`（或者 `char`）存一位十进制数是较为浪费的。我们也可以直接用多个 `int` 或者 `char` 来表示一个很长的二进制数。

64 位计算机一次只能处理长度 64 位的二进制数，那我们也可以对这个多个数据拼起来的“长数”，按照竖式计算的原则计算就可以了（也就是一个 $2^n$ 进制数）。

但是有个问题，就是输出时 2 进制和 10 进制的转换。

比如无符号二进制数 1011 和 0101 对应到十进制数就是 11 和 5。直接将数位拼接起来，得到 115，而不是 1011 0101 表示的 181。

至于转换进制，我们一般用“无余数除”和“取模运算。对于我们的 64 或者 32 位二进制数，计算机有相应的指令，可以很快地进行运算。但对于我们模拟出来的“长数”，则需要一定的处理。

所以，也可以只用数据类型范围内的 10 的若干次幂（$10^n$）作为进制。这样直接转换成 10 进制数，拼接后输出，不会有问题（需要在输出时对不足 n 位的段进行补 0）。

但，上述使用二进制的方法有一个优势，可以利用自然溢出的特性实现取模。

用十进制数来举例，在计算 5 + 8 时，会产生一位进位，然后在该位上应该留下 `(5+8)%10`，也就是 3

而自然溢出就是指，5 + 8，进位的 1 因为超出了数位长度，被自动丢弃，不用进行 `%` 取模运算了，因此提高效率。

> C 语言中的加减法都会编译到 CPU 的 `addu`、`subu` 指令，也就是 C 语言不负责数据溢出的判断。
>
> 如果要使用自然溢出的话，需要在编程时声明无符号变量，以便正确对变量中存储的数据应用操作，比如，在 C/C++ 中可以声明 `unsigned int`、`unsigned char` 等类型的变量。
