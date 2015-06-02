import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;


public class CFBEncryption {
	
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
	
	// XOR operation
	public String XOR(String x ,String s){
		String xor="";
		for(int i=0 ; i<x.length() ; i++){
			int result = x.charAt(i)^s.charAt(i);
			xor += Integer.toString(result);
		}
		return xor;
	}
	
	// initialization vector ~random~
	public String initiailVector(){
		Random rand = new Random();
		int myRandomNumber;
		String result = "";
		for(int i=0 ; i<16 ; i++){
			myRandomNumber = rand.nextInt(0x10) + 0x10;
		    result = result+Integer.toHexString(myRandomNumber);
		}
		return result;
	}
	
	//convert hexa to binary
	public  String hexToBin(String s) {
		  return new BigInteger(s, 16).toString(2);
		}
	
	// convert binary to hexa
	static String binaryToHexa(String binary){
		int decimal = Integer.parseInt(binary,2);
		return Integer.toString(decimal,16);
	}
	// convert binary message to hexadecimal
	public String binaryMessageToHexa(String binary){
		String str = "";
		String hexa = "";
		for (int i = 0; i < binary.length(); i++) {
			str += binary.charAt(i);
			if((i+1)%8 == 0){
				hexa += binaryToHexa(str);
				str = "";
			}
		}
		return hexa;
	}
	
	//convert to binary
	public String toBinary(int number){
		String binary = Integer.toBinaryString(number);
		return binary;
	}
	
	// padding zeros then divide plain text to 128 bits //~Not used becase the plain text is already devided~
	public ArrayList<String> convertAndDividePlainTex(String s){
		String binaryMessage="";
		for(int i=0 ; i<s.length() ; i++){
			char c = s.charAt(i);
			int assci = (int)c;
			String binary = toBinary(assci);
			while(binary.length()%8 != 0){
				binary = "0"+binary;
			}
			binaryMessage += binary;
		}
		//append zeros to binary
		while(binaryMessage.length()%128 !=0){
			binaryMessage += "0";
		}
		//divide binaryMessage
		ArrayList<String> Xi = new ArrayList<String>();
		String str = "";
		for (int i = 0; i < binaryMessage.length(); i++) {
			str += binaryMessage.charAt(i);
			if((i+1)%128 == 0){
				Xi.add(str);
				str = "";
			}
		}
		return Xi;	
	}
	
	public ArrayList<String> encryption(ArrayList<String>plainTextMessage/*This is the plain text which divided to 128 blocks*/){
		
		Scanner input = new Scanner(System.in);
		String plainText = "";
		String key = "";
		String cipherBinary = "";
		String IV = "";
		IV = initiailVector();
		//System.out.print("Enter Plain text: ");
		//plainText = input.nextLine();
		//System.out.println();
		System.out.print("Enter Key stream: ");
		key = input.next();
		System.out.println("Initialization vector: "+IV);
		System.out.println();
		
		ArrayList<String [][]> PText = new ArrayList<String[][]>();
		ArrayList<String> subkey = new ArrayList<String>();
		String [][] subText = new String[4][4]; 
		
		PlainText p = new PlainText();
		KeyAdditionLayer Klayer = new KeyAdditionLayer();
		AesKey AK = new AesKey();
		SubstitutionLayer s = new SubstitutionLayer();
		ShiftRow sh = new ShiftRow();
		MixColumn MC = new MixColumn();
		
		
		
		//ArrayList<String> xi = convertAndDividePlainTex(plainText);
		ArrayList<String> xi = plainTextMessage;
		ArrayList<String>yi = new ArrayList<String>();
		String y="";
		String yHexa = "";
		for(int k=0 ; k<xi.size() ; k++){
			if(k == 0){
				PText = p.dividText(IV, false);
			}else{
				PText = p.dividText(yHexa, false);
			}
			
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
				
				for(int j=0 ; j<4 ; j++){
					for(int h=0 ; h<4 ; h++){
						String binary = "";
						//convert hexa to binary
						binary = hexToBin(subText[j][h]);
						//check if length != 8 and append zeros
						while(binary.length()%8 != 0){
							binary = "0"+binary;
						}
						cipherBinary += binary;
					}
				}
			    y = XOR(xi.get(k), cipherBinary);
			    //this is an array list of ciphers
			    yi.add(y);
			    //convert binary message to hexa
			    yHexa = binaryMessageToHexa(y);
				System.out.println("this is cipher binarrryy: " + y);
				System.out.println("this is cipher hexaaaaaa: " + yHexa);
			}
			//
		}
		return yi;
		
	}
}