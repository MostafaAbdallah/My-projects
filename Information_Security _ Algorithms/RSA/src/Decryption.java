import java.util.Random;



public class Decryption {
	
	
	private long n, mod, i, j, Yp, Yq, Dp, Dq, Xp, Xq, inv, Cp, Cq, result, X;
	
	Random rand= new Random();
	//Prime p= new Prime();
	key k= new key();
	SQandMULT sm= new SQandMULT();
	
	
	boolean prime;
	long inversep,inverseq;
	Decryption(){
		n = mod = i = j = Yp = Yq = Dp = Dq = Xp = Xq = inv = Cp = Cq = result = X =  0;		
		prime=false;
	}
	
	// returns x for each y in the cipher text
	
	public long FastDecryption (long p, long q, long d, long y){

		n=p*q;
		
		//--------------- Yp mod p & Yq mod q ---------------//

        Yp=y%p;
        Yq=y%q;
		
		//--------------- Dp mod p-1 & Dq mod q-1 ---------------//
		
		Dp=Dq=d;
		Dp=d%(p-1);
		Dq=d%(q-1);
		
		//--------------- Xp mod p & Xq mod q ---------------//
		Xp= sm.squaerAndMultiply(Yp, Dp, p);
		Xq= sm.squaerAndMultiply(Yq, Dq, q);
	
		
		//--------------- Cp mod p & Cq mod q ---------------//
		
		inversep = (k.EEA(p, q))[1];
		inverseq = (k.EEA(q, p))[1];
		
		
		Cp= inversep%p;
		Cq= inverseq%q;
		//--------------- Plaintext X ---------------//
		
		X= ( (q*Cp)*Xp ) + ( (p*Cq)*Xq );
		X=X%n;
		return X;
		
		
	}

}
