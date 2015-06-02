import java.util.ArrayList;


public class PlainText {
	
	private String binaryText;
	
	public PlainText(){
		binaryText = "";
	}
	public String plainTextToBinary(String plainText){
		for(int i=0 ; i<plainText.length() ; i++){
			char c = plainText.charAt(i);
			int assci = assci(c);
			String binary = toBinary(assci);
			
			while(binary.length()%8 != 0){
				binary = "0"+binary;
			}
			binaryText += binary;
		}
		appendZeros();
		return binaryText;
	}
	
	public void appendZeros(){
		while(binaryText.length()%64 !=0){
			binaryText += "0";
		}
	}
	
	public String binaryAfterAppend(){
		return binaryText;
	}
	
	public ArrayList<String> divideBinaryTextTo64Bit(String binaryText){
		ArrayList<String> subBinary = new ArrayList<String>();
		String str = "";
		for (int i = 0; i < binaryText.length(); i++) {
			str += binaryText.charAt(i);
			if((i+1)%64 == 0){
				subBinary.add(str);
				str = "";
			}
		}	
		return subBinary;
	}
	
	public int assci(char c){
		int assci = (int)c;
		return assci;
	}
	
	public String toBinary(int number){
		String binary = Integer.toBinaryString(number);
		return binary;
	}
	
	public void PrintBinaryText(){
		System.out.println(binaryText);
	}
}
