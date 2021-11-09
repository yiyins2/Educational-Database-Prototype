import java.util.AbstractCollection;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;

public class SortedCollection<T> extends AbstractCollection<T> {
	private Collection<T> result;

	public SortedCollection(Collection<T> c, Comparator<T> comp) { 
		result = sort(c, comp);
	}

	private Collection<T> sort(Collection<T> c, Comparator<T> comp) {
		Collection<T> left = new ArrayList(); Collection<T> right = new ArrayList(); 
		Collection<T> fin = new ArrayList(); 
		Iterator iter = c.iterator();

		int mid;
		if (c.size() == 1) {    
			return c;
		} 

		else {
			mid = c.size()/2;

			for (int i=0; i<mid; i++) {
				left.add((T) iter.next());
			}

			for (int i=mid; i<c.size(); i++) {
				right.add((T) iter.next());
			}

			left = sort(left, comp);
			right = sort(right, comp); 

			MergedIterator m1 = new MergedIterator(left.iterator(), right.iterator(), comp); 
			while(m1.hasNext()) {
				fin.add((T) m1.next()); 
			}

		}
		return fin; 
	}

	public Iterator<T> iterator() {
		return result.iterator();
	}

	public int size() {
		return result.size();
	}
}