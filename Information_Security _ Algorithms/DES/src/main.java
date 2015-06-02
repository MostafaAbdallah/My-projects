import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class main {

	public static void main(String[] args) {
		
		BruteForceAttack B = new BruteForceAttack();
		ArrayList<String> AllPosFalse = new ArrayList<String>();
		ArrayList<String> s = new ArrayList<String>();
		ArrayList<String> plaintext = new ArrayList<String>();
		ArrayList<String> ciphertext = new ArrayList<String>();
		int num = 0;
		String p = "", c = "";
		BigInteger start = BigInteger.valueOf(0), end = BigInteger.valueOf(0);
		Scanner input = new Scanner(System.in);
		System.out.print("Enter the number of plaintexts:");
		num = input.nextInt();
		
		System.out.println();
		
		for (int i = 0; i < num; i++) {
			input.nextLine();
			System.out.println("Enter the plaintext:");
			p = input.nextLine();
			
			if(p.length()%8 == 0){
				for (int j = p.length(); j < 64; j++) {
					p = p + "*";
				}
			}
			System.out.print("Enter the ciphertext:");
			c = input.next();
			plaintext.add(p);
			ciphertext.add(c);
			System.out.println();
		}
		
		//System.out.println(B.decr(p, c));
		System.out.print("Enter The Start: ");
		start = input.nextBigInteger();
		System.out.println();
		System.out.print("Enter The End: ");
		end = input.nextBigInteger();
		while(true){
			if(end.subtract(start).equals(BigInteger.valueOf(100))){
				
				break;
			}
			System.out.print("End if Biger Or smaller please Enter The End: ");
			end = input.nextBigInteger();
			
		}
		System.out.println();
		for (int i = 0; i < num; i++) {
			s = B.BruteForceFun(plaintext.get(i), ciphertext.get(i), start, end);
			
			System.out.println("false positive keys for pair number " + i);
			for (int j = 0; j < s.size(); j++) {
				System.out.println("Keys: " + s.get(j));
			}
			
			if(i == 0){
				AllPosFalse = s;
			}
			else{
				ArrayList<String> temp = new ArrayList<String>();
				temp.clear();
				
				for (int j = 0; j < AllPosFalse.size(); j++) {
					for (int j2 = 0; j2 < s.size(); j2++) {
						
						if(AllPosFalse.get(j).equals(s.get(j2))){
							temp.add(s.get(j2));
						}
					}
				}
				AllPosFalse = temp;
				
				System.out.println(temp.size());
			}
		}
		
		
		System.out.println("false positive keys for all pair " );
		for (int j = 0; j < AllPosFalse.size(); j++) {
			System.out.println("Keys [" + j +"]: " + AllPosFalse.get(j));
		}
		
		
		
	}

}