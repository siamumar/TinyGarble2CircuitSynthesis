`timescale 1ns / 1ps

module DIV #( parameter N = 8, M = N )( 
	input  [N-1:0] A,
	input  [M-1:0] B,
	output [N-1:0] O
);

	wire	[N+M-2:0] A_[N:0];
	wire	[M-1:0] D[N-1:0];
		
	assign	A_[N] = {{M-1{1'b0}}, A};

	genvar g;
	
	generate
	for(g = N-1; g >= 0; g = g - 1)
	
	begin:DIV_UNIT
		if (g > 0) begin
		
		SUB #(.N(M)) SUB_1(
			.A(A_[g+1][M+g-1:g]),
			.B(B),
			.S(D[g]), 
			.CO(O[g])
		);
		
        assign A_[g][g-1:0] = A_[g+1][g-1:0]; 

		end else begin
		
		SUB #(.N(M)) SUB_2(
			.A(A_[g+1][M+g-1:g]),
			.B(B),
			.S(D[g]), 
		 	.CO(O[g])
		);
			     
        end
				
         MUX #(.N(M)) MUX(     
              .A(A_[g+1][M+g-1:g]),
              .B(D[g]),
              .S(O[g]),
              .O(A_[g][M+g-1:g])
          );
          
	   end
	endgenerate
endmodule