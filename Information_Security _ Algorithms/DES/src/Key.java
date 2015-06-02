import java.util.ArrayList;


public class Key {
	private ArrayList<String> Binary ; 
	private ArrayList<String> afterPC1 ; 
	private ArrayList<String> KeyENCRTAYA ; 
	private ArrayList<String> KeyDECRTAYA ; 
	private ArrayList<String> afterPC2 ; 
	private ArrayList<String> CD ;
	private ArrayList<String> DD ;
	private ArrayList<String> Decrpt ;
	private ArrayList<String> mix ; 
	private ArrayList<String> mixDEC ;
	private String binary="",in="",EnC="",DeC="";
	private int []PCone ;
	private int []PCtwo ;
	private ArrayList<String> C ; 
	private ArrayList<String> D ; 
	private int count =1, x=0 ;
	private String temp1="",temp2="" ;
	public Key(){
		
		Binary =new ArrayList<String>() ;
		afterPC1 =new ArrayList<String>() ;
		KeyENCRTAYA =new ArrayList<String>() ;
		KeyDECRTAYA =new ArrayList<String>() ;
		afterPC2 =new ArrayList<String>() ;
		CD =new ArrayList<String>() ;
		DD =new ArrayList<String>() ;
		Decrpt =new ArrayList<String>() ;
		mix =new ArrayList<String>() ;
		mixDEC =new ArrayList<String>() ;
		C =new ArrayList<String>() ;
		D =new ArrayList<String>() ;
		PCone =  new int []{57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,
							43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,
							7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4} ;
		
		PCtwo = new int []{14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,
							13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
	}
	public void PC2()
	{ 
		x=0;
		afterPC2.clear();
		for(int i=0; i<PCtwo.length; i++)
		{
			x= PCtwo[i];
			afterPC2.add(mix.get(x-1));
			EnC+=mix.get(x-1) ;
		
		}
		//System.out.println();
		//System.out.print("subKey"+count+"= ");
		for(int i=0; i<afterPC2.size(); i++)
		{
			if (i%8==0 && i!=0){
				//System.out.print(" ");
			}
			//System.out.print(afterPC2.get(i));
			
		}
		KeyENCRTAYA.add(EnC) ;
		EnC = "" ;
		count ++ ; 
		
	}
	
	public void PC2_DEC()
	{ 

		x=0;
		Decrpt.clear();
		for(int i=0; i<PCtwo.length; i++)
		{
			x= PCtwo[i];
			Decrpt.add(mixDEC.get(x-1));
			DeC+=mixDEC.get(x-1) ;
		}
		//System.out.println();

		//System.out.print("subKey"+count+"= ");
		for(int i=0; i<Decrpt.size(); i++)
		{
			if (i%8==0 && i!=0){
			//	System.out.print(" ");
			}
		//	System.out.print(Decrpt.get(i));
			
		}
		KeyDECRTAYA.add(DeC);
		DeC="" ;
		count ++ ; 
		
	}
	public void C_D(int round){
		if (round==1||round==2||round==9||round==16){
			temp1 = C.get(0)  ;
			C.remove(0) ; 
			C.add(temp1) ;
			
			temp1 = D.get(0)  ;
			D.remove(0) ; 
			D.add(temp1) ;
		}
		else{
			temp1 = C.get(0)  ;
			temp2= C.get(1) ;
			C.remove(0) ; 
			C.remove(0) ;
			C.add(temp1) ;
			C.add(temp2) ;
			
			temp1 = D.get(0)  ;
			temp2= D.get(1) ;
			D.remove(0) ; 
			D.remove(0) ;
			D.add(temp1) ;
			D.add(temp2) ;
			
		}
		
		if(round==16)
		{
			CD=C ;
			DD=D ; 
		}
		/*
		System.out.println();
		System.out.print("C: "+count+": ");
		for(int i=0; i<28; i++){{System.out.print(C.get(i));}}
		System.out.println();
		System.out.print("D: "+count+": ");
			for(int i=0; i<28; i++){System.out.print(D.get(i));}*/
		
		for(int i=0; i<56; i++){
			if(i<28)
			{mix.add(C.get(i));}
			else {mix.add(D.get(i-28));}
		}
		PC2();
		
	}
	
	public void Decryption(int round){
		
		if (round==2||round==9||round==16){
			temp1 = CD.get(27)  ;
			CD.remove(27) ; 
			CD.add(0, temp1);
			
			temp1 = DD.get(27)  ;
			DD.remove(27) ; 
			DD.add(0, temp1);
		}
		else if (round!=1){
			temp1 = CD.get(27)  ;
			temp2= CD.get(26) ;
			CD.remove(27) ; 
			CD.remove(26) ;
			CD.add(0, temp1);
			CD.add(0, temp2);
			
			temp1 = DD.get(27)  ;
			temp2= DD.get(26) ;
			DD.remove(27) ; 
			DD.remove(26) ;
			DD.add(0, temp1);
			DD.add(0, temp2);
			
		}
		
		
		
		
		/*
		System.out.println();
		System.out.print("C: "+count+": ");
		for(int i=0; i<28; i++){{System.out.print(C.get(i));}}
		System.out.println();
		System.out.print("D: "+count+": ");
			for(int i=0; i<28; i++){System.out.print(D.get(i));}*/
		
		for(int i=0; i<56; i++){
			if(i<28)
			{mixDEC.add(CD.get(i));}
			else {mixDEC.add(DD.get(i-28));}
		}
		PC2_DEC();
		
	}
	
	
	
	public void PC1()
	{
		
		 x=0;
		for(int i=0; i<PCone.length; i++)
		{
		//	System.out.println("Binary= "+Binary.get(i));
			if (i < 28){
				C.add(Binary.get(i));
			}
			else {
				D.add(Binary.get(i));
			}
		}
		
		/*System.out.println();
		System.out.print("After PC-1 :");
		*/for(int i=0; i<afterPC1.size(); i++)
		{
		//	System.out.print(afterPC1.get(i));
			
		}
		//System.out.println();
		//System.out.print("C0= ");
		for(int i=0; i<C.size(); i++)
		{
			//System.out.print(C.get(i));
			
		}
		/*System.out.println();
		System.out.print("D0= ");
		for(int i=0; i<D.size(); i++)
		{
			System.out.print(D.get(i));
			
		}
		System.out.println();
		System.out.println("Encryption keys: ");
*/
		for (int r=1; r<=16;r++){
			mix.clear();
			C_D(r) ;
		}
		count=1;
		//System.out.println();
		//System.out.println();
		//System.out.println("Decryption keys: ");

		for (int r=1; r<=16;r++){
			mixDEC.clear();
			Decryption(r);
		}
	}
	
	
	
	public void chToBin (String key){
	
		for(int i=0; i<key.length(); i++)
		{
			
			in+=key.charAt(i) ;
			Binary.add(in);
			in="";
		}
		/*System.out.println();
		System.out.print("Key: ");
		for(int i=0; i<Binary.size(); i++)
		{ //System.out.print(Binary.get(i));}
    //   System.out.println();
      // System.out.println("Key Generation: ");*/
		
		PC1();
	}
	public ArrayList<String> KeyEncryption(){
		
		return KeyENCRTAYA ;
	}
	
    public ArrayList<String> KeyDecryption(){
		
		return KeyDECRTAYA ;
	}


}
