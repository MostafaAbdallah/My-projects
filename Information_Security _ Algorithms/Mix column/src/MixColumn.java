import java.util.ArrayList;


public class MixColumn {

	
//====================================== Modulo ===========================================================
	
	String Modulo (String result){
		String res = "";
		int r = 0;
		for (int i = 0; i < result.length(); i++) {
			
			r =  result.charAt(i) - 48;
			r = r % 2;
			res += r; 
		}
		
		return res;	
	}
	
//=========================================================================================================	

//====================================== Long Division=====================================================	
	
	String Xor(String P, String R){
		String res = "";
		int p;
		int r;
		int sum = 0;
		for (int i = 0; i < P.length(); i++) {
			p = P.charAt(i) - 48;
			r = R.charAt(i) - 48;
			sum = (p + r)%2;
			res = res + sum;
 		}
		
		return res;
	}
	
	String LongDivision(String result){
		//String res = "";
		String P = "100011011";
		
		while(result.length()>8)
		{
			P="100011011";
			while(P.length()<result.length())
		      	P = P + "0";
		         result=Xor(P,result);
				 for(int i=0;i<result.length();i++)
				 {
					  if(result.charAt(i)=='1'){
						 result=result.substring(i,result.length());
				         break;
				       }
				  }
		}	
		
		
		return result;
	}
	
	
	
//=========================================================================================================	
	
//====================================== Addition ==========================================================
	
	public String Addition(String result, String cur){
		String res = "";
		int num = Math.max(result.length(), cur.length());
		int r = 0;
		int c = 0;
		
		for (int i = 0; i < cur.length() - result.length() ; i++) {
			result = result + "0";
		}
		
		for (int i = num-1; i >= 0; i--) {
			r = result.charAt(i) - 48;
			c = cur.charAt(i) - 48;
			
			res = (r + c) + res;
		}
		return res;
		
	}
	
//==========================================================================================================	

//======================================= Multiplication ===================================================
	
	public String Multiplication(String E, String B){
		String result = "";
		String Zeros = "";
		String cur = "";	
		int e = 0;
		int b = 0;
		
		for (int i = 0; i < E.length(); i++) {
			cur = Zeros;
			e = E.charAt(i)- 48;
			
			for (int j = 0; j < B.length(); j++) {
				b = B.charAt(j)- 48;
				cur = cur + (e*b);
				
			}
			
			if(i == 0)
				result = cur;
			else
				result = Addition(result, cur);
			
			//System.out.println("res = "+ result);
			
			Zeros = "0" + Zeros;
		}
		//System.out.println("res = "+ result);
		if(result.length() > 8 ){
			
			for (int i = 0; i <result.length()-1 - 8; i++) {
				
				if(result.charAt(i) == '1'){
					result=result.substring(i,result.length());
					
					break;
				}
			}
			//System.out.println("res = "+ result);
			
			//result = result.substring(index, result.length());
		}
		
		result = Modulo(result);
		
		
		if(Integer.parseInt(result, 2) == 0){
			result = result.substring(0, 7);
		}
		if(result.length() > 8){
			result = LongDivision(result);
			
		}
		
		//System.out.println("resM = "+result);
		
		return result;
	}
	
//==========================================================================================================
	
//======================================= Operation on Column ==============================================
	
	private String [][] MixColumnMatrixEncryption = new String [][]{
			{"02", "03", "01", "01"},
			{"01", "02", "03", "01"},
			{"01", "01", "02", "03"},
			{"03", "01", "01", "02"},
			
	};
	
	private ArrayList<String> columnOperatoinEncryption(ArrayList<String> column){
		ArrayList<String> col = new ArrayList<String>();
		ArrayList<String> Element = new ArrayList<String>();
		
		String elem_matrix =null;
		String str = null;
		for (int i = 0; i < 4; i++) {
			Element.clear();
			for (int j = 0; j < 4; j++) {
				elem_matrix = MixColumnMatrixEncryption[i][j];
				elem_matrix = Integer.toBinaryString(Integer.parseInt(elem_matrix, 16));
				//System.out.println(elem_matrix + "----------" + column.get(j) );
				str = Multiplication(elem_matrix, column.get(j));
				
				if(str.length() < 8){
					int l = str.length();
					for (int j2 = 0; j2 < 8 - l; j2++) {
						str = "0" + str;
					}
				}
				
				Element.add(str);
			}
			
			String str1 = "";
			for (int j = 0; j < Element.size(); j++) {
				if(j == 0){
					str1 = Addition(Element.get(j), Element.get(j+1));
					j++;
				}
				else{
					str1 = Addition(Element.get(j), str1);
				}
				
			}
			
			str1 = Modulo(str1);
			col.add(str1);
		}
		
		/*for (int j = 0; j < col.size(); j++) {
			System.out.println("-------"+col.get(j));
		}*/
		
		return col;
	}
//==========================================================================================================	

//======================================= Operation on Column ==============================================
	
