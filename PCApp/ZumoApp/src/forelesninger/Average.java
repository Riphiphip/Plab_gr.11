package forelesninger;

public class Average {
	int valueCount = 0;
	double totalSum = 0;
	
	void acceptValue(double value) {
		totalSum = totalSum + value;
		valueCount++;
	}
	
	double getAverage() {
		return totalSum/valueCount;
	}
	public static void main(String[] args) {
		Average av = new Average();
		av.acceptValue(2);
		av.acceptValue(4.5);
		System.out.println(av.getAverage());
	}

}
