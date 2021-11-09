package simpledb.query;

/**
 * The interface will be implemented by each query scan.
 * There is a Scan class for each relational
 * algebra operator.
 * @author Edward Sciore
 */
public interface Scan {
   
   /**
    * Position the scan before its first record. A
    * subsequent call to next() will return the first record.
    */
   public void beforeFirst();
   
   /**
    * Move the scan to the next record.
    * @return false if there is no next record
    */
   public boolean next();
   
   /**
    * Return the value of the specified integer field 
    * in the current record.
    * @param fldname the name of the field
    * @return the field's integer value in the current record
    */
   public int getInt(String fldname);
   
   /**
    * Return the value of the specified string field 
    * in the current record.
    * @param fldname the name of the field
    * @return the field's string value in the current record
    */
   public String getString(String fldname);
   
   /**
    * Return the value of the specified field in the current record.
    * The value is expressed as a Constant.
    * @param fldname the name of the field
    * @return the value of that field, expressed as a Constant.
    */
   public Constant getVal(String fldname);
   
   /**
    * Return true if the scan has the specified field.
    * @param fldname the name of the field
    * @return true if the scan has that field
    */
   public boolean hasField(String fldname);
   
   /**
    * Close the scan and its subscans, if any. 
    */
   public void close();
}