	private String [][] MixColumnMatrixDecryption = new String [][]{
			{"0E", "0B", "0D", "09"},
			{"09", "0E", "0B", "0D"},
			{"0D", "09", "0E", "0B"},
			{"0B", "0D", "09", "0E"},
			
	};
	
	private ArrayList<String> columnOperatoinDecryption(ArrayList<String> column){
		ArrayList<String> col = new ArrayList<String>();
		ArrayList<String> Element = new ArrayList<String>();
		
		String elem_matrix =null;
		String str = null;
		for (int i = 0; i < 4; i++) {
			Element.clear();
			for (int j = 0; j < 4; j++) {
				elem_matrix = MixColumnMatrixDecryption[i][j];
				elem_matrix = Integer.toBinaryString(Integer.parseInt(elem_matrix, 16));
				//System.out.println(elem_matrix + "----------" + column.get(j) );
				str = Multiplication(elem_matrix, column.get(j));
				//System.out.println("res = "+ str);
				
				if(str.length() < 8){
					int l = str.length();
					for (int j2 = 0; j2 < 8 - l; j2++) {
						str = "0" + str;
					}
				}
				
				Element.add(str);
			}
			
			String str1 = "";
			for (int j = 0; j < Element.size(); j++) {
				if(j == 0){
					str1 = Addition(Element.get(j), Element.get(j+1));
					j++;
				}
				else{
					str1 = Addition(Element.get(j), str1);
				}
				
			}
			
			str1 = Modulo(str1);
			col.add(str1);
		}
	return col;
	}
//==========================================================================================================	
	
	
//======================================= Select One Column ================================================	
	private String [][]selectColumn(String [][] shiftedRows, boolean Encryption){
		String [][] mixed = new String [4][4];
		ArrayList<String> column = new ArrayList<String>();
		ArrayList<String> columnMixed = new ArrayList<String>();
		
		for (int i = 0; i < 4; i++) {
			column.clear();
			for (int j = 0; j < 4; j++) {
				column.add(shiftedRows[j][i]);
			}
			
			if(Encryption == true)
				columnMixed = columnOperatoinEncryption(column);
			else{
				
				columnMixed = columnOperatoinDecryption(column);
			}
			
			for (int j = 0; j < 4; j++) {
				 mixed[j][i] = columnMixed.get(j);
				
			}
		}
		
		
			
		return mixed;
	}
	
//========================== Convert to 8 bit =============================================================
	
	private String [][]fromHexToBinary(String [][] shiftedRows){
		String [][] b = new String[4][4];
		int num = 0;
		String str;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				num = Integer.parseInt(shiftedRows[i][j], 16);
				str = Integer.toBinaryString(num);
				
				if(str.length() < 8){
					 num =str.length();
					 for (int k = 0; k < 8 - num; k++) {
					      str = "0" + str;
					 }
				}
				b[i][j] = str;
			}
		}
		
		return b;
		
	}
	
//=========================================================================================================	
//========================== Mix Column Main Function ======================================================	
	public String [][]mixColumn(String [][] shiftedRows, boolean Encryption){
		String [][] mixed = new String [4][4];
		String str = "";
		shiftedRows = fromHexToBinary(shiftedRows);
		
		mixed = selectColumn(shiftedRows, Encryption);
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j <4; j++) {
				str = Integer.toHexString(Integer.parseInt(mixed[i][j],2));
				if(str.length() == 1)
					str = "0" + str; 
				mixed[i][j] = str;
			}
		}
		
		return mixed;
	}
	
//=========================================================================================================	
}
