package forelesning14012019;

public class Person {
	
	String name;
	int age;
	
	public Person(String name, int age) {
		this.name = name;
		this.age = age;
	}
	
	public String getName() {
		return name;
	}
	
	public int getAge() {
		return age;
	}
	
	public void printInfo() {
		System.out.println(name + " is " + age + " years old.");
	}
	
	public static void main(String[] args) {
		Person p = new Person("Gunnar", -3);
		p.printInfo();
	}
}
