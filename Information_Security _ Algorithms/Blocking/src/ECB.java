import java.util.ArrayList;


public class ECB {
	
	ArrayList<String> ECBEncrypt(ArrayList<String> bitmap, String Key){
		ArrayList<String> cipherBitmap = new ArrayList<String>();
		Encryption e = new Encryption();
		String s = "";
		for (int i = 0; i < bitmap.size(); i++) {
			s  = e.encryption(bitmap.get(i), Key);
			cipherBitmap.add(s);
		}
		
		
		return cipherBitmap;
	}
}
