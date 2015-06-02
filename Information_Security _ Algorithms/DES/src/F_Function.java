import java.util.ArrayList;


public class F_Function {
	
	
//=====================	Expansion Matrix ========================================================
	private int E[][] = new int[][]{
						{32, 1, 2, 3, 4, 5},
						{4, 5, 6, 7, 8, 9},
						{8, 9, 10, 11, 12, 13},
						{12, 13, 14, 15, 16, 17},
						{16, 17, 18, 19, 20, 21},
						{20, 21, 22, 23, 24, 25},
						{24, 25, 26, 27, 28, 29},
						{28, 29, 30, 31, 32, 1}
						};
	
	private String Expansion(String R){
		String R_expanded = "";
		 for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				 R_expanded += R.charAt(E[i][j]-1);
			}
		}
		 
		 return R_expanded;
		
	}
	
//================================================================================================

//======================== XOR Function ==========================================================
	
	private String XOR(String R, String K){
		String R_XOR_K = "";
		int sum = 0;
		int r, k;
		
		for (int i = 0; i < R.length(); i++) {
			sum = 0;
			r =  R.charAt(i) - 48;
			k =  K.charAt(i) - 48;
			
			sum = (r + k) % 2;
			R_XOR_K += sum; 
			
		}
		
		return R_XOR_K ;
	}
	
	
//================================================================================================	
//================================ Divide The 48-bit into eight 6-bit ============================
	
	ArrayList<String> Divide_48_bit_into_eight_6_bit(String R_XOR_K){
		ArrayList<String> subStrings = new ArrayList<String>();
		String str = "";
		for (int i = 0; i < R_XOR_K.length(); i++) {
			
			str += R_XOR_K.charAt(i);
			if((i+1)%6 == 0){
				
				subStrings.add(str);
				str = "";
			}
		}	
		return subStrings;
	}
	
//================================================================================================

