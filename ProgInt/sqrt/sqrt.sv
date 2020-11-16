`timescale 1ns / 1ps

module sqrt #(parameter N = 8)(
	input	[N-1:0]	s_input,
	output	[N/2-1:0] o
);	 		
		
	square_root_comb #(.N(N)) square_root_comb(
	 	.A(s_input),
		.O(o)
	);
		
endmodule