import java.util.ArrayList;


public class GFunction {
	
	String[][] GF = new String[][]{
			  

{"63","7c","77","7b","f2","6b","6f","c5","30","01","67","2b","fe","d7","ab","76"},
			 

{"ca","82","c9","7d","fa","59","47","f0","ad","d4","a2","af","9c","a4","72","c0"},
			  

{"b7","fd","93","26","36","3f","f7","cc","34","a5","e5","f1","71","d8","31","15"},
			  

{"04","c7","23","c3","18","96","05","9a","07","12","80","e2","eb","27","b2","75"},
			  

{"09","83","2c","1a","1b","6e","5a","a0","52","3b","d6","b3","29","e3","2f","84"},
			  

{"53","d1","00","ed","20","fc","b1","5b","6a","cb","be","39","4a","4c","58","cf"},
			  

{"d0","ef","aa","fb","43","4d","33","85","45","f9","02","7f","50","3c","9f","a8"},
			  

{"51","a3","40","8f","92","9d","38","f5","bc","b6","da","21","10","ff","f3","d2"},
			  

{"cd","0c","13","ec","5f","97","44","17","c4","a7","7e","3d","64","5d","19","73"},
			  

{"60","81","4f","dc","22","2a","90","88","46","ee","b8","14","de","5e","0b","db"},
			  

{"e0","32","3a","0a","49","06","24","5c","c2","d3","ac","62","91","95","e4","79"},
			  

{"e7","c8","37","6d","8d","d5","4e","a9","6c","56","f4","ea","65","7a","ae","08"},
			  

{"ba","78","25","2e","1c","a6","b4","c6","e8","dd","74","1f","4b","bd","8b","8a"},
			  

{"70","3e","b5","66","48","03","f6","0e","61","35","57","b9","86","c1","1d","9e"},
			  

{"e1","f8","98","11","69","d9","8e","94","9b","1e","87","e9","ce","55","28","df"},
			  

{"8c","a1","89","0d","bf","e6","42","68","41","99","2d","0f","b0","54","bb","16"}
    		};
	String W2;
	ArrayList<String> RC = new ArrayList<String>();

	int y,f,d,d1,len1,len2;
	char c, h;
	String firstTwo, XORed,temp,temp1;
	


	public GFunction(){
		W2= "";
		RC= new ArrayList<String>();

		y=f=d=d1=len1=len2=0;
		c=' ';
		h=' ';
		firstTwo="";
		XORed="";
		temp="";
		temp1="";
		
		RC.add("01");
		RC.add("02");
		RC.add("04");
		RC.add("08");
		RC.add("10");
		RC.add("20");
		RC.add("40");
		RC.add("80");
		RC.add("1b");
		RC.add("36");
	}
	

	public void G_Fun(String W){
		
		
		String m="", n="";
		 m+= W.charAt(0);
		 n+=W.charAt(1);
		 
		 W=W.substring(2);
		
		 
		W+=m+n ; 
		m="";
		firstTwo=W2="";
		System.out.println();
		for(int i=0; i<W.length(); i+=2){
			c=W.charAt(i) ;
			h=W.charAt(i+1) ;
			
			
			if((int)c >= 97 ){
				f=(int)c;

				f-=87;
			}
			
			else 
				f= Integer.parseInt(W.charAt(i)+"");
			
			if((int)h >= 97 ){
				y=(int)h;

				y-=87;
			}
			else 
				y= Integer.parseInt(W.charAt(i+1)+"");

			String u;
			u = GF[f][y];
			if(u.length() < 2){
				u = "0" + u;
			}
			W2+=u;
			
		}
		
		firstTwo+=W2.charAt(0);
		firstTwo+=W2.charAt(1);
	}
	
	
	public String RoundC(int x, String s){
		
		G_Fun(s);
		XORed="" ;
		String Bin, t, Bin1, t1;
		System.out.println("first two: "+firstTwo);
	     d= Integer.parseInt(RC.get(x), 16);
	     d1= Integer.parseInt(firstTwo, 16);
		 Bin = Integer.toBinaryString(d);
		 t = Integer.toBinaryString(d1);
		for(int i=0; i<8; i++){
			if(Bin.length()<8){ 
				Bin="0"+Bin;	
			}
			if(t.length()<8){ 
				t="0"+t;
			}
		
		}
		
	  for(int i=0; i<8; i++){
	   
	    	if(Bin.charAt(i)== t.charAt(i))
	    	{
	    		XORed+="0";
	    	}
	    	else XORed+="1";
	    	
	    }
	  
		
	    d= Integer.parseInt(XORed, 2);
	     String nXORed= Integer.toHexString(d);
	      if (nXORed.length()<2){
			  nXORed="0"+ nXORed ;  
		  }

		W2=W2.substring(2);
		W2= nXORed+W2;
		
	    
		return W2;
	}
	
}
