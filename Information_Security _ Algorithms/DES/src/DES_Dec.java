import java.math.BigInteger;
import java.util.ArrayList;


public class DES_Dec {
	
	private String hexToBin(String hex){
	    String bin = "";
	    String binaryyyyy = "";
	    int iHex;
	    hex = hex.trim();
	    hex = hex.replaceFirst("0x", "");

	    for(int i = 0; i < hex.length(); i++){
	        iHex = Integer.parseInt(""+hex.charAt(i),16);
	        binaryyyyy = Integer.toBinaryString(iHex);

	        while(binaryyyyy.length() < 4){
	        	binaryyyyy = "0" + binaryyyyy;
	        }
	        bin += binaryyyyy;
	    }
	   // System.out.println(bin);
	    return bin;
	}
	
	public String hexaToBinary(String s){
		
		String binary = new BigInteger(s,16).toString(2);
		if(binary.length() < 64){
			int num = binary.length();
			for (int i = num; i < 64; i++) {
				binary = "0" + binary;
			}
		}
		//System.out.println(s);
		//System.out.println(binary);
		return binary;
	}
	
	public String appendZeros(String cipher){
		while(cipher.length()%64 !=0){
			cipher += "0";
		}
		
		return cipher;
	}
	
	ArrayList<String> divide(String cipher){
		ArrayList<String> C = new ArrayList<String>();
		String str = "";
		for (int i = 0; i < cipher.length(); i++) {
			str = str + cipher.charAt(i);
			if((i+1)%64 ==0){
				C.add(str);
				str = "";
			}
		}
		
		
		return C;
	}
	
	
	String Decreption(String ciphertext, String key){
		
		PermutationChoice pc = new PermutationChoice();
		LandR lr = new LandR(key);
		
		String Plaintext = "";
		ArrayList<String> cipherE = new ArrayList<String>();
		ArrayList<String>ipD = new ArrayList<String>();
		
		ArrayList<String>ipLeftRightE = new ArrayList<String>();
		ArrayList<String>ipLeftRightD = new ArrayList<String>();
		ArrayList<String>plainD = new ArrayList<String>();
		
		ciphertext = hexaToBinary(ciphertext);
		ciphertext = appendZeros(ciphertext);
		cipherE = divide(ciphertext);
		//System.out.println();
		
		
		for(int i=0 ; i<cipherE.size() ; i++){
			ipD.add(pc.Permutation(cipherE.get(i),pc.initialPermu));
		}
		
		/*for(int i=0 ; i<cipherE.size() ; i++){
			//System.out.println("IP"+i+": "+ipD.get(i));
		}*/
		
		//add left to right after 16 round and after swap
		for(int i=0 ; i<ipD.size() ; i++){
			lr.leftAndRight(ipD.get(i));
			lr.decryptionRounds();
			String left_Right = lr.getLeft() + lr.getRight();
			ipLeftRightD.add(left_Right);
		}
		
		//final permutation
		for(int i=0 ; i<ipLeftRightD.size() ; i++){
			plainD.add(pc.Permutation(ipLeftRightD.get(i),pc.finalPermu));
		}
		
		System.out.println();
		/*for(int i=0 ; i<plainD.size() ; i++){
			System.out.println("PlainText"+i+": "+plainD.get(i));
		}*/
		
		//divide plaintext to 8 bits
		ArrayList<String> subStrings = new ArrayList<String>();
		for(int j=0 ; j<plainD.size() ; j++){
			String str = "";
			for (int i = 0; i < plainD.get(j).length(); i++) {
				str += plainD.get(j).charAt(i);
				if((i+1)%8 == 0){
					subStrings.add(str);
					str = "";
				}
			}	
		}
		
		// convert 8bits to asscii code
		ArrayList<Integer> asscii = new ArrayList<Integer>();
		for(int i=0 ; i<subStrings.size() ; i++){
			asscii.add(Integer.parseInt(subStrings.get(i), 2));
		}
		
		// convert asscii to characters and get
		String str = "";
		for(int i=0 ; i<asscii.size() ; i++){
		    //str = "";
			int assc = asscii.get(i);
		    str += new Character((char)assc).toString();
		}
		System.out.println();
		System.out.println("Plain Text After Decryption: "+str);

		Plaintext = str;
		
		
		
		
		return Plaintext;
	}
}
