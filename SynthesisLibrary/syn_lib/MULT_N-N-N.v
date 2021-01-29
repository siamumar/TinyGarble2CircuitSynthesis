`timescale 1ns / 1ps

module MULT #(parameter N = 8, M = N)
( 
	input  [N-1:0] A,
	input  [M-1:0] B,
	output [N-1:0] O
);	
    wire [N-1:0] temp[N-1:0]; 
    wire [N-1:0] sum[N:0]; 
	assign sum[0] = {(N){1'b0}};
    
    genvar i;
	generate
	for(i=0;i<N;i=i+1)
	begin:MULT_LOOP
        assign temp[i][N-i-1:0] = A[N-i-1:0] & {(N-i){B[i]}};
        ADD #(.N(N)) ADD_(
				.A({sum[i][N-1:i],{(i){1'b0}}}),
				.B({temp[i][N-i-1:0],{(i){1'b0}}}), 
				.CI(1'b0), 
				.S(sum[i+1]), 
				.CO()
		);
		assign O[i] = sum[i+1][i];
	end
	endgenerate
endmodule