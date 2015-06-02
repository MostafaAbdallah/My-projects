import java.util.Scanner;


public class main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int num = 0;
		System.out.print("Enter (1) Encryption (2) Decryption : ");
		Scanner input = new Scanner(System.in);
		num = input.nextInt();
		Encryption e = new Encryption();
		Decryption d = new Decryption();
		if(num == 1)
			e.encryption();
		else
			d.decryption();
	
	}

}
