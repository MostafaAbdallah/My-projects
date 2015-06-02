import java.util.ArrayList;
import java.util.Scanner;


public class OFBEncryption {

	String oneVectorHex(String [][] str){
		String s = "";
		String s2 = "";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {

				s2 = str[j][i];

				s = s + s2;
				s = s ;
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
	public String encryption(String plainText, String key){

		Scanner input = new Scanner(System.in);
		//String key = "";
		String cipherHex = "";
		String cipherChar = "";
		String cipherBinary="", finalBinary="";
		String tmp="";
		int d=0,len=0;

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

		PText = p.dividText(plainText, true);
		AK.toHex(key);
		subkey = AK.Key();
		System.out.println("_______________"+ PText.size());
		for (int i = 0; i < 1; i++) {
			subText = PText.get(i);

			subText = Klayer.keyAddition(subText, subkey.get(0));

			for (int j = 0; j < 10; j++) {

				subText = s.subLayer(subText, true);
				subText = sh.shiftRowEncryption(subText);
				if(j != 9)
				subText = MC.mixColumn(subText, true);
				subText = Klayer.keyAddition(subText, subkey.get(j+1));
			}

			cipherHex = cipherHex + oneVectorHex(subText);


			//cipherChar = cipherChar + oneVectorChar(subText);

		}
		System.out.println("cipher leeeeeeeeeeeeeeen= "+cipherHex);
		for (int j=2; j<=32;j+=2){

			tmp= cipherHex.substring(j-2, j);
			d= Integer.parseInt(tmp, 16);
			cipherBinary= Integer.toBinaryString(d);
			len=8-cipherBinary.length();
			for(int w=0; w<len;w++){

				if(cipherBinary.length()<8){cipherBinary="0"+cipherBinary;}
			}
			System.out.println("cipherBinary= "+cipherBinary);
			finalBinary=finalBinary+cipherBinary;
		System.out.println("final "+ finalBinary.length());
		}

		//System.out.println("CipherHex: "+cipherHex);
		//System.out.println("CipherChar: "+cipherChar);
		return finalBinary;
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
