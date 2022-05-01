input [3:0] numeral_bit;

output e;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire minterm_00;
wire minterm_02;
wire minterm_06;
wire minterm_08;

wire minterm_intermediate_1;
wire minterm_intermediate_2;

wire minterm_A;
wire minterm_B;

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];

assign minterm_intermediate_1 = not_numeral_bit_3 & numeral_bit[1];
assign minterm_A = minterm_intermediate_1 & not_numeral_bit_0;

assign minterm_intermediate_2 = not_numeral_bit_2 & not_numeral_bit_1;
assign minterm_B = minterm_intermediate_2 & not_numeral_bit_0;

assign e = minterm_A | minterm_B;
