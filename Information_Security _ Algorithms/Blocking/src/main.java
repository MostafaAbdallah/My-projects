import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;


public class main {

	/**
	 * @param args
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		
		Scanner input = new Scanner(System.in);
		System.out.print("Enter image name: ");
		String imageName = input.next();
		
		String key = "f6cc34cdc555c5418254260203ad3ecd";
		System.out.println();
		System.out.print("Enter Key stream: ");
		//key = input.next();
		ReadImage r =new ReadImage();
		ECB ecb = new ECB();
		CTR ctr = new CTR();
		OFB ofb = new OFB();
		CipherBlockChaining cbc = new CipherBlockChaining();
		CFBEncryption cfb = new CFBEncryption();
		
		int [][] x = r.seeBMPImage(imageName);
		//r.writeImage(x, "test2.bmp");
		int wigth = x.length;
		int height = x[0].length;
		int [][] y = new int[wigth][height];
		ArrayList<String> v = new ArrayList<String>();
		ArrayList<String> v2 = new ArrayList<String>();
		int choose = 0;
		
		while (true) {
			
			System.out.println("Choose one techniques: ");
			System.out.println("1- ECB");
			System.out.println("2- CBC");
			System.out.println("3- CFB");
			System.out.println("4- OFB");
			System.out.println("5- CTR");
			System.out.println("6- EXIT");
			choose = input.nextInt();
			
			v = r.toVector(x);
			
			
			if(choose == 1){
				v2 = ecb.ECBEncrypt(v, key);
			}
			else if(choose == 2){
				v2 = cbc.cbcEncrypt(v, key);
			}
			else if(choose == 3){
				v2 = cfb.encryption(v, key);
			}
			else if(choose == 4){
				v2 = ofb.OutFeedBackMode(v, key);			
			}
			else if(choose == 5){
				
				v2 = ctr.encryption(v, key);
			}
			else{
				break;	
			}
			
			y = r.toArray(v2, wigth, height);
			r.writeImage(y, "test2.bmp");
			System.out.println("Finish");
		}
		
		
		
		
		
	
	}
}





/*	//System.out.println(x.length);
//System.out.println(x[0].length);
for (int i = 0; i < x.length; i++) {
	for (int j = 0; j < x[i].length; j++) {
		System.out.print(x[i][j]);
	}
	System.out.println();
}

ArrayList<String> v = r.toVector(x);
//x = r.toArray(v, x.length, x[0].length);
for (int i = 0; i < v.size(); i++) {

System.out.println(v.get(i));
}


for (int i = 0; i < v.size(); i++) {
	
	System.out.println(v.get(i));
}
*/