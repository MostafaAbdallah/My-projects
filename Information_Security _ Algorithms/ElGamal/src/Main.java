import java.math.BigInteger;
import java.util.Scanner;


public class Main {


	public static void main(String[] args) {
		String plainText = "";
		String plainTextDEC = "";
		String cipher = "";
		BigInteger[] keys = new BigInteger[4];
		BigInteger Km ;
		BigInteger IKm ;
		BigInteger a ;
		int c = 0;
		String str = "";
		BigInteger Y;
		BigInteger X;
		Elgamal e = new Elgamal();
		SQandMULT squaer= new SQandMULT() ;
		Scanner input = new Scanner(System.in);
		
		plainText = input.nextLine();
		
		keys = e.Key();
		System.out.println("P = "+keys[0]+ "  alpha = "+keys[1]+ "  d = "+keys[2]+"  B = "+keys[3]);
		
		for (int i = 0; i < plainText.length(); i++) {
			a = e.getRandomBigInteger(BigInteger.valueOf(2), keys[0].subtract(BigInteger.valueOf(2)));
			Km = squaer.squaerAndMultiply(keys[3], a, keys[0]);
			System.out.println("Km = " + Km);
			c = plainText.charAt(i);
			Y = Km.multiply(BigInteger.valueOf(c));
			
			Y = Y.mod(keys[0]);
			str = e.BIGTOHEX(Y);
			cipher = cipher + " " + str;
			IKm = e.EEA(Km.max(keys[0]), Km.min(keys[0]));
			IKm = IKm.mod(keys[0]);
			X = IKm.multiply(Y);
			X = X.mod(keys[0]);
			System.out.print(IKm + "  ");
			plainTextDEC = plainTextDEC + (char)X.intValue();
		}
		
		System.out.println("Cipher = " + cipher);
		System.out.println("plaintext = " + plainTextDEC);

	}

}
