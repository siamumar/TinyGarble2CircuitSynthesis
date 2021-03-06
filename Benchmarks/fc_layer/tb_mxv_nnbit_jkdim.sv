`timescale 1ns / 1ps

module tb_mxv_nnbit_jkdim;

	parameter N = 8, J = 3, K = 3, L = 2*(N-1)+K;
	
	logic	signed	[J*K*N-1:0] g_input;
	logic	signed	[K*N-1:0] 	e_input;
	logic	signed	[J*L-1:0]	o;
	
	logic	signed	[N-1:0] W[J-1:0][K-1:0];
	logic	signed	[N-1:0] X[K-1:0];
	logic	signed	[L-1:0] WX[J-1:0], WX_ref[J-1:0];
	
	integer j, k;
	
	always_comb begin
		for (j = 0; j < J; j = j+1)
			for (k = 0; k < K; k = k + 1)
				g_input[(j*K+k+1)*N-1 -: N] = W[j][k];
				
		for (k = 0; k < K; k = k + 1)
			e_input[(k+1)*N-1 -: N] = X[k];
			
		for (j = 0; j < J; j = j+1)
			WX[j] = o[(j+1)*L-1 -: L];
			
		for (j = 0; j < J; j = j+1) begin
			WX_ref[j] = 0;
			for (k = 0; k < K; k = k + 1)
				WX_ref[j] = WX_ref[j] + W[j][k]*X[k];
		end
	end
	
	mxv_nnbit_jkdim #(.N(N), .J(J), .K(K)) uut( //N: input bit-width, (JxK)(Kx1) = (Jx1)
		.g_input(g_input),
		.e_input(e_input),
		.o(o)
	);
	
	initial begin
		W = '{'{-'d1, 'd2, -'d3}, '{'d2, 'd3, -'d4}, '{-'d4, 'd5, 'd7}};
		//W = '{'{'d1, 'd1, 'd1}, '{'d1, 'd1, 'd1}, '{'d1, 'd1, 'd1}};
		X = '{'d2, 'd3, -'d4};
		//X = '{'d3, 'd3, 'd3};
		#100;
		$stop();
	end


endmodule