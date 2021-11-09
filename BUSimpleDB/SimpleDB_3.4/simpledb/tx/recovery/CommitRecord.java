package simpledb.tx.recovery;

import simpledb.file.Page;
import simpledb.log.LogMgr;
import simpledb.tx.Transaction;

/**
 * The COMMIT log record
 * @author Edward Sciore
 */
public class CommitRecord implements LogRecord {
   private int txnum;

   public CommitRecord(Page p) {
      int tpos = Integer.BYTES;
      txnum = p.getInt(tpos);
   }

   public int op() {
      return COMMIT;
   }

   public int txNumber() {
      return txnum;
   }

   /**
    * Does nothing, because a commit record
    * contains no undo information.
    */
   public void undo(Transaction tx) {}

   public String toString() {
      return "<COMMIT " + txnum + ">";
   }

   /** 
    * A static method to write a commit record to the log.
    * This log record contains the COMMIT operator,
    * followed by the transaction id.
    * @return the LSN of the last log value
    */
   public static int writeToLog(LogMgr lm, int txnum) {
      byte[] rec = new byte[2*Integer.BYTES];
      Page p = new Page(rec);
      p.setInt(0, COMMIT);
      p.setInt(Integer.BYTES, txnum);
      return lm.append(rec);
   }
}
