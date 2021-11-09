import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
import java.util.function.Predicate;

import javax.swing.text.html.HTMLDocument.Iterator;

public class HW7Test {
	public static void main(String[] args) throws IOException {
		Collection<String> dict = readFromFile("dictionary.txt"); 
		Collection<String> reversedict = reverse(dict);
		
		// predicate p1 denotes words longer than 20 characters 
		Predicate<String> p1 = new Predicate<String>() {
			public boolean test(String s) {
				return (s.length() > 20);
		}};
		printWords(reversedict, p1);
		System.out.println();
		
		// predicate p2 denotes words beginning with "chori".
		Predicate<String> p2 = new Predicate<String>() {
			public boolean test(String s) {
				return (s.contains("chori"));
			}
		};
		printWords(reversedict, p2); 
	}

	private static Collection<String> reverse(Collection<String> dict) {
		Comparator<String> comp = (s1,s2)->s2.compareTo(s1);
		Collection<String> c = new SortedCollection(dict, comp); 
		return c;
	}

	private static Collection<String> readFromFile(String string) {
		File file = new File(string);
		Collection c = new ArrayList();  
	    try {
	        Scanner sc = new Scanner(file);
	        while (sc.hasNextLine()) {
	            String i = sc.nextLine();
	            c.add(i);
	        }
	        sc.close();
	    } 
	    catch (FileNotFoundException e) {
	        e.printStackTrace();
	    }
		return c;
	}
	
	private static <T> void printWords(Collection<T> dict, Predicate pred) {
		for (T s: dict) {
			if(pred.test(s)) {
				System.out.println(s);
			}
		}
	}
}