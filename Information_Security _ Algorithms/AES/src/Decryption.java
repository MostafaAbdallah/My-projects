import java.util.ArrayList;
import java.util.Scanner;


public class Decryption {

	String oneVectorChar(String [][] str){
		String s = "";
		String s2 = "";
		int num = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				s2 = str[j][i];
				num = (Integer.parseInt(s2, 16));
				//System.out.println((char)num +"------" + num);
				s = s + (char)num;
				 
			}
		}
		
		return s;
	}
	String oneVectorHex(String [][] str){
		String s = "";
		String s2 = "";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				s2 = str[j][i];
				
				s = s + s2;
				s = s + " "; 
			}
		}
		
		return s;
	}
	
	
	void decryption(){
		Scanner input = new Scanner(System.in);
		String cipher = "";
		String key = "";
		String plainText = "";
		String plainTextHex = "";
		System.out.print("Enter Cipher text: ");
		cipher = input.next();
		System.out.println();
		System.out.print("Enter Key stream: ");
		//key = input.next();
		System.out.println();
		
		ArrayList<String [][]> CText = new ArrayList<String[][]>();
		ArrayList<String> subkey = new ArrayList<String>();
		String [][] subText = new String[4][4]; 
		
		PlainText p = new PlainText();
		KeyAdditionLayer Klayer = new KeyAdditionLayer();
		AesKey AK = new AesKey();
		SubstitutionLayer s = new SubstitutionLayer();
		ShiftRow sh = new ShiftRow();
		MixColumn MC = new MixColumn();
		
		CText = p.dividText(cipher, false);
		
		AK.toHex(key);
		AK.out();
		subkey = AK.decrypKey();
		System.out.println("---" + subkey.size());
		for (int i = 0; i < CText.size(); i++) {
			subText = CText.get(i);
			for (int j = 0; j < 10; j++) {
				
				subText = Klayer.keyAddition(subText, subkey.get(j));
				if(j != 0)
					subText = MC.mixColumn(subText, false);
				subText = sh.shiftRowDecryption(subText);	
				subText = s.subLayer(subText, false);
				
				
				
			}
			
			subText = Klayer.keyAddition(subText, subkey.get(10));
			
			
			
			plainTextHex = plainTextHex + oneVectorHex(subText);
			plainText = plainText + oneVectorChar(subText);
			
		}
		

		System.out.println("plainTextHex: "+plainTextHex);
		System.out.println("plainTextChar: "+plainText);
		
		

	}	
}
