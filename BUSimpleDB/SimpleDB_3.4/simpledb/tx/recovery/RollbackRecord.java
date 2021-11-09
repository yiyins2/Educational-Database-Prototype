package simpledb.tx.recovery;

import simpledb.file.Page;
import simpledb.log.LogMgr;
import simpledb.tx.Transaction;

/**
 * The ROLLBACK log record.
 * @author Edward Sciore
 */
public class RollbackRecord implements LogRecord {
   private int txnum;

   /**
    * Create a RollbackRecord object.
    * @param txnum the ID of the specified transaction
    */
   public RollbackRecord(Page p) {
      int tpos = Integer.BYTES;
      txnum = p.getInt(tpos);
   }

   public int op() {
      return ROLLBACK;
   }

   public int txNumber() {
      return txnum;
   }

   /**
    * Does nothing, because a rollback record
    * contains no undo information.
    */
   public void undo(Transaction tx) {}

   public String toString() {
      return "<ROLLBACK " + txnum + ">";
   }

   /** 
    * A static method to write a rollback record to the log.
    * This log record contains the ROLLBACK operator,
    * followed by the transaction id.
    * @return the LSN of the last log value
    */
   public static int writeToLog(LogMgr lm, int txnum) {
      byte[] rec = new byte[2*Integer.BYTES];
      Page p = new Page(rec);
      p.setInt(0, ROLLBACK);
      p.setInt(Integer.BYTES, txnum);
      return lm.append(rec);
   }
}
