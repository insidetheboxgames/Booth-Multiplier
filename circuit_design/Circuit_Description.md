# 8x8 Booth Multiplier 
## Encoding
In this design I used a Radix-16 approach to the encoding. This results into outputs that range from -8 to 7. It takes 5 bits as inputs.\
En is a five bit input from the multiplier. NZ_C stands for Non-Zero Code, Z_C stands for Zero Code. I use these two outputs because there is 17 possible outputs, 8 positive, 8 negative, and 1 zero. Because I use a mux in selecting the result from the generated codes, it is smaller for me to split up the codes for Zero and Non-Zero, and to then use a 16:16 mux and then a 2:16 mux later.\
Example:\
For an 8x8 multiplier there will be two codes generated. The first being generated using the first four bits plus and a zero in the En[0] bit for the first 5 bits of generation. It would then use bit 4 through 7 to generate the second code.

<details>
<summary> The truth table: </summary>

| En[4] | En[3] | En[2] | En[1] | En[0] | NZ_C  |  Z_C  |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|   0   |   0   |   0   |   0   |   0   |    0  |   1   |
|   0   |   0   |   0   |   0   |   1   |    0  |   0   |
|   0   |   0   |   0   |   1   |   0   |    0  |   0   |
|   0   |   0   |   0   |   1   |   1   |    1  |   0   |
|   0   |   0   |   1   |   0   |   0   |    1  |   0   |
|   0   |   0   |   1   |   0   |   1   |    2  |   0   |
|   0   |   0   |   1   |   1   |   0   |    2  |   0   |
|   0   |   0   |   1   |   1   |   1   |    3  |   0   |
|   0   |   1   |   0   |   0   |   0   |    3  |   0   |
|   0   |   1   |   0   |   0   |   1   |    4  |   0   |
|   0   |   1   |   0   |   1   |   0   |    4  |   0   |
|   0   |   1   |   0   |   1   |   1   |    5  |   0   |
|   0   |   1   |   1   |   0   |   0   |    5  |   0   |
|   0   |   1   |   1   |   0   |   1   |    6  |   0   |
|   0   |   1   |   1   |   1   |   0   |    6  |   0   |
|   0   |   1   |   1   |   1   |   1   |    7  |   0   |
|   1   |   0   |   0   |   0   |   0   |   -8  |   0   |
|   1   |   0   |   0   |   0   |   1   |   -7  |   0   |
|   1   |   0   |   0   |   1   |   0   |   -7  |   0   |
|   1   |   0   |   0   |   1   |   1   |   -6  |   0   |
|   1   |   0   |   1   |   0   |   0   |   -6  |   0   |
|   1   |   0   |   1   |   0   |   1   |   -5  |   0   |
|   1   |   0   |   1   |   1   |   0   |   -5  |   0   |
|   1   |   0   |   1   |   1   |   1   |   -4  |   0   |
|   1   |   1   |   0   |   0   |   0   |   -4  |   0   |
|   1   |   1   |   0   |   0   |   1   |   -3  |   0   |
|   1   |   1   |   0   |   1   |   0   |   -3  |   0   |
|   1   |   1   |   0   |   1   |   1   |   -2  |   0   |
|   1   |   1   |   1   |   0   |   0   |   -2  |   0   |
|   1   |   1   |   1   |   0   |   1   |   -1  |   0   |
|   1   |   1   |   1   |   1   |   0   |   -1  |   0   |
|   1   |   1   |   1   |   1   |   1   |    0  |   1   |

</details>

## Calculating
For the positive value codes I essentially take that code add one and then multiply.\
### NZ_C Key
|  NZ_C |   Operation  |    Logical Output    |
|:-----:|:------------:|:--------------------:|
|   0   |     M*1      |          M           |
|   1   |     M*2      |        M<<1          |
|   2   |     M*3      |     (M<<1) + M       |
|   3   |     M*4      |        M<<2          |
|   4   |     M*5      |     (M<<2) + M       |
|   5   |     M*6      |    (M<<2) + (M<<1)   |
|   6   |     M*7      |    (M<<3) - (+M)     |
|   7   |     M*8      |        M<<3          |

To calculate the negative version of the codes, all that is needed is a negation circuit.
### Z_C Key
Z_C being true essentially causes a NOP. This means that the output will be zero.
### Multiple Codes
If multiple codes are generated then after each successive code the output would need to be shifted left 4 more bits than the last time it was shifted.

## Output
The generated output is 16 bits.

## Circuit Analysis
The maximum path in the multiplier is 14 gates. In terms of total gates it is unoptimized because each operation has its own 16 bit CLA (Carry Look Ahead Adder). However this has pushed up the amount of components to about 3762. The largest portions of this are the Muxes at 1536 and the adders at 1730. The adders section could be reduced by getting it down to 2 adders, one for addition and the other for negation. This should take the CLA gate total to 692 gates.