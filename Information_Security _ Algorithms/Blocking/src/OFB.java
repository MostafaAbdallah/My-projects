import java.util.ArrayList;
import java.util.Random;


public class OFB {
	
	ArrayList<Integer> CipherText = new ArrayList<Integer>();
	String IV = "",
	firstCipher="",
	cipher="",
	xor="",
	t="",
	temp="";
	
public void encrypt(){
		
}
	
ArrayList<String> OutFeedBackMode (ArrayList<String> PlainText, String key)
{
	 ArrayList<String> cip = new ArrayList<String>();
	 String initialVector="";
	 OFBEncryption en = new OFBEncryption();
	 Random rand = new Random(); 
		int value=0;
		for(int i=0; i<128; i++){
			IV+= rand.nextInt(2);
		}
		System.out.println("ivvvvvvvv"+IV.length() );			

		initialVector= en.encryption(IV,  key);
        System.out.println("ivvvvvvvv"+initialVector.length() );			
	for(int i=0 ; i<PlainText.size(); i++){
		temp= PlainText.get(i);
		System.out.println("temp "+temp);
		System.out.println("IV "+initialVector);
		for(int j=0;j<128;j++){
		if( temp.charAt(j)==initialVector.charAt(j)) {cipher+="0"; t+="0";}
		else { cipher+=1; t+=1;}
		}
	    //Integer.valueOf(String.valueOf(PlainText.get(i)), 16);
		System.out.println("ciiiiiiiiiiiiiipher"+cipher);
		cip.add(cipher);
		cipher="";
	}
	
	return cip;

}
	
}

/*public static void main(String[] args) {
	
	OFB ofb= new OFB();
	ArrayList<String> plain = new ArrayList<String>();
	Random rand = new Random(); 
	String value="";
	for(int i=0; i<10; i++){
		for(int j=0; j<128; j++){
					value+= rand.nextInt(2);
					            }
					plain.add(value);
					value="";

				          }
				System.out.println(plain.size());
				
				ofb.OutFeedBackMode(plain);
			}


}*/

