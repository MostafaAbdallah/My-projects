import java.lang.reflect.Array;
import java.util.ArrayList;


public class AesKey {
	private	String w0  ;
	private	String  w1  ;
	private	String w2  ;
	private	String w3  ;
	private ArrayList<String> subKeys ; 
	private ArrayList<String> decryptionKeys ; 

	int count = 0 ; 
	public AesKey(){
		
		subKeys=new ArrayList<String>();
        decryptionKeys=new ArrayList<String>();

	}
	
	public void toHex(String s){
		String a="" ;
		String t="" ;		
		String q=" ";
		/*for (int i =0 ; i<s.length();i++){
	    	char c =s.charAt(i) ;
		    int	bin = (int)c ; 
		    String bombinary = Integer.toHexString(bin);
		    if (bombinary.length()<2){
		    	bombinary="0"+ bombinary ;  
			  }
		    a+=bombinary ; 
		    
		    
	    }*/
		
		a=s;
		for (int i = 8; i <= 32; i+=8) {
			t= a.substring(i-8,i);
			if(count==0){w0=t ; }
			if(count==1){w1=t ; }
			if(count==2){w2=t ; }
			if(count==3){w3=t ; }
			count ++ ; 
		}
		
		GFunction gf= new GFunction();
		for (int i = 0; i < 10; i++) {

			
			if(i==0){

				String d1,Bin="",sub1=w0+w1+w2+w3;
				for (int j = 2; j <= 32; j+=2) {
					String qw = sub1.substring(j-2, j) ;
					 int d= Integer.parseInt(qw, 16);
					String tt = Integer.toBinaryString(d);
					int len = 8-tt.length() ; 
					for(int w=0; w< len; w++){
							tt="0"+tt;		
					}
					 Bin+=tt ; 
				}
				subKeys.add(Bin) ;
			}
			String z=gf.RoundC(i,w3);
			System.out.println("Z="+z);
			round(z) ;
		}
	}
	public void out(){
			for(int ii=subKeys.size()-1; ii>=0;ii--){
		
			decryptionKeys.add(subKeys.get(ii));	
		}
	
		System.out.println("enc");
	for (int i = 0; i < subKeys.size(); i++) {

		System.out.println("subKeys"+i+"= "+subKeys.get(i));
	}
	System.out.println("Decryption Keysssss:");
	for(int j=0; j<decryptionKeys.size();j++){
		System.out.println("decryptionKeys"+j+"= "+decryptionKeys.get(j));
	}
	}
	
	public void round(String z){
		
		String temp1= w0 ;
		String temp2= w1 ;
		String temp3= w2 ;
		String temp4= w3 ;
		String wd,ze,XORed="",sub="" ;
		
		w0 = "" ;
		for (int i=2;i<=8;i+=2){
			
			wd = temp1.substring(i-2, i) ;
			ze = z.substring(i-2, i) ;
		   	
			int d= Integer.parseInt(wd, 16);
			int d1= Integer.parseInt(ze, 16);
			String Bin = Integer.toBinaryString(d);
			String t = Integer.toBinaryString(d1);
			int len = Math.max( Bin.length(), t.length()) ;
			for(int j=0; j< len; j++){
				if(Bin.length()<8){ 
					Bin="0"+Bin;	
				}
				if(t.length()<8){ 
					t="0"+t;
				}
			}
				for(int w=0; w<Bin.length(); w++){
					   
			    	if(Bin.charAt(w)== t.charAt(w))
			    	{
			    		XORed+="0";
			    	}
			    	else XORed+="1";
			    	
			    }
				
				sub+=XORed;
				 d= Integer.parseInt(XORed, 2);
				 XORed="";
				 String nXORed= Integer.toHexString(d);
				 
				  if (nXORed.length()<2){
					  nXORed="0"+ nXORed ;  
				  }
				   w0+=nXORed ;	
			
			}
		
		
		w1="" ;
		for (int i=2;i<=8;i+=2){
			
			wd = w0.substring(i-2, i) ;
			ze = temp2.substring(i-2, i) ;
			int d= Integer.parseInt(wd, 16);
			int d1= Integer.parseInt(ze, 16);
			String Bin = Integer.toBinaryString(d);
			String t = Integer.toBinaryString(d1);
			int len = Math.max( Bin.length(), t.length()) ;
			for(int j=0; j< len; j++){
				if(Bin.length()<8){ 
					Bin="0"+Bin;	
				}
				if(t.length()<8){ 
					t="0"+t;
				}
			}
				for(int w=0; w<Bin.length(); w++){
					   
			    	if(Bin.charAt(w)== t.charAt(w))
			    	{
			    		XORed+="0";
			    	}
			    	else XORed+="1";
			    	
			    }
				sub+=XORed;

				 d= Integer.parseInt(XORed, 2);
				 XORed="";
				 String nXORed= Integer.toHexString(d);
				  
				  if (nXORed.length()<2){
					  nXORed="0"+ nXORed ;  
				  }
				 
				 w1+=nXORed ;
				 
			}
		w2="" ; 
		for (int i=2;i<=8;i+=2){
			
			wd = w1.substring(i-2, i) ;
			ze = temp3.substring(i-2, i) ;
		   	
			int d= Integer.parseInt(wd, 16);
			int d1= Integer.parseInt(ze, 16);
			String Bin = Integer.toBinaryString(d);
			String t = Integer.toBinaryString(d1);
			int len = Math.max( Bin.length(), t.length()) ;
			for(int j=0; j< len; j++){
				if(Bin.length()<8){ 
					Bin="0"+Bin;	
				}
				if(t.length()<8){ 
					t="0"+t;
				}
			}
				for(int w=0; w<Bin.length(); w++){
					   
			    	if(Bin.charAt(w)== t.charAt(w))
			    	{
			    		XORed+="0";
			    	}
			    	else XORed+="1";
			    	
			    }
				sub+=XORed;

				 d= Integer.parseInt(XORed, 2);
				 XORed="";
				 String nXORed= Integer.toHexString(d);
				 if (nXORed.length()<2){
					  nXORed="0"+ nXORed ;  
				  }
				   w2+=nXORed ;	
				 
			}
		
		w3="" ;
		for (int i=2;i<=8;i+=2){
			
			wd = temp4.substring(i-2, i) ;
			ze = w2.substring(i-2, i) ;
		   	
			int d= Integer.parseInt(wd, 16);
			int d1= Integer.parseInt(ze, 16);
			String Bin = Integer.toBinaryString(d);
			String t = Integer.toBinaryString(d1);
			int len = Math.max( Bin.length(), t.length()) ;
			for(int j=0; j< len; j++){
				if(Bin.length()<8){ 
					Bin="0"+Bin;	
				}
				if(t.length()<8){ 
					t="0"+t;
				}
			}
				for(int w=0; w<Bin.length(); w++){
					   
			    	if(Bin.charAt(w)== t.charAt(w))
			    	{
			    		XORed+="0";
			    	}
			    	else XORed+="1";
			    	
			    }
				sub+=XORed;

				 d= Integer.parseInt(XORed, 2);
				 XORed="";
				 String nXORed= Integer.toHexString(d);
				 if (nXORed.length()<2){
					  nXORed="0"+ nXORed ;  
				  }
				   w3+=nXORed ;	
				  
			}
		subKeys.add(sub);
		
		
	}
	public  ArrayList<String> Key(){
		return subKeys ;
	}
	public  ArrayList<String> decrypKey(){
		return decryptionKeys;
	}
}
