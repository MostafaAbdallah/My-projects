import java.math.BigInteger;
import java.util.Scanner;


public class RSAEncryption {
	
long squaerAndMultiply(long base , long power, long n){
		
		String binaryPower = Long.toBinaryString(power);
		//System.out.println("binary: "+binaryPower);
		long result = 0L;
		for(int i=0 ; i<binaryPower.length() ; i++){
			//initial
			if(i == 0){
				result = base;
			}else{
				//squares the equation(result) and then multiplies by the base
				if(binaryPower.charAt(i) == '1'){
					result = (result*result*base) % n;
				//squares the equation(result)
				}else if(binaryPower.charAt(i) == '0'){
					result = (result*result) % n;
				}
			}
		}
		return result;
	}

	public String[] encrypto (String PlainText)
	{
		long Cipher = 0L ;
		long P;
		key key=new key() ; 
		long e_d[]=new long[4] ;
		long e = 0;
		long n = 0;
		String[] ciphertxt = new String[2];
		String str1 ="";
		String str2 ="";
		long x = 0;
		Decryption dec = new Decryption();
		for(int i=0; i<PlainText.length();i++)
		{
			int PlainAscii = (int)PlainText.charAt(i);
				e_d=key.key_gen(PlainAscii) ;
				e = e_d[0];
				
				n = e_d[2] * e_d[3];
			P = Integer.valueOf(PlainAscii);
			Cipher =  squaerAndMultiply(P, e, n);
			System.out.print("P = " + e_d[2] +  "  q = " + e_d[3] +  "  e = " + e_d[0] + "  d = " + e_d[1] + "n =" + n );
			System.out.println("Cipher = " + Cipher);
			x = dec.FastDecryption(e_d[2], e_d[3], e_d[1], Cipher);
			
			
			System.out.println( "Cipher :"+ Cipher);
			System.out.println( "Plain after dec :"+x);
			
			
			str1 =str1 + Cipher+" ";
			str2 = str2 + (char)x;
			//System.out.print( " "+Cipher+ " ");	
		}
		ciphertxt[0] = str1;
		ciphertxt[1] = str2;
		return ciphertxt;
		
	}
	

}
