import java.math.BigInteger;
import java.util.ArrayList;

public class PlainText {
	
	// append zeros to plain text
	String appendZerosToPlainTex(String s){
		while(s.length()%16 !=0){
			s = s+"0";
		}
		return s;
	}
	// convert string to hexadecimal
	 ArrayList<String> convertToHexa(String s){
		ArrayList<String> plainText = new ArrayList<String>();
		for(int i=0 ; i<s.length() ; i++){
			char c = s.charAt(i);
			String hexa = String.format("%02x", (int) c);
			plainText.add(hexa);
		}
		return plainText;
	}
	
	ArrayList<String [][]> toArray(ArrayList<String> s){
		ArrayList<String[][]> p = new ArrayList<String[][]>();
		String [][] str = new String[4][4];
		int it = 0;
		System.out.println(s.size());
		while(it < s.size()) {
			
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					str[k][j] = s.get(it);
					it++;
				}
			}
			p.add(str);
		}
		
		
		return p;
	}
	
	
	ArrayList<String> toArraylist(String s){
		ArrayList<String> hex = new ArrayList<String>();
		String str ="";
		for (int i = 2; i <= s.length(); i = i +2) {
			str = s.substring(i-2, i);
			hex.add(str);
		}
		
		return hex;
		
	}
	
	public ArrayList<String [][]> dividText(String plainText, boolean hex){
		ArrayList<String[][]> P = new ArrayList<String[][]>();
		ArrayList<String> s = new ArrayList<String>();
		plainText = appendZerosToPlainTex(plainText);
		if(hex == true)
			s = convertToHexa(plainText);
		else
			s = toArraylist(plainText);
		
		P = toArray(s);
		
		return P;
	}
	
}
