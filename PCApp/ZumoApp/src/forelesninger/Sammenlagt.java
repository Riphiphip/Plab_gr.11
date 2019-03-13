package forelesninger;

public class Sammenlagt {

	Person p1;
	Person p2;

	Sammenlagt(Person p1, Person p2) {
		super();
		this.p1 = p1;
		this.p2 = p2;
	}

	int Total() {
		return p1.getAge() + p2.getAge();
	}

	@Override
	public String toString() {
		return Integer.toString(Total());
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println();

	}

}
