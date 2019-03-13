package forelesninger;

public class Person {

	int age;
	String name;

	public Person(String name, int age) {
		this.age = age;
		this.name = name;
	}
	
	public Person() {
		this.age = 0;
		this.name = "Dummy";
	}

	int getAge() {
		return age;
	}

	String getName() {
		return name;
	}

	public void printInfo() {
		System.out.println(name + " er " + age + " år gammel.");
	}
	
	@Override
	public String toString() {
		return (name + ", " + age);
	}

	public static void main(String[] args) {
		Person p1 = new Person("Oddvar", 2);
		Person p2 = new Person("Haldis", 98);
		p1.printInfo();
		p2.printInfo();
	}

}
