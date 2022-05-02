input [3:0] numeral_bit;

output a;
output b;
output c;
output d;
output e;
output f;
output g;

wire a_maxterm;
wire a_xorterm1;
wire a_xorterm2;

wire b_xorterm;

wire c_maxterm2;
wire c_maxterm1;

wire d_minterm1;
wire d_minterm2;
wire d_minterm_for_7;
wire d_minterm_inter_1_9;
wire d_minterm_inter_2_9;
wire d_minterm_for_9;
wire d_inter_minterm;

wire e_minterm_1_inter;
wire e_minterm_1;
wire e_minterm_2_inter;
wire e_minterm_2;

wire f_alph_minterm1;
wire f_alph;
wire f_beta_minterm1;
wire f_beta_minterm2;
wire f_beta;
wire f_gamm_minterm1;
wire f_gamm;
wire f_inter;

wire g_minterm_inter;
wire g_minterm;
wire g_inverted;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];



assign a_maxterm = numeral_bit[3] ~| numeral_bit[1];
assign a_xorterm1 = numeral_bit[0] & a_maxterm;
assign a_xorterm2 = numeral_bit[2] & a_maxterm;
assign a = a_xorterm1 ~^ a_xorterm2;

assign b_xorterm = numeral_bit[0] ~^ numeral_bit[1];
assign b = not_numeral_bit_2 | b_xorterm;

assign c_maxterm1 = not_numeral_bit_2 & not_numeral_bit_2;
assign c_maxterm2 = numeral_bit[1] & not_numeral_bit_0;
assign c = c_maxterm1 ~& c_maxterm2;

assign d_minterm1 = numeral_bit[0] & numeral_bit[1];
assign d_minterm2 = numeral_bit[2] & not_numeral_bit_3;
assign d_minterm_for_7 = d_minterm1 & d_minterm2;
assign d_minterm_inter_1_9 = numeral_bit[0] & not_numeral_bit_1;
assign d_minterm_inter_2_9 = not_numeral_bit_2 & numeral_bit[3];
assign d_minterm_for_9 = d_minterm_inter_1_9 & d_minterm_inter_2_9;
assign d_inter_minterm = d_minterm_for_7 | d_minterm_for_9;
assign d = d_inter_minterm ^ a;

assign e_minterm_1_inter = not_numeral_bit_3 & numeral_bit[1];
assign e_minterm_1 = e_minterm_1_inter & not_numeral_bit_0;
assign e_minterm_2_inter = not_numeral_bit_2 & not_numeral_bit_1;
assign e_minterm_2 = e_minterm_2_inter & not_numeral_bit_0;
assign e = e_minterm_1 | e_minterm_2;

assign f_alph_minterm1 = numeral_bit[0] ~& numeral_bit[1];
assign f_alph = not_numeral_bit_3 & f_alph_minterm1;
assign f_beta_minterm1 = numeral_bit[0] ~^ numeral_bit[1];
assign f_beta_minterm2 = numeral_bit[2] | numeral_bit[3];
assign f_beta = f_beta_minterm1 | f_beta_minterm2;
assign f_gamm_minterm1 = numeral_bit[3] & not_numeral_bit_2;
assign f_gamm = f_gamm_minterm1 & not_numeral_bit_1;
assign f_inter = f_alph & f_beta;
assign f = f_gamm | f_inter;

assign g_minterm_inter = not_numeral_bit_3 & not_numeral_bit_2;
assign g_minterm = g_minterm_inter & not_numeral_bit_1;
assign g_inverted = g_minterm | d_minterm_for_7;
assign g = ~ g_inverted;
