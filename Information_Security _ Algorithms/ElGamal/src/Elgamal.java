import java.math.BigInteger;
import java.util.Random;


public class Elgamal {
	
public  BigInteger getRandomBigInteger( BigInteger minValue, BigInteger maxValue) {
		Random rand=new Random();
		
	     BigInteger range = maxValue.subtract(minValue).add(BigInteger.ONE);
	     int bits = range.bitLength();
	     BigInteger ret;
	     do {
	         ret = new BigInteger(bits, rand);
	     } while(ret.compareTo(range) >= 0);
	     return ret.add(minValue);
}
	
 
 public boolean getPrime(BigInteger x){
	 		boolean isPrime = false;
	 		SQandMULT squaer= new SQandMULT() ;
	 		String no2ta=".";
	 		int counter=0 ; 
	 		boolean check_no2ta=false ;
	   for (int i = 0; i < 100; i++) {
	       
	       Random rand1 = new Random();
	       BigInteger a = getRandomBigInteger(BigInteger.valueOf(2),x.subtract(BigInteger.valueOf(2)));
	       BigInteger num = squaer.squaerAndMultiply(a,x.subtract(BigInteger.valueOf(1)),x); 
	     		 
	      // System.out.println("checking prime"+no2ta);
	       if(! num.equals(BigInteger.valueOf(1) )){ // el mfrod hna if natg el sqaure and multiply != 1
	          isPrime=false;
	           break;
	         }
	             
	        else isPrime=true;
	        }
	  	if(counter<100&&check_no2ta==false){
	       no2ta=no2ta+".";
	       counter++ ;

	       }
	     else{
	        no2ta=no2ta.substring(1) ;
          	check_no2ta=true ; 

	         if(no2ta.length()==1){
	         	check_no2ta=false ; 
	         }
		      counter--;

	     }
	    return isPrime;  
	}
 
 public BigInteger EEA(BigInteger r0,BigInteger r1){
	 BigInteger a=r0, b=r1 ;
		        BigInteger x = BigInteger.valueOf(0), y = BigInteger.valueOf(1), lastx  = BigInteger.valueOf(1), lasty  = BigInteger.valueOf(0), temp;
		        while (!r1.equals(BigInteger.valueOf(0)))
		        {
		        	
		        	BigInteger q = r0.divide(r1) ;
		        	BigInteger r = r0.mod(r1);
		 
		            r0 = r1;
		            r1 = r;
		 
		            temp = x;
		            x = lastx.subtract(q.multiply(x)) ;
		            lastx = temp;
		 
		            temp = y;
		            y = lasty.subtract(q.multiply(y));
		            lasty = temp;            
		        }
		       // BigInteger arr[] = new BigInteger [3] ; 
		      //  BigInteger sum = (lastx*a)+(lasty*b) ;
		       /* arr[0]=lastx ;
		        
		    	if (lasty<0){

		    		lasty=a+lasty ; 
		    	}
		        arr[1]=lasty ;
		        arr[2]=sum;*/
		        return lasty ;
	}

 public String BIGTOHEX(BigInteger b) {
	String hex = "";
	
	hex = b.toString(16);
	
	return hex;
}
 
 public BigInteger[] Key() {
	 BigInteger[] keys = new BigInteger[4];
	 BigInteger p ;
	 BigInteger alpha ;
	 BigInteger d ;
	 BigInteger B ;
	 SQandMULT squaer= new SQandMULT() ;
	 while (true) {
		p = getRandomBigInteger(BigInteger.valueOf(1), BigInteger.valueOf((long) Math.pow(2, 500)));
		
		if(getPrime(p) == true)
			break;
	}
	 
	 alpha = getRandomBigInteger(BigInteger.valueOf(2), p.subtract(BigInteger.valueOf(2)));
	 d = getRandomBigInteger(BigInteger.valueOf(2), p.subtract(BigInteger.valueOf(2)));
	 B = squaer.squaerAndMultiply(alpha, d, p);
	 
	 keys[0] = p;
	 keys[1] = alpha;
	 keys[2] = d;
	 keys[3] = B;
	 
	 return keys;
 }

}
