
import java.util.AbstractCollection;
import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;

public class MergedCollection extends AbstractCollection {
	private Collection c1;
	private Collection c2;
	private Comparator comp;
	
	public MergedCollection(Collection c1, Collection c2, Comparator comp) {
		this.c1 = c1;
		this.c2 = c2; 
		this.comp = comp;
	}

	public Iterator iterator() {
		Iterator i1 = c1.iterator();
		Iterator i2 = c2.iterator();
		return new MergedIterator(i1, i2, comp);
	}
	
	public int size() {
		int size1 = 0; 
		Iterator iter = iterator(); 
		while(iter.hasNext()) {
			size1++; 
		}
		return size1; 
	}
	

}
