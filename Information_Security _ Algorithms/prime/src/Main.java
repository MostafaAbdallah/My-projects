
public class Main {

	static boolean isPrime(int num){
		
		if(num <= 3){
			return num > 1;
		}
		else if(num %2 ==0 || num %3 ==0){
			return false;
		}
		else{
			double sqrtnum = Math.floor(Math.sqrt(num));
			for(int i = 5; i <= sqrtnum; i+=6){
				if(num %i ==0 || num %(i+2) ==0){
					return false;
				}
			}
		}	
		return true;
	}
	static int getNumberOfPrimes(int N) {
		
		int numOfprime = 1;
		if(N < 3)
			numOfprime = 0;
		
		for (int i = 3; i < N; i = i+2) {
			
			if(isPrime(i)){
				numOfprime++;
			}
		}
		
		return numOfprime;

    }
	
	public static void main(String[] args) {
		
		int N = 1000000;
		int r = getNumberOfPrimes(N);
		System.out.println(r);

	}

}
