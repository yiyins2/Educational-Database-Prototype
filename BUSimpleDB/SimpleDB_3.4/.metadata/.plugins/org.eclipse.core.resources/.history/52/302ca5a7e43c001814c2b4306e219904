import java.util.Iterator;
import java.util.NoSuchElementException;

public class LookAheadIterator<T> implements Iterator<T> {
	private Iterator<T> iter;
	private T next = (T) "" ;
	
	public LookAheadIterator(Iterator<T> iter) {
		this.iter = iter;  
	}

	public boolean hasNext() {
		while(iter.hasNext()) {
			return true; 
		}
		return false;
	}

	public T next() {
		T current = next; 
		next = iter.next();
		return next;
	}

	public T peek() {
		return next; 
	}
}
