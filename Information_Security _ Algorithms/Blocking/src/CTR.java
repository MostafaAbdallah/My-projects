import java.util.ArrayList;
import java.util.Scanner;
import java.util.Random;


public class CTR {
	
	private ArrayList<String> CipherKey ; 
	
	public CTR(){
		CipherKey=new ArrayList<String>();
	}
	String oneVectorHex(String [][] str){
		String s = "";
		String s2 = "";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				s2 = str[j][i];
				
				s = s + s2;
				s = s; 
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
	
	public  ArrayList<String> encryption(ArrayList<String> px, String key){
		
		
		//Scanner input = new Scanner(System.in);
		String plainText = "";
		//String key = "";
		String cipherHex = "",Output_Block="";
		String cipherText = "";
		int count = 0 ; 
		String counter = "" ;
		/*System.out.print("Enter Plain text: ");
		plainText = input.nextLine();
		*/
		String IV= "",wd = "",HexIV="" ; 
		int randm = 0 ; 
		Random rand = new Random(); 
		
		for (int i =0 ; i<96;i++){
			randm=rand.nextInt(2);
			IV+=randm;
		}
		System.out.println("IV= "+IV);
		System.out.println();
		System.out.println();
		for (int i =8 ; i<=96;i+=8){
			wd = IV.substring(i-8, i) ;
			int d= Integer.parseInt(wd, 2);
			 String cToHex= Integer.toHexString(d);
			 if (cToHex.length()<2){
				 cToHex="0"+ cToHex ;  
			  }
			 HexIV+=cToHex ;
			System.out.println("cToHex= "+cToHex);
		}
		HexIV+="00000000";
		System.out.println();
		//System.out.print("Enter Key stream: ");
		//key = input.next();
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
		
		AK.toHex(key);
		subkey = AK.Key();
		
		for (int i = 0; i < px.size()/*PText.size()vector eli gai mn 3abdalla*/ ; i++) {
			if(HexIV.length()>32){
				HexIV = "";
				IV="";
				 randm = 0 ; 
				 rand = new Random(); 
				for (int i2 =0 ; i2<96;i2++){
					randm=rand.nextInt(2);
					IV+=randm;
				}
				System.out.println("IV= "+IV);
				System.out.println();
				System.out.println();
				for (int i2 =8 ; i2<=96;i2+=8){
					wd = IV.substring(i2-8, i2) ;
					int d= Integer.parseInt(wd, 2);
					 String cToHex= Integer.toHexString(d);
					 if (cToHex.length()<2){
						 cToHex="0"+ cToHex ;  
					  }
					 HexIV+=cToHex ;
					System.out.println("cToHex= "+cToHex);
				}
				HexIV+="00000000";
				count = 0;
			}
			
			System.out.println("HexIV="+HexIV);
			PText = p.dividText(HexIV, false);
			subText = PText.get(0) ;
			System.out.println("subText= "+subText);
			subText = Klayer.keyAddition(subText, subkey.get(0));
			
			for (int j = 0; j < 10; j++) {
				
				subText = s.subLayer(subText, true);
				subText = sh.shiftRowEncryption(subText);
				if(j != 9)
				subText = MC.mixColumn(subText, true);
				subText = Klayer.keyAddition(subText, subkey.get(j+1));
			}
			
			Output_Block =oneVectorHex(subText);
			
			for (int j = 2; j <= 32; j+=2) { // xor between out block & plain text = cipher text 
			 	wd = Output_Block.substring(j-2, j) ;
			 	int d= Integer.parseInt(wd, 16);
				String Bin = Integer.toBinaryString(d);
				int len =8- Bin.length();
				for(int w=0; w< len; w++){
					if(Bin.length()<8){ 
						Bin="0"+Bin;	
					}	
				}
				
				String Bin_PlainText=px.get(i).substring(j*4-8, j*4) ;
				String XORed="" ;
				for(int w=0; w<Bin.length(); w++){
					   
			    	if(Bin.charAt(w)== Bin_PlainText.charAt(w))
			    	{
			    		XORed+="0";
			    	}
			    	else XORed+="1";
			    	
			    }
				cipherText += XORed ; 
			}
			CipherKey.add(cipherText);
			String ci="" ;
			for (int q =8 ; q<=128;q+=8){
				wd = cipherText.substring(q-8, q) ;
				int d= Integer.parseInt(wd, 2);
				 String cToHex= Integer.toHexString(d);
				 if (cToHex.length()<2){
					 cToHex="0"+ cToHex ;  
				  }
				 ci+=cToHex ;
				
			}
			System.out.println("cipherText= "+ci);
			count ++ ;
			counter = Integer.toBinaryString(count) ;
			
			int d= Integer.parseInt(counter, 2);
			String cToHex= Integer.toHexString(d);
			if (cToHex.length()<2)
				 cToHex="0"+ cToHex ;
			
			HexIV=HexIV.substring(0,30)+cToHex;
			cipherText="" ;
			
		}
		
		return CipherKey ; 

	}
}


