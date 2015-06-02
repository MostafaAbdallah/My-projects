import java.math.BigInteger;
import java.util.ArrayList;


public class KeyAdditionLayer {
	
	PlainText p = new PlainText();
	//Key key = new Key();
	ArrayList<String>text = new ArrayList<String>();
	private ArrayList<ArrayList<String>> texts = new ArrayList<ArrayList<String>>();
	private ArrayList<String> subKey = new ArrayList<String>();
	private ArrayList<String> afterAddition = new ArrayList<String>();
	
	//hexa to binary
	public ArrayList<String> hexaToBinary(ArrayList<String> s){
		ArrayList<String> toBinary = new ArrayList<String>();
		for(int i=0 ; i<s.size() ; i++){
			// append zeros if binary length less than 8
			String binary = new BigInteger(s.get(i),16).toString(2);
			toBinary.add(binary);
		}
		return toBinary;
	}
	
	public String binaryToHexa(String binary){
		int decimal = Integer.parseInt(binary,2);
		return Integer.toString(decimal,16);
	}
	
	// XOR operation
	public String XOR(String text , String key){
		String xor="";
		for(int i=0 ; i<text.length() ; i++){
			int x = text.charAt(i)^key.charAt(i);
			xor += Integer.toString(x);
		}
		return xor;
	}
	
	// key addition operation
	
	String oneVector(String [][] str){
		String s = "";
		String s2 = "";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				s2 = str[j][i];
				
				s2 = Integer.toBinaryString(Integer.parseInt(s2, 16));
				if(s2.length() < 8 ){
					int num = s2.length();
					for (int k = 0; k < 8 - num; k++) {
						s2 = "0"+ s2;
					}
				}
				s = s + s2;
			}
		}
		
		return s;
	}
	
	String[][] toArray(String str){
		String [][] s = new String [4][4];
		int it = 8;
		String s2 ="";
		//System.out.println(str.length());
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				s2 = str.substring(it-8, it);
				s2 = Integer.toHexString(Integer.parseInt(s2,2));
				if(s2.length() == 1){
					s2 = "0" + s2;
				}
				s[j][i] = s2;
				it = it + 8;
			}
		}
		
		return s;
	}
	
	
	public String[][] keyAddition(String[][] s, String subKey){
		
		String res = "";
			res = oneVector(s);
		
			res = XOR(res, subKey);
			s = toArray(res);	
			return s;
	}
	
	public void print(){
		for(int i=0 ; i<afterAddition.size() ; i++){
			System.out.print(afterAddition.get(i)); System.out.print(" ");
		}
	}
	
	public void printHexa(){
		for(int i=0 ; i<afterAddition.size() ; i++){
			System.out.print(binaryToHexa(afterAddition.get(i))); System.out.print(" ");
		}
	}

}
