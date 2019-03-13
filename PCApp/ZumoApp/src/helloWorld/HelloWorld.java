package helloWorld;

public class HelloWorld {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Hello World!");
		for (int i = 0; i <= 10; i++) {
			java.util.Random rand = new java.util.Random();
			System.out.println(rand.nextInt(100));
		}
	}

}
