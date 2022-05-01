input  [7:0] minuend;
input  [7:0] subtrahend;
output [7:0] difference;

wire inv_subtrahend_7;
wire inv_subtrahend_6;
wire inv_subtrahend_5;
wire inv_subtrahend_4;
wire inv_subtrahend_3;
wire inv_subtrahend_2;
wire inv_subtrahend_1;
wire inv_subtrahend_0;

wire negator_carry_0;
wire negator_carry_1;
wire negator_carry_2;
wire negator_carry_3;
wire negator_carry_4;
wire negator_carry_5;
wire negator_carry_6;
wire negator_carry_7;

wire neg_subtrahend_7;
wire neg_subtrahend_6;
wire neg_subtrahend_5;
wire neg_subtrahend_4;
wire neg_subtrahend_3;
wire neg_subtrahend_2;
wire neg_subtrahend_1;
wire neg_subtrahend_0;



wire carry_1;
wire diff_ab_1;

wire carry_ab_2;
wire carry_bc_2;
wire carry_ac_2;
wire carry_inter_2;
wire carry_2;
wire diff_ab_2;

wire carry_ab_3;
wire carry_bc_3;
wire carry_ac_3;
wire carry_inter_3;
wire carry_3;
wire diff_ab_3;

wire carry_ab_4;
wire carry_bc_4;
wire carry_ac_4;
wire carry_inter_4;
wire carry_4;
wire diff_ab_4;

wire carry_ab_5;
wire carry_bc_5;
wire carry_ac_5;
wire carry_inter_5;
wire carry_5;
wire diff_ab_5;

wire carry_ab_6;
wire carry_bc_6;
wire carry_ac_6;
wire carry_inter_6;
wire carry_6;
wire diff_ab_6;

wire carry_ab_7;
wire carry_bc_7;
wire carry_ac_7;
wire carry_inter_7;
wire carry_7;
wire diff_ab_7;




assign inv_subtrahend_7 = ~ subtrahend[7];
assign inv_subtrahend_6 = ~ subtrahend[6];
assign inv_subtrahend_5 = ~ subtrahend[5];
assign inv_subtrahend_4 = ~ subtrahend[4];
assign inv_subtrahend_3 = ~ subtrahend[3];
assign inv_subtrahend_2 = ~ subtrahend[2];
assign inv_subtrahend_1 = ~ subtrahend[1];
assign inv_subtrahend_0 = ~ subtrahend[0];

assign negator_carry_0 = inv_subtrahend_0;
assign negator_carry_1 = negator_carry_0 & inv_subtrahend_1;
assign negator_carry_2 = negator_carry_1 & inv_subtrahend_2;
assign negator_carry_3 = negator_carry_2 & inv_subtrahend_3;
assign negator_carry_4 = negator_carry_3 & inv_subtrahend_4;
assign negator_carry_5 = negator_carry_4 & inv_subtrahend_5;
assign negator_carry_6 = negator_carry_5 & inv_subtrahend_6;
assign negator_carry_7 = negator_carry_6 & inv_subtrahend_7;

assign neg_subtrahend_0 = ~ inv_subtrahend_0;
assign neg_subtrahend_1 = negator_carry_0 ^ inv_subtrahend_1;
assign neg_subtrahend_2 = negator_carry_1 ^ inv_subtrahend_2;
assign neg_subtrahend_3 = negator_carry_2 ^ inv_subtrahend_3;
assign neg_subtrahend_4 = negator_carry_3 ^ inv_subtrahend_4;
assign neg_subtrahend_5 = negator_carry_4 ^ inv_subtrahend_5;
assign neg_subtrahend_6 = negator_carry_5 ^ inv_subtrahend_6;
assign neg_subtrahend_7 = negator_carry_6 ^ inv_subtrahend_7;


assign difference[0] = neg_subtrahend_0 ^ minuend[0];

assign carry_1 = neg_subtrahend_0 & minuend[0];
assign diff_ab_1 = neg_subtrahend_1 ^ minuend[1];
assign difference[1] = diff_ab_1 ^ carry_1;

assign carry_ab_2 = neg_subtrahend_1 & minuend[1];
assign carry_bc_2 = minuend[1] & carry_1;
assign carry_ac_2 = neg_subtrahend_1 & carry_1;
assign carry_inter_2 = carry_bc_2 | carry_ac_2;
assign carry_2 = carry_ab_2 | carry_inter_2;
assign diff_ab_2 = neg_subtrahend_2 ^ minuend[2];
assign difference[2] = diff_ab_2 ^ carry_2;

assign carry_ab_3 = neg_subtrahend_2 & minuend[2];
assign carry_bc_3 = minuend[2] & carry_2;
assign carry_ac_3 = neg_subtrahend_2 & carry_2;
assign carry_inter_3 = carry_bc_3 | carry_ac_3;
assign carry_3 = carry_ab_3 | carry_inter_3;
assign diff_ab_3 = neg_subtrahend_3 ^ minuend[3];
assign difference[3] = diff_ab_3 ^ carry_3;

assign carry_ab_4 = neg_subtrahend_3 & minuend[3];
assign carry_bc_4 = minuend[3] & carry_3;
assign carry_ac_4 = neg_subtrahend_3 & carry_3;
assign carry_inter_4 = carry_bc_4 | carry_ac_4;
assign carry_4 = carry_ab_4 | carry_inter_4;
assign diff_ab_4 = neg_subtrahend_4 ^ minuend[4];
assign difference[4] = diff_ab_4 ^ carry_4;

assign carry_ab_5 = neg_subtrahend_4 & minuend[4];
assign carry_bc_5 = minuend[4] & carry_4;
assign carry_ac_5 = neg_subtrahend_4 & carry_4;
assign carry_inter_5 = carry_bc_5 | carry_ac_5;
assign carry_5 = carry_ab_5 | carry_inter_5;
assign diff_ab_5 = neg_subtrahend_5 ^ minuend[5];
assign difference[5] = diff_ab_5 ^ carry_5;

assign carry_ab_6 = neg_subtrahend_5 & minuend[5];
assign carry_bc_6 = minuend[5] & carry_5;
assign carry_ac_6 = neg_subtrahend_5 & carry_5;
assign carry_inter_6 = carry_bc_6 | carry_ac_6;
assign carry_6 = carry_ab_6 | carry_inter_6;
assign diff_ab_6 = neg_subtrahend_6 ^ minuend[6];
assign difference[6] = diff_ab_6 ^ carry_6;

assign carry_ab_7 = neg_subtrahend_6 & minuend[6];
assign carry_bc_7 = minuend[6] & carry_6;
assign carry_ac_7 = neg_subtrahend_6 & carry_6;
assign carry_inter_7 = carry_bc_7 | carry_ac_7;
assign carry_7 = carry_ab_7 | carry_inter_7;
assign diff_ab_7 = neg_subtrahend_7 ^ minuend[7];
assign difference[7] = diff_ab_7 ^ carry_7;