//============================== S- BOXS =========================================================
	private int S_box1[][] = new int[][]{
			
			{14,  4,   13,  1,  2,   15, 11,  8,  3,   10,  6,  12,  5,   9,   0,   7},
			{0,   15,  7,   4,  14,  2,  13,  1,  10,  6,   12, 11,  9,   5,   3,   8},
			{4,   1,   14,  8,  13,  6,  2,   11, 15,  12,  9,  7,   3,   10,  5,   0},
			{15,  12,  8,   2,  4,   9,  1,   7,  5,   11,  3,  14,  10,  0,   6,   13},
			};
	
	
	private int S_box2[][] = new int[][]{
		
			{15,  1,    8,   14,   6,   11,  3,   4,   9,    7,    2,   13,    12,   0,   5,    10},
			{3,   13,   4,   7,    15,  2,   8,   14,  12,   0,    1,   10,    6,    9,   11,   5},
			{0,   14,   7,   11,   10,  4,   13,  1,   5,    8,    12,  6,     9,    3,   2,    15},
			{13,  8,    10,  1,    3,   15,  4,   2,   11,   6,    7,   12,    0,    5,   14,   9},
			};
	
	private int S_box3[][] = new int[][]{
			
			{10, 0,  9,  14,  6,  3,   15,  5,   1,   13,  12,   7,     11,   4,   2,   8},
			{13, 7,  0,  9,   3,  4,   6,   10,  2,   8,   5,    14,    12,   11,  15,  1},
			{13, 6,  4,  9,   8,  15,  3,   0,   11,  1,   2,    12,    5,    10,  14,  7},
			{01, 10, 13, 0,   6,  9,   8,   7,   4 ,  15,  14,   3,     11,   5,   2,   12},
			};
	
	private int S_box4[][] = new int[][]{
			
			{7,   13,  14,  3,  0,   6,   9,   10,   1,    2,   8,   5,     11,   12,  4,   15},
			{13,  8,   11,  5,  6,   15,  0,   3,    4,    7,   2,   12,    1,    10,  14,   9},
			{10,  6,   9,   0,  12,  11,  7,   13,   15,   1,   3,   14,    5,    2,   8,    4},
			{03,  15,  0,   6,  10,  1,   13,  8,    9,    4,   5,   11,    12,   7,   2,   14},
			};
	
	private int S_box5[][] = new int[][]{
			
			{2,   12,  4,   1,   7,   10,  11,  6,  8,  5,  3,  15,  13,  0,  14,  9},
			{14,  11,  2,   12,  4,   7,   13,  1,  5,  0,  15, 10,  3,   9,  8,   6},
			{4,   2,   1,   11,  10,  13,  7,   8,  15, 9,  12, 5,   6,   3,  0,   14},
			{11,  8,   12,  7,   1,   14,  2,   13, 6,  15, 0,  9,   10,  4,  5,   3},
			};
	
	private int S_box6[][] = new int[][]{
			
			{12,   1, 	10,  15,  9,   2,   6,   8,   0,  13,  3,   4,   14,  7,   5,  11},
			{10,   15, 	4,   2,   7,   12,  9,   5,   6,  1,   13,  14,  0,   11,  3,  8},
			{9,    14, 	15,  5,   2,   8,   12,  3,   7,  0,   4,   10,  1,   13,  11, 6},
			{4,    3, 	2,	 12,  9,   5,   15,  10,  11, 14,  1,   7,   6,   0,   8,  13},
			};
	
	private int S_box7[][] = new int[][]{
			
			{4,   11,  2,   14,  15,  0,  8,  13,  3,  12,  9,  7,  5,   10,  6,  01},
			{13,  0,   11,  7,   4,   9,  1,  10,  14, 03,  5,  12, 2,   15,  8,  06},
			{1,   4,   11,  13,  12,  3,  7,  14,  10, 15,  6,  8,  0,   5,   9,  02},
			{6,   11,  13,  8,   1,   4,  1,  7,   9,  5,   0,  15, 14,  2,   3,  12},
			};
	private int S_box8[][] = new int[][]{
			
			{13,  2,   8,   4,  6,  15,  11,  1,  10,  9,   3,   14,  5,   0,   12, 7},
			{1,   15,  13,  8,  10, 3,   7,   4,  12,  5,   6,   11,  0,   14,  9,  2},
			{7,   11,  4,   1,  9,  12,  14,  2,  0,   6,   10,  13,  15,  3,   5,  8},
			{2,   1,   14,  7,  4,  10,  8,   13, 15,  12,  9,   0,   3,   5,   6,  11},
			};
	
	
	private int binary_TO_Integer(String bits){
		int num = 0;
		
		num = Integer.parseInt(bits, 2);
		
		return num;
	}
	
	private String Extract_4_bit(int row, int columu, int numOfS_box){
		String str = "";
		int numFromS_box = 0;	
		
		if(numOfS_box == 1)
			numFromS_box = S_box1[row][columu];
		
		else if(numOfS_box == 2)
			numFromS_box = S_box2[row][columu];
		
		else if(numOfS_box == 3)
			numFromS_box = S_box3[row][columu];
		
		else if(numOfS_box == 4)
			numFromS_box = S_box4[row][columu];
		
		else if(numOfS_box == 5)
			numFromS_box = S_box5[row][columu];
		
		else if(numOfS_box == 6)
			numFromS_box = S_box6[row][columu];
		
		else if(numOfS_box == 7)
			numFromS_box = S_box7[row][columu];
		
		else if(numOfS_box == 8)
			numFromS_box = S_box8[row][columu];
		
		
		
		
		str = Integer.toString(numFromS_box,2);
		
		
		return str;
	} 
	
	
	private String S_boxs(ArrayList<String> subStrings){
		String converted_4_bit = "";
		String M_LSBit ="";
		String innerBits ="";
		String str ="";
		int row = 0;
		int columu = 0;
		int num =0;
		for (int i = 0; i < subStrings.size(); i++) {
			M_LSBit ="";
			
			M_LSBit += subStrings.get(i).charAt(0);
			M_LSBit += subStrings.get(i).charAt(subStrings.get(i).length()-1) ;
			row = binary_TO_Integer(M_LSBit);
			
			innerBits = subStrings.get(i).substring(1, 5);
			columu = binary_TO_Integer(innerBits);
			
			str = Extract_4_bit(row, columu, i+1);
			
			if(str.length() != 4){
				 num =str.length();
				for (int j = 0; j < 4 - num; j++) {
					str = "0" + str;
				}
			}
			converted_4_bit += str;
			
		}
		
		
		
		return converted_4_bit;
	}

//================================================================================================	

//================================ permutation P =================================================
	
	private int P[][] = new int[][]{
		
			{16,  7,  20,   21,  29,  12,  28,   17},
			{1,   15, 23,   26,  5,   18,  31,   10},
			{2,   8,  24,   14,  32,  27,  3,     9},
			{19,   13, 30,   6,   22,  11,  4,    25},
		};
	
	private String Permutation(String R_XOR_K){
		String str = "";
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				str += R_XOR_K.charAt(P[i][j]-1);
			}
		}
		
		return str;
		
	}
	
	
//================================================================================================	
	
	public String F_function(String R, String K){
		String R_expanded = "";
		String R_XOR_K = "";
		ArrayList<String>subStrings = new ArrayList<String>();
		R_expanded = Expansion(R);
		
		R_XOR_K = XOR(R_expanded, K);
		
		subStrings = Divide_48_bit_into_eight_6_bit(R_XOR_K);
		
		R_XOR_K = S_boxs(subStrings);
		
		R_XOR_K = Permutation(R_XOR_K);
		
		//System.out.println(R_XOR_K);
		
		return R_XOR_K;
	}
}
