import java.util.ArrayList;
import java.util.Scanner;


public class Encryption {
	
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
	
	String oneVectorbit(String [][] str){
		String s = "";
		String s2 = "";
		String num = "";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				s2 = str[j][i];
				num = Integer.toBinaryString(Integer.parseInt(s2, 16));
				//System.out.println((char)num +"------" + num);
				if(num.length()<8){
					for (int j2 = num.length(); j2 < 8; j2++) {
						num = "0" + num;
					}
				}
				s = s + num;
				 
			}
		}
		
		return s;
	}
	String encryption(String plainText, String key ){
		
		//Scanner input = new Scanner(System.in);
		//String key = "";
		//System.out.print("Enter Key stream: ");
		//key = input.next();
		System.out.println();
		String c = "";
		String Cipher = "";
		
		ArrayList<String [][]> PText = new ArrayList<String[][]>();
		ArrayList<String> subkey = new ArrayList<String>();
		ArrayList<String> cipherbitmap = new ArrayList<String>();
		String [][] subText = new String[4][4]; 
		
		PlainText p = new PlainText();
		KeyAdditionLayer Klayer = new KeyAdditionLayer();
		AesKey AK = new AesKey();
		SubstitutionLayer s = new SubstitutionLayer();
		ShiftRow sh = new ShiftRow();
		MixColumn MC = new MixColumn();
		
		PText = p.dividText(plainText, true);
		AK.toHex(key);
		subkey = AK.Key();
		
		for (int i = 0; i < PText.size(); i++) {
			subText = PText.get(i);
			
			subText = Klayer.keyAddition(subText, subkey.get(0));
			
			for (int j = 0; j < 10; j++) {
				
				subText = s.subLayer(subText, true);
				subText = sh.shiftRowEncryption(subText);
				if(j != 9)
				subText = MC.mixColumn(subText, true);
				subText = Klayer.keyAddition(subText, subkey.get(j+1));
			}
			Cipher =  oneVectorHex(subText);
			
			c = oneVectorbit(subText);
			
			
			
		}
		System.out.println("Cipher : " + Cipher);
		return c;
		
	}
}


/*for (int j2 = 0; j2 < 4; j2++) {
					for (int k = 0; k < 4; k++) {
						System.out.print(subText[j2][k] + " ");
					}
					System.out.println();
				}
				break;
				
*/
