package forelesning14012019;

public class Book {

	String title = "Unknown";
	String[] genres;
	int numberOfPages;
	int currentPage = 0;
	String author;
	int publishedYear;
	int version;

	public Book(String title, int numberOfPages) {
		this.title = title;
		this.numberOfPages = numberOfPages;
	}

	public Book(String title, int numberOfPages, int currentPage) {
		if (numberOfPages < 0) {
			throw new IllegalArgumentException("Number of pages can't be negative");
		}
		if (currentPage > numberOfPages) {
			throw new IllegalArgumentException("Current page can't be larger than total amount of pages");
		}
		this.title = title;
		this.numberOfPages = numberOfPages;
		this.currentPage = currentPage;
	}

	public static void main(String[] args) {
		Book HP = new Book("Harry Potter og de vises stein", 550);
		System.out.println();
		String testStr = "HY";
		String test2 = testStr.substring(0, 2);
		System.out.println(testStr.substring(0, 2) + " " + test2);
		System.out.println(test2 == "HY");
	}

}
