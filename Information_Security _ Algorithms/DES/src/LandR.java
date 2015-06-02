import java.util.ArrayList;


public class LandR {
	
	private F_Function f;
	private Key key;
	//private PermutationChoice p;
	private ArrayList<String> E = new ArrayList<String>();
	private ArrayList<String> D = new ArrayList<String>();
	private String right;
	private String left;
	private String tempLeft;
	
	
	public LandR(String k){
		right = "";
		left = "";
		tempLeft = "";
		f = new F_Function();
		key = new Key();
		//p = new PermutationChoice();
		key.chToBin(k);

	}
	
	// split binary string to left and right
	public void leftAndRight(String plainText){
			left = plainText.substring(0,32);
			right = plainText.substring(32, 64);
	}
	
	public void leftToTemp(){
		tempLeft = left;
	}
	
	// put right part to left
	public String rightToLeft(){
		 left = right;
		 
		 return left;
	}

	
	// xor operation
	public String leftXorF(String temp , String function){
		String xor="";
		for(int i=0 ; i<temp.length() ; i++){
			if(temp.charAt(i) == function.charAt(i)){
				xor += "0";
			}else if(temp.charAt(i) != function.charAt(i)){
				xor += "1";
			}
		}
		return xor;
	}
	
	// 16 round for Encryption
	public void encryptionRounds(){
		E = key.KeyEncryption();
		
		for(int i=0 ; i<16 ; i++){
			leftToTemp();
			rightToLeft();
			// left here was right before swap
			String function = f.F_function(left,E.get(i));
			// remove spaces
			//String f = function[i].replaceAll("\\s+","");
			right = leftXorF(tempLeft , function);
			/*System.out.println("L"+"["+(i+1)+"]"+": "+"\t"+left);
			System.out.println("R"+"["+(i+1)+"]"+": "+"\t"+right);
			System.out.println();*/
		}
		swapLandR();
		//After Swap Operation
		/*System.out.println("After Swap Operation:");
		System.out.println("Left:"+"\t"+left);
		System.out.println("Right"+"\t"+right);*/
	}
	
	//16 round for Decryption
	public void decryptionRounds(){
		D = key.KeyDecryption();
		//System.out.println();
		for(int i=0 ; i<16 ; i++){
			leftToTemp();
			rightToLeft();
			// left here was right before swap
			String function = f.F_function(left,D.get(i));
			// remove spaces
			//String f = function[i].replaceAll("\\s+","");
			right = leftXorF(tempLeft , function);
			/*System.out.println("L"+"["+(i+1)+"]"+": "+"\t"+left);
			System.out.println("R"+"["+(i+1)+"]"+": "+"\t"+right);
			System.out.println();*/
		}
		swapLandR();
		//After Swap Operation
		/*System.out.println("After Swap Operation:");
		System.out.println("Left:"+"\t"+left);
		System.out.println("Right"+"\t"+right);*/
	}
	
	public void swapLandR(){
		String temp;
		temp = right;
		right = left;
		left = temp;
	}
	
	public String getLeft(){
		return left;
	}
	public String getRight(){
		return right;
	}
	
	
}
