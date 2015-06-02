import java.util.Scanner;


public class Main {

	
	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		System.out.println("Enter 1- Encryption 2- Decryption 3- Exit");
		int num = 0;
		String plaintext = "";
		
		
		long cipher = 0;
	//	while(true){
			num = input.nextInt();
			if(num == 1){
				System.out.print("Enter the plainText:");
				input.nextLine();
				plaintext = input.nextLine();
				RSAEncryption rsa = new RSAEncryption();
				String[] cipherTXT = new String[2];
				cipherTXT = rsa.encrypto(plaintext);
				
				System.out.println("CipherASCII is : " + cipherTXT[0]);
				System.out.println("Palintext After DEC is : " + cipherTXT[1]);
			//	break;
				
			}
			/*else if(num == 2){
				String ciphertxt = "";
				String str = "";
				String cipherLong = "";
				long Cinum =0 ;
				boolean flag = false;
				long e_d[]=new long[4] ;
				Decryption dec = new Decryption();
				key k = new key();
				System.out.print("Enter the Cipher:");
				input.nextLine();
				ciphertxt = input.nextLine();
				for (int i = 0; i < ciphertxt.length(); i++) {
					if(ciphertxt.charAt(i) == ' '){
						flag = true;
					}
					else{
						str = str + ciphertxt.charAt(i);
					}
					
					if(flag || i == ciphertxt.length()-1){
						Cinum = (long)Integer.parseInt(str);
						
						e_d = k.key_gen(num);
						Cinum = dec.FastDecryption(e_d[2], e_d[3], e_d[1], Cinum);
						cipherLong = cipherLong + Cinum;
						plaintext = plaintext + (char)Cinum;
						str = "";
						flag = false;
					}
				}
				System.out.println("PlainAscii is: " + cipherLong);
				System.out.println("Plaintext is: " + plaintext);
				break;
				
			}
			else{
				break;
			}*/
		//}
		
		
	}

}
