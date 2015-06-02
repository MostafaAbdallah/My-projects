import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;


public class BruteForceAttack {
	PlainText P = new PlainText();
	String plainText;
    String cipherText = "";
	String plainBinary="";
	String cipherHex = "";
	String temp="";
	String temp2 = "";
	String p,c;
	int d=0,len=0,m=0,leng=0;double key=(double)(Math.pow(2, 56));
	 
	ArrayList <String> keys =  new ArrayList ();
	ArrayList <String> RightKeys = new ArrayList ();
	
	ArrayList <Integer> Plain =  new ArrayList ();
	ArrayList <String> Cipher = new ArrayList ();
	
	public String appendZeros(String K){
		while(K.length()%56 !=0){
			K = "0" + K;
		}
		
		return K;
	}
	
 ArrayList<String> KEYS(BigInteger start, BigInteger end) {
	 String str = "";
	 
	for (BigInteger i=start ; i.compareTo(end)<0; i = i.add(BigInteger.ONE)){
		str = i.toString(2);
		str = appendZeros(str);
		
		keys.add(str);
		System.out.println(c);
		
			
	}
	return keys;
}
	
	
	

	
ArrayList<String >BruteForce (ArrayList <String> Cipher , ArrayList <String> RightKeys)
{
	
	return RightKeys;
		
}



 ArrayList<String> BruteForceFun(String plainText, String cipherText, BigInteger start, BigInteger end ){
	
	 DES_Dec Des = new DES_Dec();
	 
	 ArrayList<String> PosKeys = new ArrayList<String>();
	 ArrayList<String> Keys = new ArrayList<String>();
	 
	 String likelyPlain = "";
	 Keys = KEYS(start, end);
	 System.out.println(Keys.size());
	 for (int i = 0; i < Keys.size(); i++) {
		 System.out.println(Keys.get(i));
		likelyPlain = Des.Decreption(cipherText, Keys.get(i));
		
		if((likelyPlain.contains(plainText.subSequence(0, 7)))){
			PosKeys.add(Keys.get(i));
			System.out.println( Keys.get(i));
		}
	}
	 
	Keys.clear();
	 return PosKeys;
	 
 }
 
 String decr(String cipherText, String K){
	 String p = "";
	 DES_Dec Des = new DES_Dec();
	 
	p = Des.Decreption(cipherText, K);
	 
	 return p;
 }


}
