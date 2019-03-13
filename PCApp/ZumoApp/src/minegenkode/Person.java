package minegenkode;

public class Person {

	String name;
	int age;
	
	
	public Person(String navn, int alder) {
		super();
		this.name = navn;
		this.age = alder;
	}

	public int getAge() {
		return this.age;
	}
	
	public String getName() {
		return this.name;
	}
	
	public void beskrivPerson() {
		System.out.println(this.name+" er "+this.age+" år gammel.");
	}

	public static void main(String[] args) {

		Person p1 = new Person("Per",23);
		Person p2 = new Person("Ida",19);
		p1.beskrivPerson();
		p2.beskrivPerson();
	}

}
