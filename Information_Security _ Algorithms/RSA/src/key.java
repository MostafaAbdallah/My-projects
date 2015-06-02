import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Random;



public class key {
		private ArrayList<BigInteger> e=new ArrayList<BigInteger>() ; 
		private ArrayList<BigInteger> d=new ArrayList<BigInteger>() ; 
		

	 private int i , a , p, q,prime,max=((int) Math.pow(2, 15)) -1;
;
	    Random rand= new Random();
	    boolean isPrime=true;
	Scanner input = new Scanner (System.in) ; 
	
public long[]  key_gen(int x){
	long e_d [] =new long[4] ;
	for (int i = 0; i < 2; i++) {
		if(i==0){
			p= rand.nextInt( max )+x+1;
	
			isPrime = getPrime(p) ;
			if(isPrime==false){
				i-- ; 
			}
		}
		if(i==1){
			q= rand.nextInt( max )+x+1;
			isPrime = getPrime(q) ;
			if(isPrime==false){
				i-- ; 
			}
		}
	}
	p=3 ;
	q=11;
	long n =p*q ; 
	long Qn=(p-1)*(q-1) ;
	long arr[] = new long [3] ; 
	long e = 0 ;
	long m = Qn-1 ; 
	for (int i = 0; i <Qn; i++) {
        e= rand.nextInt((int) m)+1 ;
e=3 ; 
        	arr=EEA(Qn, e) ;
        	if(arr[2]==1){
        		break ; 
        	}
	}
	
	e_d[0]=e ; 
	arr =EEA(Qn, e) ;
	long d = arr[1] ; 
	
	e_d[1]=d ;
	e_d[2]=p ;
	e_d[3]=q ;
	return  e_d ;
}

public boolean getPrime(int x){
	SQandMULT squaer= new SQandMULT() ;
          for (i = 0; i < 100; i++) {
        	  
            a= rand.nextInt(x-2)+2;
            long num = squaer.squaerAndMultiply(a,x-1,x) ; 
            if( num != 1){ // el mfrod hna if natg el sqaure and multiply != 1
                isPrime=false;
                break;
            }
            else isPrime=true;
        }
   
    return isPrime;  
}

public long[] EEA(long r0,long r1){
	
	
	long a=r0, b=r1 ;
	        long x = 0, y = 1, lastx = 1, lasty = 0, temp;
	        while (r1 != 0)
	        {
	            long q = r0 / r1;
	            long r = r0 % r1;
	 
	            r0 = r1;
	            r1 = r;
	 
	            temp = x;
	            x = lastx - q * x;
	            lastx = temp;
	 
	            temp = y;
	            y = lasty - q * y;
	            lasty = temp;            
	        }
	        long arr[] = new long [3] ; 
	        long sum = (lastx*a)+(lasty*b) ;
	        
	    //    System.out.println("Roots  s : "+ lastx +" t :"+ lasty+"GCD: "+sum);

	        arr[0]=lastx ;
	        
	    	if (lasty<0){

	    		lasty=a+lasty ; 
	    	}
	        arr[1]=lasty ;
	        arr[2]=sum;
	  //      System.out.println("Roots  s_after : "+ lastx +" t_after :"+ lasty+"GCD: "+sum);
System.out.println();
System.out.println();
	        return arr ;
}



}
