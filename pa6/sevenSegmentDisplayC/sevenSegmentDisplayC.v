input [3:0] numeral_bit;

output c;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire maxterm_interm1;
wire maxterm_interm2;
wire maxterm_02;

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];

assign maxterm_interm1 = not_numeral_bit_3 & not_numeral_bit_2;
assign maxterm_interm2 = numeral_bit[1] & not_numeral_bit_0;
assign maxterm_02 = maxterm_interm1 & maxterm_interm2;

assign c = ~ maxterm_02;
