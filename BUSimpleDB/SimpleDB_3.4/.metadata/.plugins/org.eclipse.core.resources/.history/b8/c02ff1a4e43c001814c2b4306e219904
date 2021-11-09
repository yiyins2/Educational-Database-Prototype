
import java.util.*;

public class MergedIterator<T> implements Iterator<T> {
   private LookAheadIterator<T> i1, i2;
   private Comparator<T> comp;
   T result; 
	  
   public MergedIterator(Iterator<T> iter1, Iterator<T> iter2, Comparator<T> comp) {
      i1 = new LookAheadIterator<T>(iter1);
      i2 = new LookAheadIterator<T>(iter2);
      this.comp = comp;
   }
   
   public boolean hasNext() {
      return i1.hasNext() || i2.hasNext();
   }
   
   public T next() {
	   
	   try {
		   T prev = result;
		   if(comp.compare(prev, i1.peek()) < 0 || comp.compare(prev, i2.peek()) < 0) {
			   return prev; 
		   }
	
		   else if (comp.compare(i1.peek(), i2.peek()) < 0) { 
			   result = i1.next();
			  
		   }
		   else { 
			   result = i2.next();
		   }
	
		   return result; 
	   }
	   
	   catch (NullPointerException ex) {
		   T result;
		   if (!i1.hasNext()) 
			   result = i2.next();
		   else if (!i2.hasNext()) 
			   result = i1.next();
		   else if (comp.compare(i1.peek(), i2.peek()) < 0) 
			   result = i1.next();
		   else 
			   result = i2.next();
		   return result; 
	   }
   }
}

