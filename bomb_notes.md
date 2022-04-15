# phase 2
0 1 1 2 3 5


# phase 3
trying with 4 0
4 228

num #1 <= 7


# phase 4
8 0 
first number <= 14

8  0 => 35
8  5 => 35
9  0 => 
10 0 => 37
10 1 => 37
11 0 => 18
12 0 => 43
13 0 => 31
14 0 => 

0  0 => 11
1  0 => 11
2  0 => 13
3  0 => 
4  0 => 
5  0 => 
6  0 => 
7  0 => 

2 13

Somehow we need to get something equal to 13



# phase 6
Nodes 1-5: 0x555555559220
Node 6:    0x555555559110

0x555555559220 <node1>: 388     1       1431671392      21845
0x555555559230 <node2>: 473     2       1431671328      21845
0x555555559240 <node3>: 325     3       0       0
0x555555559250 <node4>: 227     4       1431671360      21845
0x555555559260 <node5>: 753     5       1431671056      21845
0x555555559110 <node6>: 544     6       1431671376      21845



order
--------
   === A ===
4   3   1   2   6   5    => 4 3 1 2 6 5
227 325 388 473 544 753

   === B ===
5   6   2   1   3   4    => 5 6 2 1 3 4
753 544 473 388 325 227

Print nodes 1-5
x /20wd 0x555555559220
x /20wx 0x555555559220
$rdx = nodes

Print node 6
x /6wd 0x555555559110
x /6wx 0x555555559110

Print array of indicies
x /6wd $r14




1 | 388 | 3 | 4
2 | 473 | 4 | 3
3 | 325 | 2 | 5
4 | 227 | 1 | 6
5 | 753 | 6 | 1
6 | 544 | 5 | 2

4 3 1 2 6 5

4   3   1   2   6   5
227 325 388 473 544 753

$r14 = node order

Somehow 753 is being compared to 388 in reverse order ??

5   6   2   1   3   4
753 544 473 388 325 227


$rbp has the number

$eax starts at 1
We add ($rbp) to $eax

Then we compare $eax to $rbp[1]

Some kind of fibinocci ?
1 2 4 7 11 16
third number is somehow 7 ?

phase 3:

num #1 <= 7

phase 5:
String of length


There's this string ?
maduiersnfotvbyl

but it needs to equal stage
abcdef => aduier
aduier => aiefed
stage!

sduiet

a and the e stay the same ?

In the loop, $edx = current character
$edx &= $0xf (which does nothing ?)
No so apparently characters are 2 bytes ??

oilers ???
not stage! ??


!!!!!
Add multiple breakpoints within explode_bomb


Loop 1
 - Take first letter
 - &= 0xf (take first 4 bits)
 - somehow get an l?

Loop 2
 - Take second letter
 - &= 0xf (????)
 - somehow get an f ? into $edx

v


l f v e is being built from something, not so sure what exactly though ngl

oilers => lfvedu
l f v e d u
compare to:
stage!





$dl is the least significant byte, and is loaded from $rcx (maduiersnfotvbyl)

Testing if mapping is character by character

a b c d e f => aduier
b d e a f c => diearu

target: stage!
[x] s | g, w, '
[x] t | k, [
[x] a | a, q, !
[ ] g | 
[x] e | e, u, %
[ ] ! | 

Let me try constructing what I can of stage! and figure out the others
afterwards

g = 0110_0111
0110_xxxx = { `, a, b, c, d, e, f, g, h, i, j, k, l, m, n }
xxxx_0111 = { ', 7, G, W, g, w } and then some fake characters somehow

abc def

a: 0110_0001 &=> 0000_0001
0001_0001 => 

Why does b turn into d ????v

gka_e_ => stalel
Yes it worked :D

oilers:
zdoefw

si

[ ] o | j, z
[ ] i | d, t, $
[ ] l | o, ?, /
[ ] e | e, u, %
[ ] r | f, v, &
[ ] s | w, '

f | i, y, )
l | o, ?, /
y | n, >, ^
e | e, u, % 
r | f, v, &
s | w,
ionefw

$rsp + 0x1

------
a | a
b | d
c | u
d | i
e | e
f | r
g | s
h | n
i | f
j | o
k | t
l | v
m | b
n | y
o | l
p | m
q | a
r | d
s | u
t | i
u | e
v | r
w | s
x | n
y | f
z | o
! | a
" | d
' | s
, | v
? | l ?/><+-
/ | l
> | y
< | v
+ | t
- | b
= | b =@#$%^
@ | m
# | u
$ | i
% | e
^ | y
& | r &*()_~
* | o
( | n
) | f
_ | l
~ | y
` | m `[]{}|
[ | t
] | b
{ | t
} | b
| | v




# Phase 6
1 2 3 4 5 6

first number <= 5

$r13 = array







