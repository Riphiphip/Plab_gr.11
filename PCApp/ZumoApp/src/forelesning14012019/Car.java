package forelesning14012019;

import java.util.ArrayList;

public class Car {

	private int capacity;
	private ArrayList<Person> passengers = new ArrayList<Person>();

	public Car(int seats) {
		this.capacity = seats;
	}

	public boolean placePerson(Person p) {
		if (this.capacity == passengers.size()) {
			System.out.println("Bilen er full. " + p.getName() + " får ikke plass");
			return false;
		} else {
			passengers.add(p);
			System.out.println(p.getName() + " lagt til i bilen.");
			System.out.println((capacity - passengers.size()) + " plasser igjen");
			return true;
		}
	}
	
	public void printPassengers() {
		for (Person person : passengers) {
			person.printInfo();
		}
	}

	public static void main(String[] args) {
		Car c = new Car(2);
		c.placePerson(new Person("Ada",25));
	}

}
