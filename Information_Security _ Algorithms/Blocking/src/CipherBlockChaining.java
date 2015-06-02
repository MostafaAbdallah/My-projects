import java.util.ArrayList;
import java.util.Random;


public class CipherBlockChaining {
	OFBEncryption e = new OFBEncryption();
	
	String initialVector="",
			firstCipher="",
			cipher="",
			xor="",
			t="",
			temp="",
			ciph="";
	int tmp=1;
	boolean c=false;

	public ArrayList <String> cbcEncrypt(ArrayList <String> plain, String key){
		ArrayList <String> cip = new ArrayList<String>();
		Random rand = new Random(); 
		int value=0;
		for(int i=0; i<128; i++){
			initialVector+= rand.nextInt(2);
		}
		
		

		for(int i=0;i<plain.size();i++){
			temp=plain.get(i);
			System.out.println("temp           "+temp);
			for(int m=0; m<128;m++){
				if(i==0){
					c=false;
				if( temp.charAt(m)==initialVector.charAt(m)) {cipher+="0"; t+="0";}
				else { cipher+=1; t+=1;}
				
				}
				else {
					c=true;
					if(t.charAt(m) == temp.charAt(m)) {cipher+="0";}
					else { cipher+="1"; }
							
				}
						
			}
			System.out.println("cii "+ cipher.length());
			ciph= e.encryption(cipher,  key);
			System.out.println("lennn "+ciph.length());
			System.out.println("Cipher "+i/2+" = "+cipher);
			t=ciph;
			cip.add(cipher);
			cipher="";
		}
		
		return cip;
	}


}
